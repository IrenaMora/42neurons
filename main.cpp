
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

// int	main()
// {
// 	NeuronIn	in_first(0.5);
// 	NeuronIn	in_second(0.8);
// 	NeuronIn	in_third(0.2);
// 	NeuronDeep	deep_first;
// 	NeuronDeep	deep_second;
// 	NeuronOut	out_first;
// 	NeuronNetwork *network = new NeuronNetwork();

// 	try{
// 		network->addNeuron(in_first);
// 		network->addNeuron(in_second);
// 		network->addNeuron(in_third);
// 		network->addNeuron(deep_first);
// 		network->addNeuron(deep_second);
// 		network->addNeuron(out_first);
// 		network->createConnection(in_first, deep_first, 0.5);
// 		network->createConnection(in_second, deep_first, 0.7);
// 		network->createConnection(in_third, deep_first, 0.6);
// 		network->createConnection(in_first, deep_second, 0.2);
// 		network->createConnection(in_second, deep_second, 0.9);
// 		network->createConnection(in_third, deep_second, 0.8);
// 		network->createConnection(deep_first, out_first, 2);
// 		network->createConnection(deep_second, out_first, 3);
// 	}
// 	catch (NeuronException &e)
// 	{
// 		cout << e.getMessage() << endl;
// 	}

// 	network->compute();
// 	cout << "Out neuron: " << out_first.getStatus() << endl;
// 	cout << "Connections count: " << network->getCountConnections() << endl;
// 	delete (network);
// }

int	main()
{
	NeuronIn	in_first(1);
	NeuronIn	in_second(2);
	NeuronDeep	deep_first;
	NeuronDeep	deep_second;
	NeuronDeep	deep_third;
	NeuronOut	out_first;
	NeuronNetwork *network = new NeuronNetwork();

	out_first.setExpectedStatus(0.5);
	try{
		network->addNeuron(in_first);
		network->addNeuron(in_second);
		network->addNeuron(deep_first);
		network->addNeuron(deep_second);
		network->addNeuron(deep_third);
		network->addNeuron(out_first);
		network->createConnection(in_first, deep_first, 1);
		network->createConnection(in_second, deep_first, 1);
		network->createConnection(deep_first, deep_second, 2);
		network->createConnection(deep_first, deep_third, 2);
		network->createConnection(deep_second, out_first, 0.25);
		network->createConnection(deep_third, out_first, 0.25);
	}
	catch (NeuronException &e)
	{
		cout << e.getMessage() << endl;
	}

	network->compute();
	cout << "Out status: " << out_first.getStatus() << endl;
	cout << "Expected status: " << out_first.getExpectedStatus() << endl << endl;
	for (int i = 1; i < 1000; i++)
	{
		network->learn();
		network->compute();
	}

	cout << "Out status past learn: " << out_first.getStatus() << endl;
	cout << "Expected status past learn: " << out_first.getExpectedStatus() << endl << endl;

	cout << "Connections count: " << network->getCountConnections() << endl;
	delete (network);
}
