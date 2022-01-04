//
// Created by Irena Mora on 1/4/22.
//

#include "NeuronDifficult.hpp"

double	NeuronDifficult::getResume() const
{
	return (this->resume);
}

void	NeuronDifficult::setResume(double resume)
{
	this->resume = resume;
}

NeuronDifficult::NeuronDifficult(double resumeMinimum, double resumeMaximum) : resumeMinimum(resumeMinimum),
						resumeMaximum(resumeMaximum) {}

double	NeuronDifficult::getResumeMinimum() const
{
	return (this->resumeMinimum);
}

void	NeuronDifficult::setResumeMinimum(double resumeMinimum)
{
	this->resumeMinimum = resumeMaximum;
}

double	NeuronDifficult::getResumeMaximum() const
{
	return (this->resumeMaximum);
}

void	NeuronDifficult::setResumeMaximum(double resumeMaximum)
{
	this->resumeMaximum = resumeMaximum;
}
