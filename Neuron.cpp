//
// Created by Irena Mora on 1/3/22.
//

#include "Neuron.hpp"

bool	Neuron::isAvailable() const
{
	return (is_available);
}

void	Neuron::setAvailable(bool is_available)
{
	this->is_available = is_available;
}

Neuron::Neuron(float power, bool status) : power(power), status(status), is_available(true) {}

float	Neuron::getPower() const
{
	return (power);
}

void	Neuron::setPower(float power)
{
	this->power = power;
}

bool	Neuron::getStatus() const
{
	return (status);
}

void	Neuron::setStatus(bool status)
{
	this->status = status;
}

float	Neuron::getOutPower() const
{
	if (!status)
		return (false);
	return (power);
}
