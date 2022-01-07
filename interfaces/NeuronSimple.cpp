//
// Created by Irena Mora on 1/4/22.
//

#include "NeuronSimple.hpp"

NeuronSimple::NeuronSimple(double status) : is_available(true)
{
	setStatus(status);
}

bool	NeuronSimple::isAvailable() const
{
	return (this->is_available);
}

void	NeuronSimple::setAvailable(bool is_available)
{
	this->is_available = is_available;
}

bool	NeuronSimple::isExistConnection(NeuronConnection &connection) const
{
	t_VectorNeuronToConnections::const_iterator begin = this->connections.cbegin(); 
	t_VectorNeuronToConnections::const_iterator end = this->connections.cend();

	while (begin != end)
	{
		if (*begin == &connection)
			return (true);
		begin++;
	}
	return (false);
}

void	NeuronSimple::addConnection(NeuronConnection &connection)
{
	if (isExistConnection(connection))
		throw (NeuronException(0, "This connection already exist"));
	this->connections.insert(&connection);
}

void	NeuronSimple::removeConnection(NeuronConnection &connection)
{
	t_VectorNeuronToConnections::iterator begin = this->connections.begin(); 
	t_VectorNeuronToConnections::iterator end = this->connections.end();

	while (begin != end)
	{
		if (*begin == &connection)
		{
			this->connections.erase(begin);
			return ;
		}
		begin++;
	}
	throw (NeuronException(0, "This connection is not exist"));
}

double	NeuronSimple::getStatus() const
{
	return (this->status);
}

void	NeuronSimple::setStatus(double status)
{
	this->status = status;
}

size_t	NeuronSimple::getCountConnections()
{
	return (this->connections.size());
}
