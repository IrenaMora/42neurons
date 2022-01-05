//
// Created by Irena Mora on 1/4/22.
//

#pragma once

#include "../exceptions/NeuronException.hpp"

#include <iostream>
#include <vector>
#include "../base/NeuronBase.hpp"

using namespace std;

class NeuronNetwork;

class NeuronSimple
{
private:
	double	status;
public:
	NeuronSimple(double status = 0);
	double	getStatus() const;
	void	setStatus(double status);
	friend class NeuronNetwork;
};
