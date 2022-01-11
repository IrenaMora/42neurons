//
// Created by Irena Mora on 1/5/22.
//

#include <cmath>
#include "NeuronBase.hpp"
#include "../exceptions/NeuronException.hpp"


class NeuronFunctions
{
private:
	static double	getSigmoid(double value);
	static double	getDerivativeSigmoid(double value);
	static double	getReLU(double value);
	static double	getDerivativeReLU(double value);
public:
	static double	getCorrection(double value, FunctionType function_type);
	static double	getDerivativeCorrection(double value, FunctionType function_type);
};
