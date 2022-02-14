//
// Created by Irena Mora on 1/5/22.
//

#include "NeuronFunctions.hpp"

double	NeuronFunctions::getSigmoid(double value)
{
	return (1 / (1 + exp(-value)));
}

double	NeuronFunctions::getDerivativeSigmoid(double value)
{
	double sigma = getSigmoid(value);
	return (sigma * (1 - sigma));
}

double	NeuronFunctions::getReLU(double value)
{
	return (fmax(0, value));
}

double	NeuronFunctions::getDerivativeReLU(double)
{
	return (1);
}

double	NeuronFunctions::getRandomWeight()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	srand(time.tv_sec * time.tv_usec);
	return (static_cast<double>(rand() % 1000000) / 1000000);
}

double	NeuronFunctions::getCorrection(double value, FunctionType function_type)
{
	if (function_type == FunctionType::SIGMOID)
		return (NeuronFunctions::getSigmoid(value));
	else if (function_type == FunctionType::RELU)
		return (NeuronFunctions::getReLU(value));
	else
		throw (NeuronException(0, "Unknown type of function"));

}

double	NeuronFunctions::getDerivativeCorrection(double value, FunctionType function_type)
{
	if (function_type == FunctionType::SIGMOID)
		return (NeuronFunctions::getDerivativeSigmoid(value));
	else if (function_type == FunctionType::RELU)
		return (NeuronFunctions::getDerivativeReLU(value));
	else
		throw (NeuronException(0, "Unknown type of function"));
}
