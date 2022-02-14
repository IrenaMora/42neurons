//
// Created by Irena Mora on 1/4/22.
//

#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "NeuronIn.hpp"
#include "NeuronDeep.hpp"
#include "NeuronOut.hpp"
#include "NeuronException.hpp"
#include "NeuronBase.hpp"
#include "NeuronFunctions.hpp"
#include "NeuronConnection.hpp"

class NeuronNetwork
{
private:
	t_SetToNeurons neurons;
	t_SetNeuronConnections connections;

private:
	void addConnection(NeuronSimple &from, NeuronSimple &to, FunctionType function_type, double learning_rate, double weight);
	void removeAllConnections(NeuronSimple &neuron);
	bool isNeuronIn(NeuronSimple &neuron);
	bool isNeuronDeep(NeuronSimple &neuron);
	bool isNeuronOut(NeuronSimple &neuron);
	void disableAllNeurons();
	void computeNeuron(NeuronSimple *next, double resume);
	void learnNeuron(NeuronSimple &neuron, double sigma_weight);

public:
	bool isExistNeuron(NeuronSimple &neuron);
	void addNeuron(NeuronSimple &neuron);
	template<typename T>
	void addNeurons(T &container_neurons)
	{
		typename T::iterator begin = container_neurons.begin();
		typename T::iterator end = container_neurons.end();

		while (begin != end)
		{
			addNeuron(*begin);
			begin++;
		}
	}
	void removeNeuron(NeuronSimple &neuron);
	void createConnection(NeuronSimple &from, NeuronSimple &to, FunctionType function_type, double learning_rate);
	void createConnection(NeuronSimple &from, NeuronSimple &to, FunctionType function_type, double learning_rate, double weight);
	size_t getCountNeurons();
	size_t getCountConnections();
	void compute();
	void learn();

	void saveNetwork(const std::string & = "network");
	void loadNetwork(std::vector<std::unique_ptr<NeuronSimple>> &, const std::string & = "network");
};
