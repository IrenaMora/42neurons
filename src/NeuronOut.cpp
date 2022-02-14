//
// Created by Irena Mora on 1/4/22.
//

#include "NeuronOut.hpp"

NeuronOut::NeuronOut(double expectedStatus) : NeuronSimple(0, NeuronType::OUT), expectedStatus(expectedStatus) {}

void    NeuronOut::setExpectedStatus(double expectedStatus)
{
    this->expectedStatus = expectedStatus;
}

double    NeuronOut::getExpectedStatus() const
{
    return (this->expectedStatus);
}
