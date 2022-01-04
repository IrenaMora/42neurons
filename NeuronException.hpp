//
// Created by Irena Mora on 1/4/22.
//

#pragma once

#include <iostream>

using namespace std;

class NeuronException
{
private:
	long	code;
	string	message;
public:
	NeuronException(long code, string message);
	long	getCode();
	string	getMessage();
};

