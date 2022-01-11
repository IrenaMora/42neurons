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

void	NeuronNetwork::addConnection(NeuronSimple &from, NeuronSimple &to, double learning_rate, double weight)
{
	t_VectorNeuronConnections::iterator current = this->connections.insert(NeuronConnection(from, to, learning_rate, weight)).first;
	from.addConnection(const_cast<NeuronConnection &>(*current));
	to.addConnection(const_cast<NeuronConnection &>(*current));
}

//TODO: optimize this method using and realizing method neuron.getAllConnectionsFrom() and neuron.getAllConnectionsTo()
void	NeuronNetwork::removeAllConnections(NeuronSimple &neuron)
{
	NeuronConnection *currentConnection;

	if (!isExistNeuron(neuron))
		throw (NeuronException(0, "The neuron is not exist in this neural network"));
	t_VectorNeuronToConnections::iterator begin = neuron.getAllConnections().begin();
	t_VectorNeuronToConnections::iterator end = neuron.getAllConnections().end();
	while (begin != end)
	{
		currentConnection = *begin;
		if (&currentConnection->getNeuronFrom() == &neuron || &currentConnection->getNeuronTo() == &neuron)
		{
			currentConnection->getNeuronFrom().removeConnection(const_cast<NeuronConnection &>(*currentConnection));
			currentConnection->getNeuronTo().removeConnection(const_cast<NeuronConnection &>(*currentConnection));
			this->connections.erase(*currentConnection);
			begin = neuron.getAllConnections().begin();
			end = neuron.getAllConnections().end();
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

//TODO: optimize this method using and realizing method neuron.getAllConnectionsFrom() and neuron.getAllConnectionsTo()
void	NeuronNetwork::computeNeuron(NeuronSimple *next, double resume)
{
	NeuronConnection *currentConnection;

	if (!isNeuronIn(*next))
		next->setStatus(next->getStatus() + resume);
	if (isNeuronOut(*next))
		return ;
	t_VectorNeuronToConnections::iterator begin = next->getAllConnections().begin();
	t_VectorNeuronToConnections::iterator end = next->getAllConnections().end();
	while (begin != end)
	{
		currentConnection = *begin;
		if (&currentConnection->getNeuronFrom() == next)
			computeNeuron(&currentConnection->getNeuronTo(), resume * currentConnection->getWeight());
		begin++;
	}
}

void	NeuronNetwork::learnNeuron(NeuronSimple &neuron, double sigma_weight)
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
			delta_current_weight = sigma_weight * currentConnection->getWeight() * currentConnection->getNeuronFrom().getStatus() * currentConnection->getLearningRate();
			currentConnection->setWeight(currentConnection->getWeight() + delta_current_weight);
			learnNeuron(currentConnection->getNeuronFrom(), sigma_weight);
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

void	NeuronNetwork::addNeurons(vector<NeuronIn> &neurons)
{
	vector<NeuronIn>::iterator begin = neurons.begin();
	vector<NeuronIn>::iterator end = neurons.end();

	while (begin != end)
	{
		addNeuron(*begin);
		begin++;
	}
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

void	NeuronNetwork::createConnection(NeuronSimple &from, NeuronSimple &to, double learning_rate, double weight)
{
	if (!isExistNeuron(from) || !isExistNeuron(to))
		throw (NeuronException(0, "The neuron(-s) is not in this neural network"));
	if (NeuronConnection::isAlreadyConnected(this->connections, from, to))
		throw (NeuronException(0, "This connection already exists"));
	if (isNeuronOut(from))
		throw (NeuronException(0, "Neuron FROM cannot be NeuronOut"));
	addConnection(from, to, learning_rate, weight);
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
	double sigma_weight;
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
				sigma_weight = delta * currentConnection->getWeight();
				currentConnection->setWeight(currentConnection->getWeight() + (sigma_weight * currentConnection->getLearningRate()));
				learnNeuron(currentConnection->getNeuronFrom(), sigma_weight);
				begin2++;
			}
		}
		begin++;
	}
}
