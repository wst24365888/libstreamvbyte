<div id="top"></div>

<!-- PROJECT SHIELDS -->

[<div align="center"> ![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![MIT License][license-shield]][license-url]
[![Issues][issues-shield]][issues-url]
[![Issues Closed][issues-closed-shield]][issues-closed-url]
[![Python Version][python-version-shield]][python-version-url]
[![Week Download][download-shield]</div>][download-url]

<br />

<!-- PROJECT BANNER -->

![libstreamvbyte](https://socialify.git.ci/wst24365888/libstreamvbyte/image?description=1&font=KoHo&name=1&owner=1&pattern=Circuit%20Board&theme=Light)

<br />
<div align="center">
<p align="center">
    <a href="https://github.com/wst24365888/libstreamvbyte#usage"><strong>Explore Usage »</strong></a>
    <br />
    <br />
    <a href="https://github.com/wst24365888/libstreamvbyte/issues">Report Bug</a>
    ·
    <a href="https://github.com/wst24365888/libstreamvbyte/issues">Request Feature</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#usage">Usage</a></li>
        <li><a href="#example">Example</a></li>
      </ul>
    </li>
    <li><a href="#benchmark">Benchmark</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#reference">Reference</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->

## About The Project

`libstreamvbyte` is a `C++` implementation of [StreamVByte](#reference), with `Python` bindings using `pybind11`. 

[StreamVByte](#reference) is an integer compression technique that use SIMD instructions (vectorization) to improve performance. The library is optimized with `SSSE3` intrinsics, which are supported by most `x86_64` processors. It uses `sse2neon` to translate `SSSE3` intrinsics to `NEON` intrinsics for `ARM` processors. The library can also be used with other 32-bit architectures, although it will fall back to scalar implementations in those cases.

With `libstreamvbyte`, you can quickly and efficiently compress integer sequences, reducing the amount of storage space and network bandwidth required. The library is easy to use and integrates seamlessly with `Python` via `pybind11` bindings. Whether you're working with large datasets or building a distributed computing system, `libstreamvbyte` can help you improve performance and reduce the resources needed to handle your data.

Currently supports `Python 3.8+` on Windows, Linux (`manylinux_2_17`, `musllinux_1_1`) and macOS (`universal2`).

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- GETTING STARTED -->

## Getting Started

### Installation

#### For `Python`

Install from `PyPI` using `pip`.

```bash
pip install libstreamvbyte
```

Or install from `.whl` file.

```bash
pip install "path/to/your/downloaded/whl"
```

To find appropriate `.whl` file, please visit [releases](https://github.com/wst24365888/libstreamvbyte/releases).

#### For `C++`

You must have `CMake` installed on your system.

```bash
# clone the repo
git clone https://github.com/wst24365888/libstreamvbyte
cd libstreamvbyte

# build and install
cmake .
make
sudo make install
```

### Usage

#### For `Python`

Import `libstreamvbyte` first.

```python
import libstreamvbyte as svb
```

And here are the APIs.

```python
# Encode an array of unsigned integers into a byte array.
encode(in_uint32: numpy.ndarray[numpy.uint32]) -> numpy.ndarray[numpy.uint8]

# Decode a byte array into an array of unsigned integers.
decode(in_uint8: numpy.ndarray[numpy.uint8], size: int) -> numpy.ndarray[numpy.uint32]

# Encode an array of signed integers into an array of unsigned integers.
zigzag_encode(in_int32: numpy.ndarray[numpy.int32]) -> numpy.ndarray[numpy.uint32]

# Decode an array of unsigned integers into an array of signed integers.
zigzag_decode(in_uint32: numpy.ndarray[numpy.uint32]) -> numpy.ndarray[numpy.int32]

# Check if the current wheel is a vectorized version.
is_vectorized_version() -> bool
```

#### For `C++`

Include `streamvbyte.h` first.

```cpp
#include "streamvbyte.h"
```

For the APIs, please refer to [include/streamvbyte.h](https://github.com/wst24365888/libstreamvbyte/blob/main/include/streamvbyte.h).

### Example

#### For `Python`

```python
import libstreamvbyte as svb

N = 2**20 + 2

# type(original_data) == np.ndarray
# original_data.dtype == np.int32
original_data = np.random.randint(-2**31, 2**31, N, dtype=np.int32)

# type(compressed_bytes) == np.ndarray
# compressed_bytes.dtype == np.uint8
compressed_bytes = svb.encode(svb.zigzag_encode(original_data))

# type(recovered_data) == np.ndarray
# recovered_data.dtype == np.int32
recovered_data = svb.zigzag_decode(svb.decode(compressed_bytes, N))
```

#### For `C++`

```cpp
#include "streamvbyte.h"

int main() {
    std::size_t N = (1 << 20) + 2;

    std::vector<int32_t> original_data(N);
    for (std::size_t i = 0; i < N; ++i) {
        original_data[i] = rand() - rand();
    }

    std::vector<uint8_t> compressed_bytes = streamvbyte::encode(streamvbyte::zigzag_encode(original_data));
    std::vector<int32_t> recovered_data = streamvbyte::zigzag_decode(streamvbyte::decode(compressed_bytes, N));

    return 0;
}
```

Compile it with linking to `libstreamvbyte`.

```bash
g++ -o example example.cpp -lstreamvbyte
```

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- BENCHMARK -->

## Benchmark

```bash
OS: Linux 5.15.79.1-microsoft-standard-WSL2 x86_64
CPU: AMD Ryzen 5 3600 6-Core Processor (12) @ 3.600GHz

Run on (12 X 3593.26 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 512 KiB (x6)
  L3 Unified 16384 KiB (x1)
Load Average: 0.81, 0.85, 0.69
-----------------------------------------------------------------------------------
Benchmark                              Time             CPU   Iterations Throughput
-----------------------------------------------------------------------------------
BM_memcpy/4096                       149 ns          149 ns      4688531 13.7122G/s
BM_memcpy/8192                       548 ns          548 ns      1275803 7.46783G/s
BM_memcpy/16384                     1139 ns         1138 ns       640835 7.19553G/s
BM_memcpy/32768                     2185 ns         2185 ns       320840 7.49932G/s
BM_memcpy/65536                     4921 ns         4921 ns       142703 6.65895G/s
BM_memcpy/131072                   10968 ns        10968 ns        63502 5.97511G/s
BM_memcpy/262144                   22465 ns        22465 ns        31134 5.83457G/s
BM_memcpy/524288                   45101 ns        45100 ns        15541 5.81245G/s
BM_memcpy/1048576                  91131 ns        91131 ns         7639 5.75314G/s
BM_streamvbyte_encode/4096          1222 ns         1222 ns       580855 1.67556G/s
BM_streamvbyte_encode/8192          2470 ns         2467 ns       282349 1.66064G/s
BM_streamvbyte_encode/16384         4945 ns         4945 ns       139671 1.65662G/s
BM_streamvbyte_encode/32768         9990 ns         9989 ns        70497 1.64017G/s
BM_streamvbyte_encode/65536        19853 ns        19853 ns        30963 1.65051G/s
BM_streamvbyte_encode/131072       39933 ns        39932 ns        17401 1.64118G/s
BM_streamvbyte_encode/262144       80563 ns        80562 ns         8193 1.62697G/s
BM_streamvbyte_encode/524288      160716 ns       160716 ns         4284  1.6311G/s
BM_streamvbyte_encode/1048576     319253 ns       319253 ns         1942 1.64223G/s
BM_streamvbyte_decode/4096           691 ns          691 ns      1040462 2.96191G/s
BM_streamvbyte_decode/8192          1341 ns         1341 ns       516979 3.05539G/s
BM_streamvbyte_decode/16384         2683 ns         2683 ns       261208 3.05359G/s
BM_streamvbyte_decode/32768         5348 ns         5348 ns       130319 3.06353G/s
BM_streamvbyte_decode/65536        10817 ns        10817 ns        64427 3.02936G/s
BM_streamvbyte_decode/131072       23207 ns        23207 ns        31546   2.824G/s
BM_streamvbyte_decode/262144       45746 ns        45746 ns        11291 2.86519G/s
BM_streamvbyte_decode/524288       88660 ns        88660 ns         7947 2.95673G/s
BM_streamvbyte_decode/1048576     178497 ns       178497 ns         3907 2.93724G/s
BM_zigzag_encode/4096                810 ns          810 ns       854076 2.52829G/s
BM_zigzag_encode/8192               1611 ns         1608 ns       433154   2.548G/s
BM_zigzag_encode/16384              3174 ns         3174 ns       219165 2.58084G/s
BM_zigzag_encode/32768              6457 ns         6457 ns       108415 2.53754G/s
BM_zigzag_encode/65536             12582 ns        12582 ns        54747 2.60432G/s
BM_zigzag_encode/131072            25243 ns        25243 ns        27802 2.59617G/s
BM_zigzag_encode/262144            50278 ns        50278 ns        13952 2.60693G/s
BM_zigzag_encode/524288           100563 ns       100562 ns         6932 2.60678G/s
BM_zigzag_encode/1048576          211846 ns       211845 ns         3222 2.47487G/s
BM_zigzag_decode/4096                675 ns          675 ns      1041044 3.03263G/s
BM_zigzag_decode/8192               1342 ns         1342 ns       523553 3.05196G/s
BM_zigzag_decode/16384              2643 ns         2643 ns       265497 3.09905G/s
BM_zigzag_decode/32768              5383 ns         5383 ns       130976 3.04377G/s
BM_zigzag_decode/65536             11474 ns        11474 ns        60817 2.85588G/s
BM_zigzag_decode/131072            21777 ns        21777 ns        32345 3.00944G/s
BM_zigzag_decode/262144            43477 ns        43478 ns        14387  3.0147G/s
BM_zigzag_decode/524288            86120 ns        86120 ns         8145 3.04393G/s
BM_zigzag_decode/1048576          173095 ns       173093 ns         4028 3.02894G/s
```

> The unit of `Throughput` is `GB/s` (Giga Bytes per second).

### Build Benchmarks from Source

```bash
cmake . \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_PYBIND11=OFF \
    -DPRINT_BENCHMARK=OFF \
    -DBUILD_TESTS=ON \
    -DBUILD_BENCHMARKS=ON
make libstreamvbyte_benchmarks
./libstreamvbyte_benchmarks --benchmark_counters_tabular=true
```

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- ROADMAP -->

## Roadmap

- [x] Zigzag encoding/decoding.
- [x] Support ARM processors with `NEON` intrinsics.
- [ ] Differential coding (delta encoding/decoding).

See the [open issues](https://github.com/wst24365888/libstreamvbyte/issues)
for a full list of proposed features (and known issues).

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTRIBUTING -->

## Contributing

Contributions are what make the open source community such an amazing place to
learn, inspire, and create. Any contributions you make are **greatly
appreciated**.

If you have a suggestion that would make this better, please fork the repo and
create a pull request. You can also simply open an issue with the tag
"enhancement". Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feat/amazing-feature`)
3. Commit your Changes with
   [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/)
4. Push to the Branch (`git push origin feat/amazing-feature`)
5. Open a Pull Request

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- LICENSE -->

## License

Distributed under the MIT License. See
[LICENSE](https://github.com/wst24365888/libstreamvbyte/blob/main/LICENSE)
for more information.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- REFERENCE -->

## Reference

- Daniel Lemire, Nathan Kurz, Christoph Rupp, [Stream VByte: Faster Byte-Oriented Integer Compression](https://arxiv.org/abs/1709.08990), Information Processing Letters 130, 2018.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTACT -->

## Contact

### Author

- HSING-HAN, WU (Xyphuz)
  - Mail me: xyphuzwu@gmail.com
  - About me: <https://www.xyphuz.com>
  - GitHub: <https://github.com/wst24365888>

### Project Link

- <https://github.com/wst24365888/libstreamvbyte>

<p align="right">(<a href="#top">back to top</a>)</p>

[contributors-shield]: https://img.shields.io/github/contributors/wst24365888/libstreamvbyte.svg?style=for-the-badge
[contributors-url]: https://github.com/wst24365888/libstreamvbyte/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/wst24365888/libstreamvbyte.svg?style=for-the-badge
[forks-url]: https://github.com/wst24365888/libstreamvbyte/network/members
[stars-shield]: https://img.shields.io/github/stars/wst24365888/libstreamvbyte.svg?style=for-the-badge
[stars-url]: https://github.com/wst24365888/libstreamvbyte/stargazers
[issues-shield]: https://img.shields.io/github/issues/wst24365888/libstreamvbyte.svg?style=for-the-badge
[issues-url]: https://github.com/wst24365888/libstreamvbyte/issues
[issues-closed-shield]: https://img.shields.io/github/issues-closed/wst24365888/libstreamvbyte.svg?style=for-the-badge
[issues-closed-url]: https://github.com/wst24365888/libstreamvbyte/issues?q=is%3Aissue+is%3Aclosed
[license-shield]: https://img.shields.io/github/license/wst24365888/libstreamvbyte.svg?style=for-the-badge
[license-url]: https://github.com/wst24365888/libstreamvbyte/blob/main/LICENSE
[python-version-shield]: https://img.shields.io/pypi/pyversions/libstreamvbyte?color=A000A0&style=for-the-badge
[python-version-url]: https://pypi.org/project/libstreamvbyte/
[download-shield]: https://img.shields.io/pypi/dw/libstreamvbyte?color=A000A0&style=for-the-badge
[download-url]: https://pypistats.org/packages/libstreamvbyte
