//
// Created by Irena Mora on 1/4/22.
//

#include "NeuronException.hpp"

NeuronException::NeuronException(long code, string message) : code(code), message(message) {}

long	NeuronException::getCode()
{
	return (this->code);
}

string	NeuronException::getMessage()
{
	return (message);
}
