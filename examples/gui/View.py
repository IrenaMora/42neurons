from tkinter import Tk, Canvas, Button, S, Frame, Label, W, messagebox, Entry, IntVar, PhotoImage, Scrollbar, RIGHT, Y, \
    X, END, NORMAL
from typing import Optional
from tkinter import filedialog as fd
from Contract import *


class View(ViewInput):
    def __init__(self, presenter: ViewOutput) -> None:
        self.presenter = presenter
        self.root = Tk(className="42Neurons")
        self.root.geometry("600x200")
        self.left = Frame(self.root)
        self.left.grid(row=0, column=0)
        self.bottom = Frame(self.root)
        label = Label(self.bottom, text="Upload your data first")
        label.pack()
        self.bottom.grid(row=1, column=1)
        self.bottom_cells: list[Frame] = []
        self.inputs: list[Entry] = []
        self.outputs: list[Label] = []

    def view_did_load(self) -> None:
        self.presenter.view_did_load(self)
        self.root.mainloop()

    def create_button_cells(self) -> None:
        input_load_button = Button(self.left, text="Load input", command=lambda: self.load_button_tapped("input"))
        input_load_button.grid(row=0, column=0)
        output_load_button = Button(self.left, text="Load output", command=lambda: self.load_button_tapped("output"))
        output_load_button.grid(row=1, column=0)
        start_button = Button(self.left, text="Start learning", command=self.start_button_tapped)
        start_button.grid(row=2, column=0)

    def validate(self, input: str):
        return input.isdigit()

    def add_deep_plus_minus_buttons(self, layer: int):
        self.bottom_cells.insert(layer, Frame(self.bottom))
        self.bottom_cells[layer + 1].grid(column=layer + 1, row=0)
        self.bottom_cells[layer].grid(column=layer, row=0)
        label = Label(
            self.bottom_cells[layer],
            text=f"{layer} Layer"
        )
        plus_button = Button(
            self.bottom_cells[layer],
            text="+",
            command=lambda: self.plus_neuron_button_tapped(layer=layer),
        )
        minus_button = Button(
            self.bottom_cells[layer],
            text="-",
            command=lambda: self.minus_neuron_button_tapped(layer=layer),
        )
        plus_button.grid(row=1, column=1, padx=0)
        minus_button.grid(row=1, column=0, padx=0)
        layer_input = Entry(
            self.bottom_cells[layer],
            textvariable=self.presenter.number_of_neurons_in_deep_layer[layer - 1],
            width=5,
            justify="center",
            validate="key",
            validatecommand=(self.root.register(self.validate), '%P'))
        layer_input.grid(row=0, column=0, columnspan=2)
        label.grid(row=2, column=0, columnspan=2)

    def remove_bottom_label(self):
        for widget in self.bottom.winfo_children():
            widget.destroy()

    def remove_plus_minus_buttons(self, layer: int):
        self.bottom_cells[layer].destroy()
        del self.bottom_cells[layer]

    def add_plus_layer_button(self, layer: int):
        self.bottom_cells.insert(layer, Frame(self.bottom))
        self.bottom_cells[layer + 1].grid(column=layer + 1, row=0)
        self.bottom_cells[layer].grid(column=layer, row=0)
        self.bottom.update()
        button = Button(self.bottom_cells[layer], text="+", command=self.plus_layer_button_tapped)
        button.pack()

    def remove_plus_layer_button(self, layer: int):
        self.bottom_cells[layer].destroy()
        del self.bottom_cells[layer]

    def plus_neuron_button_tapped(self, layer: int):
        self.presenter.plus_neuron_button_tapped(self, layer=layer)

    def minus_neuron_button_tapped(self, layer: int):
        self.presenter.minus_neuron_button_tapped(self, layer=layer)

    def plus_layer_button_tapped(self):
        self.presenter.plus_layer_button_tapped(self)

    def minus_layer_button_tapped(self):
        self.presenter.minus_layer_button_tapped(self)

    def load_button_tapped(self, type: str):
        if type == "input":
            self.presenter.load_input_button_tapped(self)
        elif type == "output":
            self.presenter.load_output_button_tapped(self)

    def start_button_tapped(self):
        self.presenter.start_button_tapped(self)

    def open_file(self) -> Optional[str]:
        filetypes = (
            ('text files', '*.txt *.csv *.xls *.xlsx'),
            ('All files', '*.*')
        )
        self.root.update_idletasks()
        filename = fd.askopenfilename(
            title='Open a file',
            initialdir='.',
            filetypes=filetypes
        )
        self.left.focus_set()
        return filename

    def show_error(self, text: str) -> None:
        # new_window = Tk()
        messagebox.showerror("Ошибка", text)
        self.root.focus_set()

    def show_input_uploaded(self) -> None:
        Label(self.left, text="* Uploaded").grid(row=0, column=1)

    def show_output_uploaded(self) -> None:
        Label(self.left, text="* Uploaded").grid(row=1, column=1)

    def show_simple_network(self, number_of_input_neurons: int, number_of_output_neurons: int):
        self.bottom_cells = [Frame(self.bottom) for _ in range(2)]
        for i in range(len(self.bottom_cells)):
            self.bottom_cells[i].grid(column=i, row=0)

        Label(self.bottom_cells[0], text="Input Layer").grid(row=2, column=0, columnspan=2)
        Label(self.bottom_cells[0], text=f"{number_of_input_neurons}").grid(row=0, column=0, columnspan=2)
        self.add_plus_layer_button(1)
        # self.add_deep_plus_minus_buttons(1)
        Label(self.bottom_cells[2], text="Output Layer").grid(row=2, column=0, columnspan=2)
        Label(self.bottom_cells[2], text=f"{number_of_output_neurons}").grid(row=0, column=0, columnspan=2)

    def guess_button_tapped(self):
        self.presenter.guess_button_tapped(*[x.get() for x in self.inputs])

    def show_guessing(self, inputs, outputs):
        height = (len(inputs) + len(outputs)) * 10 + 200
        self.root.geometry(f"600x{height}")
        frame = Frame(self.bottom)
        frame.grid(row=1, columnspan=len(inputs))
        for i in range(len(inputs)):
            entry = Entry(frame)
            entry.insert(0, inputs[i])
            self.inputs.append(entry)
            entry.pack(fill=X)
        Button(frame, text="Compute", command=self.guess_button_tapped).pack()
        for i in range(len(outputs)):
            label = Label(frame, text=outputs[i])
            self.outputs.append(label)
            label.pack(fill=X)

    def set_outputs(self, *args):
        for i in range(len(args)):
            self.outputs[i].config(text=args[i])