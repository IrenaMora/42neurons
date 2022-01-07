
//
// Created by Irena Mora on 1/4/22.
//
//#include ".hpp"

#include <iostream>
#include <set>
#include "network/NeuronNetwork.hpp"
#include "neurons/NeuronIn.hpp"
#include "neurons/NeuronDeep.hpp"
#include "neurons/NeuronOut.hpp"
#include "exceptions/NeuronException.hpp"

using namespace std;

int	main()
{
	NeuronIn	in_first(0.5);
	NeuronIn	in_second(0.8);
	NeuronDeep	deep_first;
	NeuronDeep	deep_second;
	NeuronOut	out_first;
	NeuronNetwork *network = new NeuronNetwork();

	try{
		network->addNeuron(in_first);
		network->addNeuron(in_second);
		network->addNeuron(deep_first);
		network->addNeuron(deep_second);
		network->addNeuron(out_first);
		network->createConnection(in_first, deep_first, 0.5);
		network->createConnection(in_second, deep_first, 0.7);
		network->createConnection(in_first, deep_second, 0.2);
		network->createConnection(in_second, deep_second, 0.9);
		network->createConnection(deep_first, out_first, 2);
		network->createConnection(deep_second, out_first, 3);
	}
	catch (NeuronException &e)
	{
		cout << e.getMessage() << endl;
	}

	network->compute();
	cout << endl;
	cout << in_first.status << endl;
	cout << in_second.status << endl;
	cout << deep_first.status << endl;
	cout << deep_second.status << endl;
	cout << out_first.status << endl;
	cout << endl;
	cout << "Connections count: " << network->getCountConnections() << endl;
	delete (network);
}
