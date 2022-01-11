//
// Created by Irena Mora on 1/5/22.
//

#include "NeuronConnection.hpp"

NeuronConnection::NeuronConnection(NeuronSimple &from, NeuronSimple &to, double learning_rate, double weight) : from(&from), to(&to), learning_rate(learning_rate), weight(weight) {}

double	NeuronConnection::getWeight() const
{
	return (this->weight);
}

void	NeuronConnection::setWeight(double weight)
{
	this->weight = weight;
}

double	NeuronConnection::getLearningRate() const
{
	return (this->learning_rate);
}

void	NeuronConnection::setLearningRate(double learning_rate)
{
	this->learning_rate = learning_rate;
}

NeuronSimple	&NeuronConnection::getNeuronFrom() const
{
	return (*this->from);
}

void	NeuronConnection::setNeuronFrom(NeuronSimple &from)
{
	this->from = &from;
}

NeuronSimple	&NeuronConnection::getNeuronTo() const
{
	return (*this->to);
}

void	NeuronConnection::setNeuronTo(NeuronSimple &to)
{
	this->to = &to;
}

bool	NeuronConnection::isAlreadyConnected(t_VectorNeuronConnections &connections, NeuronSimple &from, NeuronSimple &to)
{
	t_VectorNeuronConnections::const_iterator begin = connections.cbegin();
	t_VectorNeuronConnections::const_iterator end = connections.cend();

	while (begin != end)
	{
		if (&begin->getNeuronFrom() == &from && &begin->getNeuronTo() == &to)
			return (true);
		begin++;
	}
	return (false);
}

bool	operator < (const NeuronConnection &first, const NeuronConnection &second)
{
	return (&first < &second);
}
