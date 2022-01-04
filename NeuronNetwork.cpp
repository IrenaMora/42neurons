//
// Created by Irena Mora on 1/4/22.
//

#include "NeuronNetwork.hpp"

void	NeuronNetwork::setConnection(NeuronIn &in_neuron, NeuronOut &out_neuron, double weight)
{
	if (!in_neuron.isAvailable() || !out_neuron.isAvailable())
		throw (NeuronException(4, "The neuron already use in some neural network"));
	in_neuron.addNextNeuron(out_neuron, weight);
	out_neuron.addPreviousNeuron(in_neuron, weight);
}
