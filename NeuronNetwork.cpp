//
// Created by Irena Mora on 1/4/22.
//

#include "NeuronNetwork.hpp"

void	NeuronNetwork::setConnection(NeuronIn &in_neuron, NeuronOut &out_neuron)
{
	if (!in_neuron.isAvailable() || !out_neuron.isAvailable())
		throw (NeuronException(4, "The neuron already use in some neural network"));
}
