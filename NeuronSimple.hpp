//
// Created by Irena Mora on 1/4/22.
//

#pragma once

#include "NeuronException.hpp"

class NeuronSimple
{
private:
	double	status;
	bool	is_available;
private:
	bool	isAvailable() const;
	void	setAvailable(bool is_available);
public:
	NeuronSimple(double status = 0);
	double	getStatus() const;
	void	setStatus(double status);
};
