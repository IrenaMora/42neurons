//
// Created by Irena Mora on 1/5/22.
//

#include "NeuronFunctions.hpp"

double	NeuronFunctions::getDelta(double expectation, double result)
{
	return (result - expectation);
}

double	NeuronFunctions::getSigma(double value)
{
	return (1 / (1 + exp(-value)));
}
