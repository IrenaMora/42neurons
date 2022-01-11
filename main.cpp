
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

#include <sys/time.h>

using namespace std;

// int	main()
// {
// 	NeuronIn	in_first(1);
// 	NeuronIn	in_second(2);
// 	NeuronDeep	deep_first;
// 	NeuronDeep	deep_second;
// 	NeuronDeep	deep_third;
// 	NeuronOut	out_first;
// 	NeuronNetwork *network = new NeuronNetwork();

// 	out_first.setExpectedStatus(0.5);
// 	try{
// 		network->addNeuron(in_first);
// 		network->addNeuron(in_second);
// 		network->addNeuron(deep_first);
// 		network->addNeuron(deep_second);
// 		network->addNeuron(deep_third);
// 		network->addNeuron(out_first);
// 		network->createConnection(in_first, deep_first, 0.1, 1);
// 		network->createConnection(in_second, deep_first, 0.1, 1);
// 		network->createConnection(deep_first, deep_second, 0.1, 2);
// 		network->createConnection(deep_first, deep_third, 0.1, 2);
// 		network->createConnection(deep_second, out_first, 0.1, 0.25);
// 		network->createConnection(deep_third, out_first, 0.1, 0.25);
// 	}
// 	catch (NeuronException &e)
// 	{
// 		cout << e.getMessage() << endl;
// 	}

// 	network->compute();
// 	cout << "Out status: " << out_first.getStatus() << endl;
// 	cout << "Expected status: " << out_first.getExpectedStatus() << endl << endl;
// 	for (int i = 1; i < 100; i++)
// 	{
// 		network->learn();
// 		network->compute();
// 	}

// 	cout << "Out status past learn: " << out_first.getStatus() << endl;
// 	cout << "Expected status past learn: " << out_first.getExpectedStatus() << endl << endl;

// 	cout << "Connections count: " << network->getCountConnections() << endl;
// 	delete (network);
// }

int getRandom()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	srand(time.tv_sec * time.tv_usec);
	return (rand() % 100);
}

int	main()
{
	NeuronIn	in_first;
	NeuronIn	in_second(1.0);
	NeuronOut	out_first;
	NeuronNetwork *network = new NeuronNetwork();

	try{
		network->addNeuron(in_first);
		network->addNeuron(in_second);
		network->addNeuron(out_first);
		network->createConnection(in_first, out_first, 0.001);
		network->createConnection(in_second, out_first, 0.001);
	}
	catch (NeuronException &e)
	{
		cout << e.getMessage() << endl;
	}

	for (int i = 1; i < 100000; i++)
	{
		int rand = getRandom();
		in_first.setStatus(rand);
		out_first.setExpectedStatus(rand + 10.000);
		network->learn();
		network->compute();
		cout << "Learning №" << i + 1 << ". Expected " << out_first.getExpectedStatus() << ", result " << out_first.getStatus() << endl;
	}

	while (1)
	{
		string line;
		cout << "Write value:" << endl;
		getline(cin, line);
		int value = std::stoi(line);
		in_first.setStatus(value);
		network->compute();
		cout << "Your result: " << out_first.getStatus() << endl;
	}

	delete (network);
}
