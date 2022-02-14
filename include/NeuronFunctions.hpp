//
// Created by Irena Mora on 1/5/22.
//

#pragma once

#include <cmath>
#include <sys/time.h>
#include "NeuronBase.hpp"
#include "NeuronException.hpp"


class NeuronFunctions
{
private:
	static double	getSigmoid(double value);
	static double	getDerivativeSigmoid(double value);
	static double	getReLU(double value);
	static double	getDerivativeReLU(double value);
public:
	static double	getRandomWeight();
	static double	getCorrection(double value, FunctionType function_type);
	static double	getDerivativeCorrection(double value, FunctionType function_type);
};
