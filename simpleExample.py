import random


from build.pylibneurons import *

in_first = PyNeuronIn()
out_first = PyNeuronOut()
network = PyNeuronNetwork()
network.addNeuron(in_first)
network.addNeuron(out_first)
network.createConnection(in_first, out_first, PyFunctionType.RELU, 0.01, 0.5)
for i in range(20):
	value = random.randint(1, 100)
	in_first.status = value
	out_first.expectedStatus = value * 0.75
	network.learn()
	print("Learning №", i, ".", "Expected status ", out_first.expectedStatus, ".", "Status", out_first.status)
while True:
	value = float(input("Write value:\n"))
	in_first.status = value
	network.compute()
	print("Your result:", out_first.status)
