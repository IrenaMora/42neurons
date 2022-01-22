//
// Created by Irena Mora on 1/12/22.
//

#pragma once

#include <set>
#include <iostream>

enum NeuronType
{
	IN,
	DEEP,
	OUT,
	NOPE
};

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

//////////////////////////////////////////
/// \brief Class for the inner workings of the library. Implements connections between multiple neurons.
//////////////////////////////////////////
class NeuronConnection
{
public:
	//////////////////////////////////////////
	/// \brief Operator overload comparison.
	//////////////////////////////////////////
	friend bool	operator < (const NeuronConnection &first, const NeuronConnection &second);
};

//////////////////////////////////////////
/// \brief Class for handling exceptions on library errors.
//////////////////////////////////////////
class NeuronException
{
private:
	long	code;
	std::string	message;
public:
	//////////////////////////////////////////
	/// \brief Constructor.
	/// \param code Error code.
	/// \param message Error message.
	//////////////////////////////////////////
	NeuronException(long code, std::string message);
	//////////////////////////////////////////
	/// \brief Returns an error code.
	//////////////////////////////////////////
	long	getCode();
	//////////////////////////////////////////
	/// \brief Returns an error message.
	//////////////////////////////////////////
	std::string	getMessage();
};

//////////////////////////////////////////
/// \brief Base class for all types of neurons: input, deep, output.
//////////////////////////////////////////
class NeuronSimple
{
private:
	double	status;
	bool	is_available;
	t_SetNeuronToConnections connections;
	t_SetNeuronToConnections	&getAllConnections();
	NeuronType	type;
private:
	bool	isAvailable() const;
	void	setAvailable(bool is_available);
	bool	isExistConnection(NeuronConnection &connection) const;
	void	addConnection(NeuronConnection &connection);
	void	removeConnection(NeuronConnection &connection);
public:
	//////////////////////////////////////////
	/// \brief Class destructor.
	//////////////////////////////////////////
	virtual ~NeuronSimple() {};
	//////////////////////////////////////////
	/// \brief Class constructor.
	/// \param status Specify the initial status (value) for the neuron for further calculations.
	//////////////////////////////////////////
	NeuronSimple(double status = 0, NeuronType type = NeuronType::NOPE);
	//////////////////////////////////////////
	/// \brief Get the status (value) of a neuron.
	//////////////////////////////////////////
	double	getStatus() const;
	//////////////////////////////////////////
	/// \brief Set the status (value) of a neuron.
	/// \param status Sets the status (value) for the neuron. Status (value) is directly involved in further calculations.
	//////////////////////////////////////////
	void	setStatus(double status);
	//////////////////////////////////////////
	/// \brief Returns the number of connections present in the neural network.
	//////////////////////////////////////////
	size_t	getCountConnections();
	friend class NeuronNetwork;
};

//////////////////////////////////////////
/// \brief Incoming neuron. In neural networks, only these classes store all input data.
//////////////////////////////////////////
class NeuronIn : public NeuronSimple
{
public:
	//////////////////////////////////////////
	/// \brief Class constructor.
	/// \param status The status (value) of a neuron stores the input data. For example, it can store the amount of red color from rgb (from 0 to 255), or store the price of a currency.
	//////////////////////////////////////////
	NeuronIn(double status = 0);
};

//////////////////////////////////////////
/// \brief Deep neuron. There is no way to set the status (value). The neural network sets it when learning/calculating on its own.
/// Just add objects of this class to the neural network, connect them with other neurons properly, and your task will be solved much more efficiently.   
//////////////////////////////////////////
class NeuronDeep : public NeuronSimple
{
private:
	using NeuronSimple::setStatus;
public:
	//////////////////////////////////////////
	/// \brief Class constructor
	//////////////////////////////////////////
	NeuronDeep();
};

//////////////////////////////////////////
/// \brief Deep neuron.
/// It stores the prediction of the neural network after the calculation and you put the desired result during training in it.
//////////////////////////////////////////
class NeuronOut : public NeuronSimple
{
private:
	using NeuronSimple::setStatus;
	double	expectedStatus;
public:
	//////////////////////////////////////////
	/// \brief Class constructor.
	/// \param expectedStatus Desired answer (for training) by default.
	//////////////////////////////////////////
	NeuronOut(double expectedStatus = 0.0);
	//////////////////////////////////////////
	/// \brief Set the expected status for this neuron (the neural network will strive for this status during training; this is the learning process).
	/// \param expectedStatus Desired answer (for training) by default.
	//////////////////////////////////////////
	void	setExpectedStatus(double expectedStatus);
	//////////////////////////////////////////
	/// \brief Returns the desired status you set earlier.
	//////////////////////////////////////////
	double	getExpectedStatus() const;
};

//////////////////////////////////////////
/// \brief Neural network. This is where you load the neurons, this is where you create all the connections.
/// This class trains and calculates the whole system.
//////////////////////////////////////////
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
	//////////////////////////////////////////
	/// \brief Returns whether a neuron exists in this neural network.
	/// \param neuron Neuron that is being tested for existence  
	//////////////////////////////////////////
	bool isExistNeuron(NeuronSimple &neuron);
	//////////////////////////////////////////
	/// \brief Add a neuron to this neural network.
	/// \param neuron The neuron we are testing.  
	//////////////////////////////////////////
	void addNeuron(NeuronSimple &neuron);
	//////////////////////////////////////////
	/// \brief Add neurons to this neural network.
	/// \param container_neurons Any container containing the neurons we want to add.  
	//////////////////////////////////////////
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
	//////////////////////////////////////////
	/// \brief Removes a neuron from this neural network.
	/// \param neuron Neuron to be deleted.  
	//////////////////////////////////////////
	void removeNeuron(NeuronSimple &neuron);
	//////////////////////////////////////////
	/// \brief Creating a connection between two neurons with a random weight.
	/// \param from Initial neuron.
	/// \param to Terminal neuron.
	/// \param function_type Activation function type.
	/// \param learning_rate Neural network learning rate. Usually has small fractional values. 
	//////////////////////////////////////////
	void createConnection(NeuronSimple &from, NeuronSimple &to, FunctionType function_type, double learning_rate);
	//////////////////////////////////////////
	/// \brief Creating a connection between two neurons.
	/// \param from Initial neuron.
	/// \param to Terminal neuron.
	/// \param function_type Activation function type.
	/// \param learning_rate Neural network learning rate. Usually has small fractional values.
	/// \param weight Initial connection weight between two neurons.
	//////////////////////////////////////////
	void createConnection(NeuronSimple &from, NeuronSimple &to, FunctionType function_type, double learning_rate, double weight);
	//////////////////////////////////////////
	/// \brief Returns the number of neurons that are part of this neural network.
	//////////////////////////////////////////
	size_t getCountNeurons();
	//////////////////////////////////////////
	/// \brief Returns the number of connections contained in this neural network.
	//////////////////////////////////////////
	size_t getCountConnections();
	//////////////////////////////////////////
	/// \brief Make a prediction.
	//////////////////////////////////////////
	void compute();
	//////////////////////////////////////////
	/// \brief Trains a neural network.
	//////////////////////////////////////////
	void learn();
};

