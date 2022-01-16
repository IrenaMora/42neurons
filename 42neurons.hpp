//
// Created by Irena Mora on 1/12/22.
//

#pragma once

#include "network/NeuronNetwork.hpp"
#include "neurons/NeuronIn.hpp"
#include "neurons/NeuronDeep.hpp"
#include "neurons/NeuronOut.hpp"
#include "exceptions/NeuronException.hpp"

class NeuronIn
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief The constructor allows you to set the default status (value) of the neuron
	////////////////////////////////////////////////////////////////////////////////////////////////////
	NeuronIn(double status = 0);
	double	getStatus() const;
	void	setStatus(double status);
	size_t	getCountConnections();
};
