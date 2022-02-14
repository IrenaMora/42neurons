//
// Created by Irena Mora on 1/5/22.
//

#pragma once

#include "NeuronBase.hpp"
#include "NeuronSimple.hpp"

class NeuronConnection
{
private:
    NeuronSimple	*from;
    NeuronSimple	*to;
    FunctionType	function_type;
    double			learning_rate;
	double			weight;
public:
	NeuronConnection(NeuronSimple &from, NeuronSimple &to, FunctionType function_type, double learning_rate, double weight);
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
	static bool	isAlreadyConnected(t_SetNeuronConnections &connections, NeuronSimple &from, NeuronSimple &to);
	friend bool	operator < (const NeuronConnection &first, const NeuronConnection &second);
};
