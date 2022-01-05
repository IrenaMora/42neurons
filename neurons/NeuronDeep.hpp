//
// Created by Irena Mora on 1/4/22.
//

#pragma once

#include "../interfaces/NeuronDifficult.hpp"

class NeuronDeep : public NeuronDifficult
{
private:
	using NeuronDifficult::getStatus;
	using NeuronDifficult::setStatus;
	using NeuronDifficult::getResume;
	using NeuronDifficult::setResume;
public:
	NeuronDeep(double resumeMinimum = 0, double resumeMaximum = 0);
};
