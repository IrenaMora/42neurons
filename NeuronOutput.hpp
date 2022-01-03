//
// Created by Irena Mora on 1/3/22.
//

#pragma once

#include "Neuron.hpp"

class NeuronOutput : public Neuron
{
private:
	float	minimum_resume;
	float	maximum_resume;
public:
	NeuronOutput(float minimum_resume = 0, float maximum_resume = 0);
};
