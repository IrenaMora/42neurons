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

void	NeuronSimple::addNextNeuron(NeuronSimple &neuron, double weight)
{
	NeuronFunctions::addNeuronToList(this->next_neurons, neuron, weight);
}

void	NeuronSimple::removeNextNeuron(NeuronSimple &neuron)
{
	NeuronFunctions::removeNeuronFromList(this->next_neurons, neuron);
}

void	NeuronSimple::addPreviousNeuron(NeuronSimple &neuron, double weight)
{
	NeuronFunctions::addNeuronToList(this->previous_neurons, neuron, weight);
}

void	NeuronSimple::removePreviousNeuron(NeuronSimple &neuron)
{
	NeuronFunctions::removeNeuronFromList(this->previous_neurons, neuron);
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
