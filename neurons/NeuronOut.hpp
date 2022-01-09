//
// Created by Irena Mora on 1/4/22.
//

#pragma once

#include "../interfaces/NeuronSimple.hpp"

class NeuronOut : public NeuronSimple
{
private:
	using NeuronSimple::setStatus;
	double	expectedStatus;
public:
	NeuronOut(double expectedStatus = 0.0);
	void	setExpectedStatus(double expectedStatus);
	double	getExpectedStatus() const;
};
