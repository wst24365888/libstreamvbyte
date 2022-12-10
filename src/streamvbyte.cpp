#include "streamvbyte.h"
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(libstreamvbyte, m) {
    m.doc() = "C++ StreamVByte Plugin";

    m.def(
        "encode", [](py::array_t<uint32_t> in) {
            py::buffer_info in_buf = in.request();

            if (in_buf.ndim != 1) {
                throw std::runtime_error("Number of dimensions must be one.");
            }

            auto out = py::array_t<uint8_t>(streamvbyte::max_compressed_size(in_buf.size));
            py::buffer_info out_buf = out.request();

            std::size_t compressed_size = streamvbyte::encode(reinterpret_cast<uint32_t*>(in_buf.ptr), in_buf.size, reinterpret_cast<uint8_t*>(out_buf.ptr));
            out.resize({ compressed_size });

            return out;
        },
        "Encode an array of unsigned integers into a byte array.");

    m.def(
        "decode", [](py::array_t<uint8_t> in, std::size_t size) {
            py::buffer_info in_buf = in.request();

            if (in_buf.ndim != 1) {
                throw std::runtime_error("Number of dimensions must be one.");
            }

            auto out = py::array_t<uint32_t>(size);
            py::buffer_info out_buf = out.request();

            streamvbyte::decode(reinterpret_cast<uint8_t*>(in_buf.ptr), reinterpret_cast<uint32_t*>(out_buf.ptr), out_buf.size);

            return out;
        },
        "Decode a byte array into an array of unsigned integers.");

    m.def(
        "encode_zigzag", [](py::array_t<int32_t> in) {
            py::buffer_info in_buf = in.request();

            if (in_buf.ndim != 1) {
                throw std::runtime_error("Number of dimensions must be one.");
            }

            auto out = py::array_t<uint32_t>(in_buf.size);
            py::buffer_info out_buf = out.request();

            streamvbyte::encode_zigzag(reinterpret_cast<int32_t*>(in_buf.ptr), in_buf.size, reinterpret_cast<uint32_t*>(out_buf.ptr));

            return out;
        },
        "Encode an array of signed integers into an array of unsigned integers.");

    m.def(
        "decode_zigzag", [](py::array_t<uint32_t> in) {
            py::buffer_info in_buf = in.request();

            if (in_buf.ndim != 1) {
                throw std::runtime_error("Number of dimensions must be one.");
            }

            auto out = py::array_t<int32_t>(in_buf.size);
            py::buffer_info out_buf = out.request();

            streamvbyte::decode_zigzag(reinterpret_cast<uint32_t*>(in_buf.ptr), in_buf.size, reinterpret_cast<int32_t*>(out_buf.ptr));

            return out;
        },
        "Decode an array of unsigned integers into an array of signed integers.");
}