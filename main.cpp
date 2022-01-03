#include <iostream>

#include "NeuronInput.hpp"
#include "NeuronOutput.hpp"
#include "NeuronNetwork.hpp"

using namespace std;

int	main()
{
	NeuronInput first;
	NeuronInput second;
	NeuronInput third;
	NeuronOutput out;
	NeuronNetwork network;

	network.addNeuronInput(first);
	network.addNeuronInput(second);
	network.addNeuronInput(third);
	network.addNeuronOutput(out);

	network.setConnection(first, out);
	network.setConnection(second, out);
	network.setConnection(third, out);

	cout << "Input count: " << network.countNeuronInput() << endl;
	cout << "Output count: " << network.countNeuronOutput() << endl;
	cout << "Neuron connections: " << network.countNeuronConnection() << endl;

}
