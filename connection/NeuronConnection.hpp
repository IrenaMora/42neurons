//
// Created by Irena Mora on 1/5/22.
//

#pragma once

#include "../interfaces/NeuronSimple.hpp"

class NeuronConnection
{
private:
	double			weight;
	NeuronSimple	*from;
	NeuronSimple	*to;
public:
	NeuronConnection(NeuronSimple &from, NeuronSimple &to, double weight = 0);
	double	getWeight() const;
	void	setWeight(double weight);
	NeuronSimple	&getNeuronFrom() const;
	void	setNeuronFrom(NeuronSimple &from);
	NeuronSimple	&getNeuronTo() const;
	void	setNeuronTo(NeuronSimple &to);
	static bool	isAlreadyConnected(t_VectorNeuronConnections &connections, NeuronSimple &from, NeuronSimple &to);
	friend bool	operator < (const NeuronConnection &first, const NeuronConnection &second);
};
