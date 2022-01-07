//
// Created by Irena Mora on 1/4/22.
//

#pragma once

#include "../neurons/NeuronIn.hpp"
#include "../neurons/NeuronDeep.hpp"
#include "../neurons/NeuronOut.hpp"
#include "../exceptions/NeuronException.hpp"
#include "../base/NeuronBase.hpp"
#include "../connection/NeuronConnection.hpp"

class NeuronNetwork
{
private:
	t_VectorToNeurons	neurons;
	t_VectorNeuronConnections	connections;
private:
	void	addConnection(NeuronSimple &from, NeuronDifficult &to, double weight = 0);
	void	removeAllConnections(NeuronSimple &neuron);
	bool	isNeuronSimple(NeuronSimple &neuron);
	bool	isNeuronDifficult(NeuronSimple &neuron);
	bool	isNeuronIn(NeuronSimple &neuron);
	bool	isNeuronDeep(NeuronSimple &neuron);
	bool	isNeuronOut(NeuronSimple &neuron);
	void	disableAllNeurons();
	void	computeNeuron(NeuronSimple *next, double resume);
public:
	~NeuronNetwork();
	bool	isExistNeuron(NeuronSimple &neuron);
	void	addNeuron(NeuronSimple &neuron);
	void	removeNeuron(NeuronSimple &neuron);
	void	createConnection(NeuronSimple &from, NeuronDifficult &to, double weight = 0);
	size_t	getCountNeurons();
	size_t	getCountConnections();
	void	compute();
};