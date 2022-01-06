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
	std::cout << "Neurons: " << getCountNeurons() << endl;
	std::cout << "Connections: " << getCountConnections() << endl;
}

void	NeuronNetwork::addConnection(NeuronSimple &from, NeuronDifficult &to, double weight)
{
	t_VectorNeuronConnections::iterator begin;
	t_VectorNeuronConnections::iterator end;

	this->connections.insert(NeuronConnection(from, to, weight));
	begin = this->connections.begin();
	end = this->connections.end();
	while (begin != end)
	{
		if (&begin->getNeuronFrom() == &from && &begin->getNeuronTo() == &to)
		{
			from.addConnection(const_cast<NeuronConnection &>(*begin));
			to.addConnection(const_cast<NeuronConnection &>(*begin));
			return ;
		}
		begin++;
	}
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
		throw (NeuronException(0, "The neuron does not use in this neural network1"));
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
	throw (NeuronException(0, "The neuron does not use in this neural network2"));
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
