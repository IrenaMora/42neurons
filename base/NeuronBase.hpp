//
// Created by Irena Mora on 1/5/22.
//

#pragma once

class NeuronSimple;
class NeuronConnection;

#include <set>

typedef set<NeuronSimple *> t_VectorToNeurons;
typedef set<NeuronConnection> t_VectorNeuronConnections;
typedef set<NeuronConnection *> t_VectorNeuronToConnections;
