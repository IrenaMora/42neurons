//
// Created by Irena Mora on 1/4/22.
//

#pragma once

#include "../interfaces/NeuronDifficult.hpp"

class NeuronOut : public NeuronDifficult
{
private:
	using NeuronDifficult::setStatus;
	using NeuronDifficult::setResume;
public:
	NeuronOut(double resumeMinimum = 0, double resumeMaximum = 0);
};
