//
// Created by Irena Mora on 1/3/22.
//

#pragma once

#include <vector> //TODO: use set
#include <iostream>
#include "NeuronInput.hpp"
#include "NeuronOutput.hpp"

using namespace std;

class NeuronNetwork
{
private:
	vector<NeuronInput *> input_neurons;
	vector<NeuronOutput *> output_neurons;
private:
	bool	isExistNeuron(NeuronInput &neuron);
	bool	isExistNeuron(NeuronOutput &neuron);
public:
	size_t	countNeuronInput() const;
	void	addNeuronInput(NeuronInput &neuron);
	void	removeNeuronInput(NeuronInput &neuron);
	size_t	countNeuronOutput() const;
	void	addNeuronOutput(NeuronOutput &neuron);
	void	removeNeuronOutput(NeuronOutput &neuron);
	void	setConnection(NeuronInput &neuronIn, NeuronOutput &neuronOut);
	void	removeConnection(NeuronInput &neuronIn, NeuronOutput &neuronOut);
	size_t	countNeuronConnection() const;
	void	learn(bool result);
};
