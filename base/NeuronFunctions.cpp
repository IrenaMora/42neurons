//
// Created by Irena Mora on 1/5/22.
//

#include "NeuronFunctions.hpp"

double	NeuronFunctions::getDelta(double expectation, double result)
{
	return (expectation - result);
}

double	NeuronFunctions::getDeltaSimpleWeight(double delta, double weight)
{
	return (delta * weight);
}

double	NeuronFunctions::getDeltaDifficultWeight(double weight_delta, double learn_rate)
{
	return (weight_delta * learn_rate);
}

double	NeuronFunctions::getSigma(double value)
{
	return (1 / (1 + exp(-value)));
}

double	NeuronFunctions::getDerivativeSigma(double value)
{
	double sigma = getSigma(value);
	return (sigma * (1 - sigma));
}

double	NeuronFunctions::getReLU(double value)
{
	return (fmax(0, value));
}

double	NeuronFunctions::getDerivativeReLU(double value)
{
	return (1);
}
