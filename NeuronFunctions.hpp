//
// Created by Irena Mora on 1/4/22.
//

#pragma once

#include <vector>
#include "NeuronException.hpp"

using namespace std;

class NeuronSimple;
typedef vector< pair<float, NeuronSimple *> > t_NeuronList;

class NeuronFunctions
{
public:
	static bool	isExistNeuron(t_NeuronList &neuronList, NeuronSimple &neuron);
	static void	addNeuronToList(t_NeuronList &neuronList, NeuronSimple &neuron, double weight);
	static void	removeNeuronFromList(t_NeuronList &neuronList, NeuronSimple &neuron);
};
