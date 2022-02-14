from tkinter import IntVar
from typing import Optional
import pandas as pd
from pandas import DataFrame
from DrawNN import DrawNN
from Contract import *
from pylibneurons import *
import itertools
import time
import networkx as nx
import numpy.random as rnd
import matplotlib.pyplot as plt


class Presenter(ViewOutput):
    def __init__(self) -> None:
        self.__number_of_last_deep_layer = -1
        self.__number_of_input_neurons: int = 0
        self.__number_of_output_neurons: int = 0
        self.__number_of_neurons_in_deep_layer: list[IntVar] = []
        self.view: Optional[ViewInput] = None
        self.input_data: Optional[DataFrame] = None
        self.output_data: Optional[DataFrame] = None
        self.network: Optional[PyNeuronNetwork] = None

    @property
    def number_of_neurons_in_deep_layer(self) -> list[IntVar]:
        return self.__number_of_neurons_in_deep_layer

    def view_did_appear(self, view: ViewInput) -> None:
        pass

    def view_did_load(self, view: ViewInput) -> None:
        self.view.create_button_cells()

    def plus_neuron_button_tapped(self, view: ViewInput, layer: int):
        self.__number_of_neurons_in_deep_layer[layer - 1].set(
            self.__number_of_neurons_in_deep_layer[layer - 1].get() + 1)

    def minus_neuron_button_tapped(self, view: ViewInput, layer: int):
        if self.__number_of_neurons_in_deep_layer[layer - 1].get() <= 1:
            if layer - 1 < self.__number_of_last_deep_layer:
                self.view.show_error("Can't remove neuron")
            else:
                self.view.remove_plus_layer_button(layer=layer)
                self.view.remove_plus_minus_buttons(layer=layer)
                self.__number_of_last_deep_layer -= 1
                self.view.add_plus_layer_button(layer=layer)
                del self.__number_of_neurons_in_deep_layer[layer - 1]
        else:
            self.__number_of_neurons_in_deep_layer[layer - 1].set(
                self.__number_of_neurons_in_deep_layer[layer - 1].get() - 1)

    def plus_layer_button_tapped(self, view: ViewInput):
        self.__number_of_neurons_in_deep_layer.append(IntVar(value=1))
        self.__number_of_last_deep_layer += 1
        self.view.remove_plus_layer_button(layer=self.__number_of_last_deep_layer + 1)
        self.view.add_deep_plus_minus_buttons(layer=self.__number_of_last_deep_layer + 1)
        self.view.add_plus_layer_button(layer=self.__number_of_last_deep_layer + 2)

    def minus_layer_button_tapped(self, view: ViewInput):
        self.data_source.remove_layer()

    def load_input_button_tapped(self, view: ViewInput):
        filename = self.view.open_file()
        if filename is not None and len(filename) != 0:
            data = pd.read_csv(filename, sep='\t', header=None, dtype=float, decimal='.')
            self.input_data = data
            self.view.show_input_uploaded()
            self.__number_of_input_neurons = len(self.input_data.columns)
        if self.input_data is not None and self.output_data is not None:
            # self.__number_of_neurons_in_deep_layer.append(IntVar(value=0))
            self.view.remove_bottom_label()
            self.view.show_simple_network(self.__number_of_input_neurons, self.__number_of_output_neurons)

    def load_output_button_tapped(self, view: ViewInput):
        filename = self.view.open_file()
        if filename is not None and len(filename) != 0:
            data = pd.read_csv(filename, sep='\t', header=None, dtype=float, decimal='.')
            self.output_data = data
            self.view.show_output_uploaded()
            self.__number_of_output_neurons = len(self.output_data.columns)
        if self.input_data is not None and self.output_data is not None:
            # self.__number_of_neurons_in_deep_layer.append(IntVar(value=0))
            self.view.remove_bottom_label()
            self.view.show_simple_network(self.__number_of_input_neurons, self.__number_of_output_neurons)

    def start_button_tapped(self, view: ViewInput):
        if self.input_data is None:
            view.show_error("Input data is empty")
        elif self.output_data is None:
            view.show_error("Output data is empty")
        else:
            network = self.create_network()
            self.learn_network(network)
            self.view.show_guessing([x.status for x in self.network.in_neurons],
                                    [x.status for x in self.network.out_neurons])

    def create_network(self) -> PyNeuronNetwork:
        graph = nx.Graph()
        network = PyNeuronNetwork()
        self.network = network
        in_neurons = [PyNeuronIn() for _ in range(self.__number_of_input_neurons)]
        network.in_neurons = in_neurons
        deep_neurons = [
            [PyNeuronDeep() for _ in range(self.__number_of_neurons_in_deep_layer[layer].get())]
            for layer in range(len(self.__number_of_neurons_in_deep_layer))
            if self.__number_of_neurons_in_deep_layer[layer].get() > 0
        ]
        out_neurons = [PyNeuronOut() for _ in range(self.__number_of_output_neurons)]
        network.out_neurons = out_neurons
        neurons_layer = [in_neurons] + deep_neurons + [out_neurons]
        network_graph = DrawNN(
            [self.__number_of_input_neurons] + [x.get() for x in self.__number_of_neurons_in_deep_layer if
                                                x.get() > 0] + [self.__number_of_output_neurons])
        network_graph.draw()

        def add_edge(f_item, s_item, graph=None):
            graph.add_edge(f_item, s_item)
            graph.add_edge(s_item, f_item)

        for layer in neurons_layer:
            for neuron in layer:
                network.add_neuron(neuron)
                graph.add_node(neuron, text="In")
        for first, second in zip(neurons_layer[:-1], neurons_layer[1:]):
            for f_neuron in first:
                for s_neuron in second:
                    network.create_connection(f_neuron, s_neuron, PyFunctionType.relu, 0.1, 0.5)
                    add_edge(f_neuron, s_neuron, graph=graph)
        return network

    def learn_network(self, network):
        try:
            data_len = min(len(self.input_data), len(self.output_data))
            for i in range(data_len):
                for j in range(len(self.input_data.columns)):
                    network.in_neurons[j].status = self.input_data[j][i]
                for j in range(len(self.output_data.columns)):
                    network.out_neurons[j].expected_status = self.input_data[j][i]
                network.learn()
                print(
                    "Learning №",
                    i,
                    "\nExpected status\n",
                    list(map(lambda x: x.expected_status, network.out_neurons)),
                    "\nStatus\n",
                    list(map(lambda x: x.status, network.out_neurons))
                )
        except TypeError:
            self.view.show_error("Invalid Data")
        except IndexError:
            self.view.show_error("Invalid number of neurons")

    def guess_button_tapped(self, *args):
        for i in range(len(self.network.in_neurons)):
            self.network.in_neurons[i].status = float(args[i])
        self.network.compute()
        self.view.set_outputs([x.status for x in self.network.out_neurons])
