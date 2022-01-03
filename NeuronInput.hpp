//
// Created by Irena Mora on 1/3/22.
//

#pragma once

#include <vector>
#include <iostream>
#include "Neuron.hpp"
#include "NeuronOutput.hpp"

using namespace std;

class NeuronInput : public Neuron
{
private:
	vector<NeuronOutput *> next_neurons;
private:
	size_t	countNeuronNext() const;
	void	addNeuronNext(NeuronOutput &neuron);
	void	removeNeuronNext(NeuronOutput &neuron);
	void	clearNeuronNext();
public:
	NeuronInput(float power = 0, bool status = false);
	friend class NeuronNetwork;
};
