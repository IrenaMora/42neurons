//
// Created by Irena Mora on 1/3/22.
//

#include "NeuronInput.hpp"

NeuronInput::NeuronInput(float power, bool status) : Neuron(power, status) {}

size_t	NeuronInput::countNeuronNext() const
{
	return (next_neurons.size());
}

void	NeuronInput::addNeuronNext(NeuronOutput &neuron)
{
	vector<NeuronOutput *>::iterator position = std::find(next_neurons.begin(), next_neurons.end(), &neuron);
	if (position == next_neurons.end())
		next_neurons.push_back(&neuron);
}

void	NeuronInput::removeNeuronNext(NeuronOutput &neuron)
{
	vector<NeuronOutput *>::iterator position = std::find(next_neurons.begin(), next_neurons.end(), &neuron);
	if (position == next_neurons.end())
		return ;
	next_neurons.erase(position);
}

void	NeuronInput::clearNeuronNext()
{
	this->next_neurons.clear();
}
