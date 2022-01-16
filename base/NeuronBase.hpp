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


typedef set<NeuronSimple *> t_SetToNeurons;
typedef set<NeuronConnection> t_SetNeuronConnections;
typedef set<NeuronConnection *> t_SetNeuronToConnections;
