# 42neurons library

**What is this library?**

This library can help you freely develop your own neural network the way you want.

**What language library use?**

The library is written in pure C++ without additional libraries. 

**It is fast?**

Yes! Library wirtten in pure C++ and therefore has a high performance.

**Why I must use it?**

You can create neural networks the way you want by connecting neurons in any order on your own. This makes the library flexible.
You also will understand more about how neural network works.

**Is this difficult to use?**

No. The library has several classes close to each other containing 2-3 functions.

**Where can I get examples?**

All examples - from simple to complex - are in the folder examples

**I want to see a simple neural network with this library!**

	/* Creating incoming neuron */
	NeuronIn in_first; 
	/* Creating outgoing neuron */
	NeuronOut out_first;
	/* Create neural network */
	NeuronNetwork network;
	
	/* Add incoming neuron to neural network */
	network.addNeuron(in_first);
	/* Add outgoing neuron */
	network.addNeuron(out_first);
	
	/* Create connection between incoming and outgoing neurons */
	/* Set function RELU and learning rate 0.01 */
	network.createConnect(in_first, out_first, FunctionType::RELU, 0.01);
	
	/* Compute neural network */
	network.compute(); 
	
	/* Write result */
	cout << out_first.getStatus() << endl;

