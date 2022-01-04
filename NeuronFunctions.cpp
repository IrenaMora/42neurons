//
// Created by Irena Mora on 1/4/22.
//

#include "NeuronFunctions.hpp"

bool	NeuronFunctions::isExistNeuron(t_NeuronList &neuronList, NeuronSimple &neuron)
{
	t_NeuronList::const_iterator begin = neuronList.cbegin();
	t_NeuronList::const_iterator end = neuronList.cend();

	while (begin != end)
	{
		if (begin->second == &neuron)
			return (true);
		begin++;
	}
	return (false);
}

void	NeuronFunctions::addNeuronToList(t_NeuronList &neuronList, NeuronSimple &neuron, double weight)
{
	if (NeuronFunctions::isExistNeuron(neuronList, neuron))
		throw (NeuronException(2, "The neuron already was connected")); //TODO: is error corrent?
	neuronList.push_back(make_pair(weight, &neuron));
}

void	NeuronFunctions::removeNeuronFromList(t_NeuronList &neuronList, NeuronSimple &neuron)
{
	if (!NeuronFunctions::isExistNeuron(neuronList, neuron))
		throw (NeuronException(3, "The neuron is not connected")); //TODO: is error corrent?
	t_NeuronList::iterator begin = neuronList.begin();
	t_NeuronList::iterator end = neuronList.end();

	while (begin != end)
	{
		if (begin->second == &neuron)
		{
			neuronList.erase(begin);
			return ;
		}
		begin++;
	}
}
