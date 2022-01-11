//
// Created by Irena Mora on 1/4/22.
//

#pragma once

#include <vector>
#include "../neurons/NeuronIn.hpp"
#include "../neurons/NeuronDeep.hpp"
#include "../neurons/NeuronOut.hpp"
#include "../exceptions/NeuronException.hpp"
#include "../base/NeuronBase.hpp"
#include "../base/NeuronFunctions.hpp"
#include "../connection/NeuronConnection.hpp"

class NeuronNetwork
{
private:
	t_VectorToNeurons	neurons;
	t_VectorNeuronConnections	connections;
private:
	void	addConnection(NeuronSimple &from, NeuronSimple &to, double learning_rate, double weight = 0.5);
	void	removeAllConnections(NeuronSimple &neuron);
	bool	isNeuronIn(NeuronSimple &neuron);
	bool	isNeuronDeep(NeuronSimple &neuron);
	bool	isNeuronOut(NeuronSimple &neuron);
	void	disableAllNeurons();
	void	computeNeuron(NeuronSimple *next, double resume);
	void	learnNeuron(NeuronSimple &neuron, double sigma_weight);
public:
	~NeuronNetwork();
	bool	isExistNeuron(NeuronSimple &neuron);
	void	addNeuron(NeuronSimple &neuron);
	void	addNeurons(vector<NeuronIn> &neurons);
	void	removeNeuron(NeuronSimple &neuron);
	void	createConnection(NeuronSimple &from, NeuronSimple &to, double learning_rate, double weight = 0.5);
	size_t	getCountNeurons();
	size_t	getCountConnections();
	void	compute();
	void	learn();
};
