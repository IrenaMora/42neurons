//
// Created by Irena Mora on 1/5/22.
//

#include <cmath>

class NeuronFunctions {
public:
	static double	getDelta(double expectation, double result);
	static double	getDeltaSimpleWeight(double delta, double weight); //TODO: set new body of function
	static double	getDeltaDifficultWeight(double weight_delta, double learn_rate); //TODO: set new body of function
	static double	getSigma(double value);
	static double	getDerivativeSigma(double value);
	static double	getReLU(double value);
	static double	getDerivativeReLU(double value);
};
