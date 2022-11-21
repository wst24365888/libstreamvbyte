#include "streamvbyte.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(streamvbyte, m) {
    m.doc() = "C++ StreamVByte Plugin";

    m.def("encode", py::overload_cast<const std::vector<uint32_t>&>(&streamvbyte::encode), "Encode a list of integers into a byte array.");
    m.def("decode", py::overload_cast<const std::vector<uint8_t>&, std::size_t>(&streamvbyte::decode), "Decode a byte array into a list of integers.");
}