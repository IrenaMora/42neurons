//
// Created by Irena Mora on 1/5/22.
//

#pragma once

#include <set>

using namespace std;

enum FunctionType
{
	SIGMOID,
	RELU
};

class NeuronSimple;
class NeuronConnection;


typedef set<NeuronSimple *> t_VectorToNeurons;
typedef set<NeuronConnection> t_VectorNeuronConnections;
typedef set<NeuronConnection *> t_VectorNeuronToConnections;
