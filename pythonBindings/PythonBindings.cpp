#include "NeuronDeep.hpp"
#include "NeuronIn.hpp"
#include "NeuronOut.hpp"
#include "NeuronNetwork.hpp"
#include "NeuronSimple.hpp"
#include "NeuronException.hpp"
#include "NeuronConnection.hpp"
#include "NeuronBase.hpp"
#include "NeuronFunctions.hpp"

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "pybind11/operators.h"

namespace py = pybind11;

PYBIND11_MODULE(pylibneurons, handle) {
    handle.doc() = "Some docs";
    py::class_<NeuronSimple>(
        handle, "PyNeuronSimple"
    )
    .def(py::init<double>(), py::arg("status") = 0)
    .def_property("status", &NeuronSimple::getStatus, &NeuronSimple::setStatus)
    .def_property_readonly("count_connections", &NeuronSimple::getCountConnections)
    ;
    py::class_<NeuronIn, NeuronSimple>(
        handle, "PyNeuronIn"
    )
    .def(py::init<double>(), py::arg("status") = 0)
    ;
    py::class_<NeuronDeep, NeuronSimple>(
        handle, "PyNeuronDeep"
    )
    .def(py::init())
    ;
    py::class_<NeuronOut, NeuronSimple>(
        handle, "PyNeuronOut"
    )
    .def(py::init<double>(), py::arg("expected_status") = 0.0)
    .def_property("expected_status", &NeuronOut::getExpectedStatus, &NeuronOut::setExpectedStatus)
    ;
    py::class_<NeuronConnection>(
        handle, "PyNeuronConnection"
    )
    .def(py::self < py::self)
    ;
    py::class_<NeuronNetwork>(
    handle, "PyNeuronNetwork", py::dynamic_attr())
    .def(py::init())
    .def("is_exist_neuron", &NeuronNetwork::isExistNeuron)
    .def("add_neuron", &NeuronNetwork::addNeuron, py::keep_alive<1, 2>())
    .def("remove_neuron", &NeuronNetwork::removeNeuron)
    .def(
        "create_connection",
         py::overload_cast<NeuronSimple &, NeuronSimple &, FunctionType, double, double>(&NeuronNetwork::createConnection),
         py::arg("from"),
         py::arg("to"),
         py::arg("function_type"),
         py::arg("learning_rate"),
         py::arg("weight")
    )
    .def(
        "create_connection",
         py::overload_cast<NeuronSimple &, NeuronSimple &, FunctionType, double>(&NeuronNetwork::createConnection),
         py::arg("from"),
         py::arg("to"),
         py::arg("function_type"),
         py::arg("learning_rate")
   )
    .def_property_readonly("count_neurons", &NeuronNetwork::getCountNeurons)
    .def_property_readonly("count_connections", &NeuronNetwork::getCountConnections)
    .def("compute", &NeuronNetwork::compute)
    .def("learn", &NeuronNetwork::learn)
    ;
    py::enum_<FunctionType>(
        handle, "PyFunctionType"
    )
    .value("sigmoid", SIGMOID)
    .value("relu", RELU)
    .export_values()
    ;
}