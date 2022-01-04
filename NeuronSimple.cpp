//
// Created by Irena Mora on 1/4/22.
//

#include "NeuronSimple.hpp"

NeuronSimple::NeuronSimple(double status) : status(status) {}

double	NeuronSimple::getStatus() const
{
	return (this->status);
}

void	NeuronSimple::setStatus(double status)
{
	this->status = status;
}
