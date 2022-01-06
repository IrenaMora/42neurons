
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
	NeuronIn	in_first;
	NeuronDeep	deep_first;
	NeuronOut	out_first;
	NeuronNetwork *network = new NeuronNetwork();

	try{
		network->addNeuron(in_first);
		network->addNeuron(deep_first);
		network->addNeuron(out_first);
		network->createConnection(in_first, deep_first);
		network->createConnection(deep_first, out_first);
	}
	catch (NeuronException &e)
	{
		cout << e.getMessage() << endl;
	}

	cout << "Connections count: " << network->getCountConnections() << endl;
	delete (network);
}
