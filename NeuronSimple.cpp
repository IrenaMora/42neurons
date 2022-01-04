//
// Created by Irena Mora on 1/4/22.
//

#include "NeuronSimple.hpp"

NeuronSimple::NeuronSimple(double status)
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

double	NeuronSimple::getStatus() const
{
	return (this->status);
}

void	NeuronSimple::setStatus(double status)
{
	if (status < 0.0 || status > 1.0)
		throw (NeuronException(1, "The status cannot be less than 0 or more than 1"));
	this->status = status;
}
