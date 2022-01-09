//
// Created by Irena Mora on 1/4/22.
//

#include "NeuronNetwork.hpp"

NeuronNetwork::~NeuronNetwork()
{
	t_VectorToNeurons::iterator begin = this->neurons.begin();
	t_VectorToNeurons::iterator end = this->neurons.end();

	while (begin != end)
	{
		this->removeNeuron(**begin);
		begin = this->neurons.begin();
		end = this->neurons.end();
	}
}

void	NeuronNetwork::addConnection(NeuronSimple &from, NeuronSimple &to, double weight)
{
	t_VectorNeuronConnections::iterator current = this->connections.insert(NeuronConnection(from, to, weight)).first;
	from.addConnection(const_cast<NeuronConnection &>(*current));
	to.addConnection(const_cast<NeuronConnection &>(*current));
}

//TODO: optimize this method using and realizing method neuron.getAllConnections()
void	NeuronNetwork::removeAllConnections(NeuronSimple &neuron)
{
	t_VectorNeuronConnections::iterator begin;
	t_VectorNeuronConnections::iterator end;

	if (!isExistNeuron(neuron))
		throw (NeuronException(0, "The neuron is not exist in this neural network"));
	begin = this->connections.begin();
	end = this->connections.end();
	while (begin != end)
	{
		if (&begin->getNeuronFrom() == &neuron || &begin->getNeuronTo() == &neuron)
		{
			begin->getNeuronFrom().removeConnection(const_cast<NeuronConnection &>(*begin));
			begin->getNeuronTo().removeConnection(const_cast<NeuronConnection &>(*begin));
			this->connections.erase(begin);
			begin = this->connections.begin();
			end = this->connections.end();
			continue ;
		}
		begin++;
	}
}

bool	NeuronNetwork::isNeuronIn(NeuronSimple &neuron)
{
	try
	{
		(void)dynamic_cast<NeuronIn &>(neuron);
		return (true);
	}
	catch (std::bad_cast) {}
	return (false);
}

bool	NeuronNetwork::isNeuronDeep(NeuronSimple &neuron)
{
	try
	{
		(void)dynamic_cast<NeuronDeep &>(neuron);
		return (true);
	}
	catch (std::bad_cast) {}
	return (false);
}


bool	NeuronNetwork::isNeuronOut(NeuronSimple &neuron)
{
	try
	{
		(void)dynamic_cast<NeuronOut &>(neuron);
		return (true);
	}
	catch (std::bad_cast) {}
	return (false);
}

void	NeuronNetwork::disableAllNeurons()
{
	t_VectorToNeurons::iterator begin = this->neurons.begin();
	t_VectorToNeurons::iterator end = this->neurons.end();

	while (begin != end)
	{
		if (!isNeuronIn(**begin))
			(*begin)->setStatus(0);
		begin++;
	}
}

//TODO: optimize this method using and realizing method next->getAllConnections()
void	NeuronNetwork::computeNeuron(NeuronSimple *next, double resume)
{
	if (!isNeuronIn(*next))
		next->setStatus(next->getStatus() + resume);
	if (isNeuronOut(*next))
		return ;
	t_VectorNeuronConnections::iterator begin = this->connections.begin();
	t_VectorNeuronConnections::iterator end = this->connections.end();
	while (begin != end)
	{
		if (&begin->getNeuronFrom() == next)
			computeNeuron(&begin->getNeuronTo(), resume * begin->getWeight());
		begin++;
	}
}

void	NeuronNetwork::learnNeuron(NeuronSimple &neuron, double delta_weight)
{
	double delta_current_weight;
	NeuronConnection *currentConnection;
	t_VectorNeuronToConnections::iterator begin = neuron.getAllConnections().begin();
	t_VectorNeuronToConnections::iterator end = neuron.getAllConnections().end();

	while (begin != end)
	{
		currentConnection = dynamic_cast<NeuronConnection *>(*begin);
		if (&(currentConnection->getNeuronTo()) == &neuron)
		{
			delta_current_weight = delta_weight * currentConnection->getWeight() * currentConnection->getNeuronFrom().getStatus() * 0.1;
			currentConnection->setWeight(currentConnection->getWeight() + delta_current_weight);
			learnNeuron(currentConnection->getNeuronFrom(), delta_weight);
		}
		begin++;
	}
}

bool	NeuronNetwork::isExistNeuron(NeuronSimple &neuron)
{
	t_VectorToNeurons::iterator begin = this->neurons.begin();
	t_VectorToNeurons ::iterator end = this->neurons.end();

	while (begin != end)
	{
		if (*begin == &neuron)
			return (true);
		begin++;
	}
	return (false);
}

void	NeuronNetwork::addNeuron(NeuronSimple &neuron)
{
	if (isExistNeuron(neuron))
		throw (NeuronException(0, "The neuron already use in this neural network"));
	if (!neuron.isAvailable())
		throw (NeuronException(0, "This neuron already exist in another neural network"));
	neuron.setAvailable(false);
	this->neurons.insert(&neuron);
}

void	NeuronNetwork::removeNeuron(NeuronSimple &neuron)
{
	t_VectorToNeurons::iterator begin;
	t_VectorToNeurons::iterator end;

	if (neuron.isAvailable())
		throw (NeuronException(0, "The neuron does not use in this neural network"));
	begin = this->neurons.begin();
	end = this->neurons.end();
	while (begin != end)
	{
		if (*begin == &neuron)
		{
			removeAllConnections(**begin);
			(*begin)->setAvailable(true);
			this->neurons.erase(begin);
			return ;
		}
		begin++;
	}
	//Нейрон не найден
	throw (NeuronException(0, "The neuron does not use in this neural network"));
}

void	NeuronNetwork::createConnection(NeuronSimple &from, NeuronSimple &to, double weight)
{
	if (!isExistNeuron(from) || !isExistNeuron(to))
		throw (NeuronException(0, "The neuron(-s) is not in this neural network"));
	if (NeuronConnection::isAlreadyConnected(this->connections, from, to))
		throw (NeuronException(0, "This connection already exists"));
	if (isNeuronOut(from))
		throw (NeuronException(0, "Neuron FROM cannot be NeuronOut"));
	addConnection(from, to, weight);
}

size_t	NeuronNetwork::getCountNeurons()
{
	return (this->neurons.size());
}

size_t	NeuronNetwork::getCountConnections()
{
	return (this->connections.size());
}

void	NeuronNetwork::compute()
{
	t_VectorToNeurons::iterator begin = this->neurons.begin();
	t_VectorToNeurons::iterator end = this->neurons.end();

	disableAllNeurons();
	while (begin != end)
	{
		if (isNeuronIn(**begin))
			computeNeuron(*begin, (*begin)->getStatus());
		begin++;
	}
}

void	NeuronNetwork::learn()
{
	double delta;
	double delta_weight;
	NeuronSimple *currentNeuron;
	NeuronConnection *currentConnection;

	this->compute();
	t_VectorToNeurons::iterator begin = this->neurons.begin();
	t_VectorToNeurons::iterator end = this->neurons.end();
	while (begin != end)
	{
		currentNeuron = *begin;
		if (isNeuronOut(*currentNeuron))
		{
			delta = dynamic_cast<NeuronOut *>(currentNeuron)->getExpectedStatus() - currentNeuron->getStatus();
			t_VectorNeuronToConnections::iterator begin2 = currentNeuron->getAllConnections().begin();
			t_VectorNeuronToConnections::iterator end2 = currentNeuron->getAllConnections().end();
			while (begin2 != end2)
			{
				currentConnection = *begin2;
				delta_weight = delta * currentConnection->getWeight();
				currentConnection->setWeight(currentConnection->getWeight() + (delta_weight * 0.1));
				learnNeuron(currentConnection->getNeuronFrom(), delta_weight);
				begin2++;
			}
		}
		begin++;
	}
}
