//
// Created by Irena Mora on 1/5/22.
//

#pragma once

#include "../interfaces/NeuronSimple.hpp"
#include "../interfaces/NeuronDifficult.hpp"

class NeuronConnection
{
private:
	double			weight;
	NeuronSimple	*from;
	NeuronDifficult	*to;
public:
	NeuronConnection(NeuronSimple &from, NeuronDifficult &to, double weight = 0);
	double	getWeight() const;
	void	setWeight(double weight);
	NeuronSimple	&getNeuronFrom() const;
	void	setNeuronFrom(NeuronSimple &from);
	NeuronDifficult	&getNeuronTo() const;
	void	setNeuronTo(NeuronDifficult &to);
	static bool	isAlreadyConnected(t_VectorNeuronConnections &connections, NeuronSimple &from, NeuronDifficult &to);
	friend bool	operator < (const NeuronConnection &first, const NeuronConnection &second);
};
