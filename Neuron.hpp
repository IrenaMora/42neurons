//
// Created by Irena Mora on 1/3/22.
//

#pragma once

class Neuron
{
private:
	float	power;
	bool 	status;
	bool	is_available;
private:
	bool	isAvailable() const;
	void	setAvailable(bool is_available);
public:
	Neuron(float power = 0, bool status = false);
	float	getPower() const;
	void	setPower(float power);
	bool	getStatus() const;
	void	setStatus(bool status);
	float	getOutPower() const;
	friend class NeuronNetwork;
};
