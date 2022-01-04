//
// Created by Irena Mora on 1/4/22.
//

//#include ".hpp"

#include <iostream>
#include "NeuronIn.hpp"
#include "NeuronDeep.hpp"
#include "NeuronOut.hpp"
#include "NeuronException.hpp"

using namespace std;

int	main()
{
	try
	{
		NeuronIn	in_first;
		NeuronDeep	deep_first;
		NeuronOut	out_first;

	}
	catch (NeuronException &e) { cout << e.getMessage() << endl; }
}
