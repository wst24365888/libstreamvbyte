#include "streamvbyte.h"
#include "config.h"
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
        py::arg("in_uint32"),
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
        py::arg("in_uint8"), py::arg("size"),
        "Decode a byte array into an array of unsigned integers.");

    m.def(
        "zigzag_encode", [](py::array_t<int32_t> in) {
            py::buffer_info in_buf = in.request();

            if (in_buf.ndim != 1) {
                throw std::runtime_error("Number of dimensions must be one.");
            }

            auto out = py::array_t<uint32_t>(in_buf.size);
            py::buffer_info out_buf = out.request();

            streamvbyte::zigzag_encode(reinterpret_cast<int32_t*>(in_buf.ptr), in_buf.size, reinterpret_cast<uint32_t*>(out_buf.ptr));

            return out;
        },
        py::arg("in_int32"),
        "Encode an array of signed integers into an array of unsigned integers.");

    m.def(
        "zigzag_decode", [](py::array_t<uint32_t> in) {
            py::buffer_info in_buf = in.request();

            if (in_buf.ndim != 1) {
                throw std::runtime_error("Number of dimensions must be one.");
            }

            auto out = py::array_t<int32_t>(in_buf.size);
            py::buffer_info out_buf = out.request();

            streamvbyte::zigzag_decode(reinterpret_cast<uint32_t*>(in_buf.ptr), in_buf.size, reinterpret_cast<int32_t*>(out_buf.ptr));

            return out;
        },
        py::arg("in_uint32"),
        "Decode an array of unsigned integers into an array of signed integers.");

    m.def(
        "is_vectorized_version", []() {
#if defined(_MSC_VER) && defined(_M_AMD64)
            return true;
#elif defined(__SSSE3__) || defined(__NEON__)
            return true;
#else
            return false;
#endif
        },
        "Check if the current wheel is a vectorized version.");

#if defined(PROJECT_VERSION)
    m.attr("__version__") = PROJECT_VERSION;
#endif
}