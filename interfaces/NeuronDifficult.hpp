//
// Created by Irena Mora on 1/4/22.
//

#pragma once

#include "NeuronSimple.hpp"

class NeuronDifficult : public NeuronSimple
{
private:
	double	resume;
	double	resumeMinimum;
	double	resumeMaximum;
public:
	NeuronDifficult(double resumeMinimum = 0, double resumeMaximum = 0);
	double	getResumeMinimum() const;
	void	setResumeMinimum(double resumeMinimum);
	double	getResumeMaximum() const;
	void	setResumeMaximum(double resumeMaximum);
	double	getResume() const;
	void	setResume(double resume);
};
