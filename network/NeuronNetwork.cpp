//
// Created by Irena Mora on 1/4/22.
//

#include "NeuronNetwork.hpp"

void	NeuronNetwork::addConnection(NeuronSimple &from, NeuronDifficult &to, double weight)
{
	this->connections.push_back(NeuronConnection(from, to, weight));
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
	this->neurons.push_back(&neuron);
}

void	NeuronNetwork::removeNeuron(NeuronSimple &neuron)
{
	t_VectorToNeurons::iterator begin = this->neurons.begin();
	t_VectorToNeurons::iterator end = this->neurons.end();

	while (begin != end)
	{
		if (*begin == &neuron)
		{
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

size_t	NeuronNetwork::getCountConnections()
{
	return (this->connections.size());
}
