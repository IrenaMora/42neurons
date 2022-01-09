//
// Created by Irena Mora on 1/4/22.
//

#pragma once

#include "../interfaces/NeuronSimple.hpp"

class NeuronDeep : public NeuronSimple
{
private:
	using NeuronSimple::setStatus;
public:
	NeuronDeep();
};
