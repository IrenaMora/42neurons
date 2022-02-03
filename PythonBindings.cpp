#include "neurons/NeuronDeep.hpp"
#include "neurons/NeuronIn.hpp"
#include "neurons/NeuronOut.hpp"
#include "network/NeuronNetwork.hpp"
#include "interfaces/NeuronSimple.hpp"
#include "exceptions/NeuronException.hpp"
#include "connection/NeuronConnection.hpp"
#include "base/NeuronBase.hpp"
#include "base/NeuronFunctions.hpp"

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
    .def_property_readonly("countConnections", &NeuronSimple::getCountConnections)
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
    .def(py::init<double>(), py::arg("expectedStatus") = 0.0)
    .def_property("expectedStatus", &NeuronOut::getExpectedStatus, &NeuronOut::setExpectedStatus)
    ;
    py::class_<NeuronConnection>(
        handle, "PyNeuronConnection"
    )
    .def(py::self < py::self)
    ;
    py::class_<NeuronNetwork>(
    handle, "PyNeuronNetwork")
    .def(py::init())
    .def("isExistNeuron", &NeuronNetwork::isExistNeuron)
    .def("addNeuron", &NeuronNetwork::addNeuron, py::keep_alive<1, 2>())
    .def("removeNeuron", &NeuronNetwork::removeNeuron)
    .def("createConnection", py::overload_cast<NeuronSimple &, NeuronSimple &, FunctionType, double, double>(&NeuronNetwork::createConnection))
    .def("createConnection", py::overload_cast<NeuronSimple &, NeuronSimple &, FunctionType, double>(&NeuronNetwork::createConnection))

    .def_property_readonly("countNeurons", &NeuronNetwork::getCountNeurons)
    .def_property_readonly("countConnections", &NeuronNetwork::getCountConnections)
    .def("compute", &NeuronNetwork::compute)
    .def("learn", &NeuronNetwork::learn)
    ;
    py::enum_<FunctionType>(
        handle, "PyFunctionType"
    )
    .value("SIGMOID", SIGMOID)
    .value("RELU", RELU)
    .export_values()
    ;
}