//
// Created by Irena Mora on 1/4/22.
//

#pragma once

#include <vector>

#include "NeuronIn.hpp"
#include "NeuronDeep.hpp"
#include "NeuronOut.hpp"
#include "NeuronException.hpp"
#include "NeuronFunctions.hpp"

class NeuronNetwork
{
public:
	void	setConnection(NeuronIn &in_neuron, NeuronOut &out_neuron);
};
