//
// Created by Irena Mora on 1/4/22.
//

#pragma once

#include "../exceptions/NeuronException.hpp"

#include <iostream>
#include "../base/NeuronBase.hpp"

using namespace std;

class NeuronNetwork;

class NeuronSimple
{
private:
	double	status;
	bool	is_available;
	t_VectorNeuronToConnections connections;
private:
	bool	isAvailable() const;
	void	setAvailable(bool is_available);
	bool	isExistConnection(NeuronConnection &connection) const;
	void	addConnection(NeuronConnection &connection);
	void	removeConnection(NeuronConnection &connection);
public:
	NeuronSimple(double status = 0);
	double	getStatus() const;
	void	setStatus(double status);
	size_t	getCountConnections();
	friend class NeuronNetwork;
};
