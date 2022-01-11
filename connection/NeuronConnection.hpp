//
// Created by Irena Mora on 1/5/22.
//

#pragma once

#include "../base/NeuronBase.hpp"
#include "../interfaces/NeuronSimple.hpp"

class NeuronConnection
{
private:
	double			weight;
	double			learning_rate;
	FunctionType	function_type;
	NeuronSimple	*from;
	NeuronSimple	*to;
public:
	NeuronConnection(NeuronSimple &from, NeuronSimple &to, FunctionType function_type, double learning_rate, double weight = 0.5);
	double	getWeight() const;
	void	setWeight(double weight);
	double	getLearningRate() const;
	void	setLearningRate(double learning_rate);
	FunctionType	getFunctionType() const;
	void	setFunctionType(FunctionType function_type);
	NeuronSimple	&getNeuronFrom() const;
	void	setNeuronFrom(NeuronSimple &from);
	NeuronSimple	&getNeuronTo() const;
	void	setNeuronTo(NeuronSimple &to);
	static bool	isAlreadyConnected(t_VectorNeuronConnections &connections, NeuronSimple &from, NeuronSimple &to);
	friend bool	operator < (const NeuronConnection &first, const NeuronConnection &second);
};
