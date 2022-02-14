import abc
import typing as t
from tkinter import IntVar


@t.runtime_checkable
class ViewInput(t.Protocol):
    @abc.abstractmethod
    def create_button_cells(self) -> None:
        pass

    @abc.abstractmethod
    def add_deep_plus_minus_buttons(self, layer: int) -> None:
        pass

    @abc.abstractmethod
    def remove_plus_minus_buttons(self, layer: int) -> None:
        pass

    @abc.abstractmethod
    def add_plus_layer_button(self, layer: int) -> None:
        pass

    @abc.abstractmethod
    def remove_plus_layer_button(self, layer: int) -> None:
        pass

    @abc.abstractmethod
    def remove_bottom_label(self):
        pass

    @abc.abstractmethod
    def open_file(self) -> t.Optional[str]:
        pass

    @abc.abstractmethod
    def show_error(self, text: str) -> None:
        pass

    @abc.abstractmethod
    def show_input_uploaded(self) -> None:
        pass

    @abc.abstractmethod
    def show_output_uploaded(self) -> None:
        pass

    @abc.abstractmethod
    def show_simple_network(self, number_of_input_neurons: int, number_of_output_neurons: int):
        pass

    @abc.abstractmethod
    def set_outputs(self, *args):
        pass

    @abc.abstractmethod
    def show_guessing(self, number_of_inputs, number_of_outputs):
        pass


@t.runtime_checkable
class ViewOutput(t.Protocol):
    number_of_neurons_in_deep_layer: list[IntVar]

    @abc.abstractmethod
    def view_did_load(self, view: ViewInput) -> None:
        pass

    @abc.abstractmethod
    def view_did_appear(self, view: ViewInput) -> None:
        pass

    @abc.abstractmethod
    def plus_neuron_button_tapped(self, view: ViewInput, layer: int):
        pass

    @abc.abstractmethod
    def minus_neuron_button_tapped(self, view: ViewInput, layer: int):
        pass

    @abc.abstractmethod
    def plus_layer_button_tapped(self, view: ViewInput):
        pass

    @abc.abstractmethod
    def minus_layer_button_tapped(self, view: ViewInput):
        pass

    @abc.abstractmethod
    def load_input_button_tapped(self, view: ViewInput):
        pass

    @abc.abstractmethod
    def load_output_button_tapped(self, view: ViewInput):
        pass

    @abc.abstractmethod
    def start_button_tapped(self, view: ViewInput):
        pass

    @abc.abstractmethod
    def guess_button_tapped(self, *args):
        pass
