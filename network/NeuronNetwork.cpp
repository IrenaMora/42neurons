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

void	NeuronNetwork::addConnection(NeuronSimple &from, NeuronDifficult &to, double weight)
{
	t_VectorNeuronConnections::iterator current = this->connections.insert(NeuronConnection(from, to, weight)).first;
	from.addConnection(const_cast<NeuronConnection &>(*current));
	to.addConnection(const_cast<NeuronConnection &>(*current));
}

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

bool	NeuronNetwork::isNeuronSimple(NeuronSimple &neuron)
{
	try
	{
		(void)dynamic_cast<NeuronSimple &>(neuron);
		return (true);
	}
	catch (std::bad_cast) {}
	return (false);
}

bool	NeuronNetwork::isNeuronDifficult(NeuronSimple &neuron)
{
	try
	{
		(void)dynamic_cast<NeuronDifficult &>(neuron);
		return (true);
	}
	catch (std::bad_cast) {}
	return (false);
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
		if (isNeuronDifficult(**begin))
			(*begin)->setStatus(0);
		begin++;
	}
}

void	NeuronNetwork::computeNeuron(NeuronSimple *next, double resume)
{
	if (!isNeuronIn(*next))
	{
		cout << next->getStatus() << " * " << resume << endl;
		next->setStatus(next->getStatus() + resume);
	}
	if (isNeuronOut(*next))
		return ;
	t_VectorNeuronConnections::iterator begin = this->connections.begin();
	t_VectorNeuronConnections::iterator end = this->connections.end();
	while (begin != end)
	{
		if (&begin->getNeuronFrom() == next)
		{
			resume = resume * begin->getWeight();
			computeNeuron(&begin->getNeuronTo(), resume);
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

void	NeuronNetwork::createConnection(NeuronSimple &from, NeuronDifficult &to, double weight)
{
	if (!isExistNeuron(from) || !isExistNeuron(to))
		throw (NeuronException(0, "The neuron(-s) is not in this neural network"));
	if (NeuronConnection::isAlreadyConnected(this->connections, from, to))
		throw (NeuronException(0, "This connection already exists"));
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
