//
// Created by Irena Mora on 1/4/22.
//

#pragma once

class NeuronSimple
{
private:
	double	status;
public:
	NeuronSimple(double status = 0);
	double	getStatus() const;
	void	setStatus(double status);
};
