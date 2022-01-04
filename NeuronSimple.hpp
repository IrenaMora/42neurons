//
// Created by Irena Mora on 1/4/22.
//

#pragma once

#include "NeuronException.hpp"

#include <iostream>
#include <vector>
#include "NeuronFunctions.hpp"

using namespace std;

class NeuronNetwork;

class NeuronSimple
{
private:
	double	status;
	bool	is_available;
	t_NeuronList next_neurons;
	t_NeuronList previous_neurons;
private:
	bool	isAvailable() const;
	void	setAvailable(bool is_available);
	void	addNextNeuron(NeuronSimple &neuron, double weight = 0);
	void	removeNextNeuron(NeuronSimple &neuron);
	void	addPreviousNeuron(NeuronSimple &neuron, double weight = 0);
	void	removePreviousNeuron(NeuronSimple &neuron);
public:
	NeuronSimple(double status = 0);
	double	getStatus() const;
	void	setStatus(double status);
	friend class NeuronNetwork;
};
