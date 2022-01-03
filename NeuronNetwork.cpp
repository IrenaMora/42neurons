//
// Created by Irena Mora on 1/3/22.
//

#include "NeuronNetwork.hpp"

bool	NeuronNetwork::isExistNeuron(NeuronInput &neuron)
{
	vector<NeuronInput *>::iterator position = std::find(input_neurons.begin(), input_neurons.end(), &neuron);
	if (position == input_neurons.end())
		return (false);
	return (true);
}

bool	NeuronNetwork::isExistNeuron(NeuronOutput &neuron)
{
	vector<NeuronOutput *>::iterator position = std::find(output_neurons.begin(), output_neurons.end(), &neuron);
	if (position == output_neurons.end())
		return (false);
	return (true);
}

size_t	NeuronNetwork::countNeuronInput() const
{
	return (input_neurons.size());
}

void	NeuronNetwork::addNeuronInput(NeuronInput &neuron)
{
	if (!neuron.isAvailable())
		return ;
	vector<NeuronInput *>::iterator position = std::find(input_neurons.begin(), input_neurons.end(), &neuron);
	if (position == input_neurons.end())
		input_neurons.push_back(&neuron);
	neuron.setAvailable(false);
}

void	NeuronNetwork::removeNeuronInput(NeuronInput &neuron)
{
	vector<NeuronInput *>::iterator position = std::find(input_neurons.begin(), input_neurons.end(), &neuron);
	if (position == input_neurons.end())
		return ;
	input_neurons.erase(position);
	neuron.setAvailable(true);
	neuron.clearNeuronNext();
}

size_t	NeuronNetwork::countNeuronOutput() const
{
	return (output_neurons.size());
}

void	NeuronNetwork::addNeuronOutput(NeuronOutput &neuron)
{
	if (!neuron.isAvailable())
		return ;
	vector<NeuronOutput *>::iterator position = std::find(output_neurons.begin(), output_neurons.end(), &neuron);
	if (position == output_neurons.end())
		output_neurons.push_back(&neuron);
	neuron.setAvailable(false);
}

void	NeuronNetwork::removeNeuronOutput(NeuronOutput &neuron)
{
	vector<NeuronOutput *>::iterator position = std::find(output_neurons.begin(), output_neurons.end(), &neuron);
	if (position == output_neurons.end())
		return ;
	output_neurons.erase(position);
	neuron.setAvailable(true);
}

void	NeuronNetwork::setConnection(NeuronInput &neuronIn, NeuronOutput &neuronOut)
{
	if (!isExistNeuron(neuronIn) || !isExistNeuron(neuronOut))
		return ;
	neuronIn.addNeuronNext(neuronOut);
}

void	NeuronNetwork::removeConnection(NeuronInput &neuronIn, NeuronOutput &neuronOut)
{
	if (!isExistNeuron(neuronIn) || !isExistNeuron(neuronOut))
		return ;
	neuronIn.removeNeuronNext(neuronOut);
}

size_t	NeuronNetwork::countNeuronConnection() const
{
	size_t	count = 0;
	vector<NeuronInput *>::const_iterator begin = input_neurons.cbegin();
	vector<NeuronInput *>::const_iterator end = input_neurons.cend();

	while (begin != end)
	{
		count += (*begin)->countNeuronNext();
		begin++;
	}
	return (count);
}
