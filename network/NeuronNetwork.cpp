//
// Created by Irena Mora on 1/4/22.
//

#include "NeuronNetwork.hpp"

void	NeuronNetwork::addConnection(NeuronSimple &from, NeuronSimple &to, FunctionType function_type, double learning_rate, double weight)
{
	t_SetNeuronConnections::iterator current = this->connections.insert(NeuronConnection(from, to, function_type, learning_rate, weight)).first;
	from.addConnection(const_cast<NeuronConnection &>(*current));
	to.addConnection(const_cast<NeuronConnection &>(*current));
}

//TODO: optimize this method using and realizing method neuron.getAllConnectionsFrom() and neuron.getAllConnectionsTo()
void	NeuronNetwork::removeAllConnections(NeuronSimple &neuron)
{
	NeuronConnection *currentConnection;

	if (!isExistNeuron(neuron))
		throw (NeuronException(0, "The neuron is not exist in this neural network"));
	t_SetNeuronToConnections::iterator begin = neuron.getAllConnections().begin();
	t_SetNeuronToConnections::iterator end = neuron.getAllConnections().end();
	while (begin != end)
	{
		currentConnection = *begin;
		if (&currentConnection->getNeuronFrom() == &neuron || &currentConnection->getNeuronTo() == &neuron)
		{
			currentConnection->getNeuronFrom().removeConnection(const_cast<NeuronConnection &>(*currentConnection));
			currentConnection->getNeuronTo().removeConnection(const_cast<NeuronConnection &>(*currentConnection));
			this->connections.erase(*currentConnection);
			begin = neuron.getAllConnections().begin();
			end = neuron.getAllConnections().end();
			continue ;
		}
		begin++;
	}
}

bool	NeuronNetwork::isNeuronIn(NeuronSimple &neuron)
{
	return (neuron.getType() == NeuronType::IN);
}

bool	NeuronNetwork::isNeuronDeep(NeuronSimple &neuron)
{
	return (neuron.getType() == NeuronType::DEEP);
}


bool	NeuronNetwork::isNeuronOut(NeuronSimple &neuron)
{
	return (neuron.getType() == NeuronType::OUT);
}

void	NeuronNetwork::disableAllNeurons()
{
	t_SetToNeurons::iterator begin = this->neurons.begin();
	t_SetToNeurons::iterator end = this->neurons.end();

	while (begin != end)
	{
		if (!isNeuronIn(**begin))
			(*begin)->setStatus(0);
		begin++;
	}
}

//TODO: optimize this method using and realizing method neuron.getAllConnectionsFrom() and neuron.getAllConnectionsTo()
void	NeuronNetwork::computeNeuron(NeuronSimple *next, double resume)
{
	double weight;
	NeuronConnection *currentConnection;

	if (!isNeuronIn(*next))
		next->setStatus(next->getStatus() + resume);
	if (isNeuronOut(*next))
		return ;
	t_SetNeuronToConnections::iterator begin = next->getAllConnections().begin();
	t_SetNeuronToConnections::iterator end = next->getAllConnections().end();
	while (begin != end)
	{
		currentConnection = *begin;
		weight = currentConnection->getWeight();
		if (&currentConnection->getNeuronFrom() == next)
			computeNeuron(&currentConnection->getNeuronTo(), resume * weight * NeuronFunctions::getCorrection(weight, currentConnection->getFunctionType()));
		begin++;
	}
}

void	NeuronNetwork::learnNeuron(NeuronSimple &neuron, double sigma_weight)
{
	double delta_current_weight;
	NeuronConnection *currentConnection;
	t_SetNeuronToConnections::iterator begin = neuron.getAllConnections().begin();
	t_SetNeuronToConnections::iterator end = neuron.getAllConnections().end();

	while (begin != end)
	{
		currentConnection = *begin;
		if (&(currentConnection->getNeuronTo()) == &neuron)
		{
			delta_current_weight = sigma_weight * currentConnection->getWeight() * currentConnection->getNeuronFrom().getStatus() * currentConnection->getLearningRate();
			currentConnection->setWeight(currentConnection->getWeight() + delta_current_weight);
			learnNeuron(currentConnection->getNeuronFrom(), sigma_weight);
		}
		begin++;
	}
}

bool	NeuronNetwork::isExistNeuron(NeuronSimple &neuron)
{
	t_SetToNeurons::iterator begin = this->neurons.begin();
	t_SetToNeurons ::iterator end = this->neurons.end();

	while (begin != end)
	{
		if (*begin == &neuron)
			return (true);
		begin++;
	}
	return (false);
}

void	NeuronNetwork::addNeuron(NeuronSimple &neuron)
{
	if (isExistNeuron(neuron))
		throw (NeuronException(0, "The neuron already use in this neural network"));
	if (!neuron.isAvailable())
		throw (NeuronException(0, "This neuron already exist in another neural network"));
	neuron.setAvailable(false);
	this->neurons.insert(&neuron);
}

void	NeuronNetwork::removeNeuron(NeuronSimple &neuron)
{
	t_SetToNeurons::iterator begin;
	t_SetToNeurons::iterator end;

	begin = this->neurons.begin();
	end = this->neurons.end();
	while (begin != end)
	{
		if (*begin == &neuron)
		{
			removeAllConnections(**begin);
			(*begin)->setAvailable(true);
			this->neurons.erase(begin);
			return ;
		}
		begin++;
	}
	//Нейрон не найден
	throw (NeuronException(0, "The neuron does not use in this neural network"));
}

void	NeuronNetwork::createConnection(NeuronSimple &from, NeuronSimple &to, FunctionType function_type, double learning_rate, double weight)
{
	if (!isExistNeuron(from) || !isExistNeuron(to))
		throw (NeuronException(0, "The neuron(-s) is not in this neural network"));
	if (NeuronConnection::isAlreadyConnected(this->connections, from, to))
		throw (NeuronException(0, "This connection already exists"));
	if (isNeuronOut(from))
		throw (NeuronException(0, "Neuron FROM cannot be NeuronOut"));
	addConnection(from, to, function_type, learning_rate, weight);
}

void	NeuronNetwork::createConnection(NeuronSimple &from, NeuronSimple &to, FunctionType function_type, double learning_rate)
{
	createConnection(from, to, function_type, learning_rate, NeuronFunctions::getRandomWeight());
}

size_t	NeuronNetwork::getCountNeurons()
{
	return (this->neurons.size());
}

size_t	NeuronNetwork::getCountConnections()
{
	return (this->connections.size());
}

void	NeuronNetwork::compute()
{
	t_SetToNeurons::iterator begin = this->neurons.begin();
	t_SetToNeurons::iterator end = this->neurons.end();

	disableAllNeurons();
	while (begin != end)
	{
		if (isNeuronIn(**begin))
			computeNeuron(*begin, (*begin)->getStatus());
		begin++;
	}
}

void	NeuronNetwork::learn()
{
	double weight;
	double delta;
	double sigma_weight;
	NeuronSimple *currentNeuron;
	NeuronConnection *currentConnection;

	this->compute();
	t_SetToNeurons::iterator begin = this->neurons.begin();
	t_SetToNeurons::iterator end = this->neurons.end();
	while (begin != end)
	{
		currentNeuron = *begin;
		if (isNeuronOut(*currentNeuron))
		{
			delta = ((NeuronOut *)(currentNeuron))->getExpectedStatus() - currentNeuron->getStatus();
			t_SetNeuronToConnections::iterator begin2 = currentNeuron->getAllConnections().begin();
			t_SetNeuronToConnections::iterator end2 = currentNeuron->getAllConnections().end();
			while (begin2 != end2)
			{
				currentConnection = *begin2;
				weight = currentConnection->getWeight();
				sigma_weight = delta * weight * NeuronFunctions::getDerivativeCorrection(weight, currentConnection->getFunctionType());
				currentConnection->setWeight(currentConnection->getWeight() + (sigma_weight * currentConnection->getLearningRate()));
				learnNeuron(currentConnection->getNeuronFrom(), sigma_weight);
				begin2++;
			}
		}
		begin++;
	}
}

void	NeuronNetwork::saveNetwork(const std::string &file)
{
	std::ofstream out(file, std::ios::out | std::ios::binary);
	if (!out)
		throw (NeuronException(0, "Unable to open file " + file));

	out << this->getCountNeurons() << '\n';
	for (const auto &connection : this->connections)
	{
		std::string function_type, from_type, to_type;
		if (connection.getFunctionType() == FunctionType::SIGMOID)
			function_type = "SIGMOID";
		else if (connection.getFunctionType() == FunctionType::RELU)
			function_type = "RELU";

		if (connection.getNeuronFrom().getType() == NeuronType::IN)
			from_type = "IN";
		else if (connection.getNeuronFrom().getType() == NeuronType::DEEP)
			from_type = "DEEP";
		else if (connection.getNeuronFrom().getType() == NeuronType::OUT)
			from_type = "OUT";

		if (connection.getNeuronTo().getType() == NeuronType::IN)
			to_type = "IN";
		else if (connection.getNeuronTo().getType() == NeuronType::DEEP)
			to_type = "DEEP";
		else if (connection.getNeuronTo().getType() == NeuronType::OUT)
			to_type = "OUT";

		out << &connection.getNeuronFrom() << ' ' << &connection.getNeuronTo() << ' '
			<< function_type << ' ' << connection.getWeight() << ' ' << connection.getLearningRate() << ' '
			<< from_type << ' ' << to_type << '\n';
	}
}

void	NeuronNetwork::loadNetwork(std::vector<std::unique_ptr<NeuronSimple>> &neurons_container, const std::string &file)
{
	std::ifstream in(file, std::ios::in | std::ios::binary);
	if (!in)
		throw (NeuronException(0, "Unable to open file " + file));

	this->connections.clear();
	this->neurons.clear();

	neurons_container.clear();
	std::unordered_map<std::string, size_t> pointers;
	size_t neurons_count = 0;
	in >> neurons_count;
	neurons_container.reserve(neurons_count);

	std::string from, to, function_type, from_type, to_type;
	double weight = 0, learning_rate = 0;
	while (in >> from >> to >> function_type >> weight >> learning_rate >> from_type >> to_type)
	{
		if (pointers.find(from) == pointers.end())
		{
			if (from_type == "IN")
				neurons_container.push_back(std::make_unique<NeuronIn>());
			else if (from_type == "DEEP")
				neurons_container.push_back(std::make_unique<NeuronDeep>());
			else if (from_type == "OUT")
				neurons_container.push_back(std::make_unique<NeuronOut>());
			else
				throw (NeuronException(0, "Invalid 'from' neuron type " + from_type));

			pointers[from] = neurons_container.size() - 1;
			this->addNeuron(*neurons_container.back());
		}

		if (pointers.find(to) == pointers.end())
		{
			if (to_type == "IN")
				neurons_container.push_back(std::make_unique<NeuronIn>());
			else if (to_type == "DEEP")
				neurons_container.push_back(std::make_unique<NeuronDeep>());
			else if (to_type == "OUT")
				neurons_container.push_back(std::make_unique<NeuronOut>());
			else
				throw (NeuronException(0, "Invalid 'to' neuron type " + to_type));

			pointers[to] = neurons_container.size() - 1;
			this->addNeuron(*neurons_container.back());
		}

		auto type = FunctionType::SIGMOID;
		if (function_type == "SIGMOID")
			type = FunctionType::SIGMOID;
		else if (function_type == "RELU")
			type = FunctionType::RELU;
		else
			throw (NeuronException(0, "Invalid function_type " + function_type));

		this->createConnection(*neurons_container[pointers[from]], *neurons_container[pointers[to]], type, learning_rate, weight);
	}
}
