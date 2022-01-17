//
// Created by Irena Mora on 1/12/22.
//

#pragma once

#include <set>
#include <iostream>

enum FunctionType
{
	SIGMOID,
	RELU
};

class NeuronSimple;
class NeuronConnection;

typedef std::set<NeuronSimple *> t_SetToNeurons;
typedef std::set<NeuronConnection> t_SetNeuronConnections;
typedef std::set<NeuronConnection *> t_SetNeuronToConnections;

class NeuronFunctions
{
private:
	static double	getSigmoid(double value);
	static double	getDerivativeSigmoid(double value);
	static double	getReLU(double value);
	static double	getDerivativeReLU(double value);
public:
	static double	getRandomWeight();
	static double	getCorrection(double value, FunctionType function_type);
	static double	getDerivativeCorrection(double value, FunctionType function_type);
};

class NeuronConnection
{
private:
	double			weight;
	double			learning_rate;
	FunctionType	function_type;
	NeuronSimple	*from;
	NeuronSimple	*to;
public:
	NeuronConnection(NeuronSimple &from, NeuronSimple &to, FunctionType function_type, double learning_rate, double weight);
	double	getWeight() const;
	void	setWeight(double weight);
	double	getLearningRate() const;
	void	setLearningRate(double learning_rate);
	FunctionType	getFunctionType() const;
	void	setFunctionType(FunctionType function_type);
	NeuronSimple	&getNeuronFrom() const;
	void	setNeuronFrom(NeuronSimple &from);
	NeuronSimple	&getNeuronTo() const;
	void	setNeuronTo(NeuronSimple &to);
	static bool	isAlreadyConnected(t_SetNeuronConnections &connections, NeuronSimple &from, NeuronSimple &to);
	friend bool	operator < (const NeuronConnection &first, const NeuronConnection &second);
};

class NeuronException
{
private:
	long	code;
	std::string	message;
public:
	NeuronException(long code, std::string message);
	long	getCode();
	std::string	getMessage();
};

class NeuronSimple
{
private:
	double	status;
	bool	is_available;
	t_SetNeuronToConnections connections;
	t_SetNeuronToConnections	&getAllConnections();
private:
	bool	isAvailable() const;
	void	setAvailable(bool is_available);
	bool	isExistConnection(NeuronConnection &connection) const;
	void	addConnection(NeuronConnection &connection);
	void	removeConnection(NeuronConnection &connection);
public:
	virtual ~NeuronSimple() {};
	NeuronSimple(double status = 0);
	double	getStatus() const;
	void	setStatus(double status);
	size_t	getCountConnections();
	friend class NeuronNetwork;
};

class NeuronIn : public NeuronSimple
{
public:
	NeuronIn(double status = 0);
};

class NeuronDeep : public NeuronSimple
{
private:
	using NeuronSimple::setStatus;
public:
	NeuronDeep();
};

class NeuronOut : public NeuronSimple
{
private:
	using NeuronSimple::setStatus;
	double	expectedStatus;
public:
	NeuronOut(double expectedStatus = 0.0);
	void	setExpectedStatus(double expectedStatus);
	double	getExpectedStatus() const;
};

class NeuronNetwork
{
private:
	t_SetToNeurons neurons;
	t_SetNeuronConnections connections;

private:
	void addConnection(NeuronSimple &from, NeuronSimple &to, FunctionType function_type, double learning_rate, double weight);
	void removeAllConnections(NeuronSimple &neuron);
	bool isNeuronIn(NeuronSimple &neuron);
	bool isNeuronDeep(NeuronSimple &neuron);
	bool isNeuronOut(NeuronSimple &neuron);
	void disableAllNeurons();
	void computeNeuron(NeuronSimple *next, double resume);
	void learnNeuron(NeuronSimple &neuron, double sigma_weight);

public:
	~NeuronNetwork();
	bool isExistNeuron(NeuronSimple &neuron);
	void addNeuron(NeuronSimple &neuron);
	template <typename T>
	void addNeurons(T &container_neurons)
	{
		typename T::iterator begin = container_neurons.begin();
		typename T::iterator end = container_neurons.end();

		while (begin != end)
		{
			addNeuron(*begin);
			begin++;
		}
	}
	void removeNeuron(NeuronSimple &neuron);
	void createConnection(NeuronSimple &from, NeuronSimple &to, FunctionType function_type, double learning_rate);
	void createConnection(NeuronSimple &from, NeuronSimple &to, FunctionType function_type, double learning_rate, double weight);
	size_t getCountNeurons();
	size_t getCountConnections();
	void compute();
	void learn();
};

