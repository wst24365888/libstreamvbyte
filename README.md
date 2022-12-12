<div id="top"></div>

<!-- PROJECT SHIELDS -->

[<div align="center"> ![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![MIT License][license-shield]][license-url]
[![Issues][issues-shield]][issues-url]
[![Issues Closed][issues-closed-shield]</div>][issues-closed-url]

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

[StreamVByte](#reference) is a integer compression technique that use SIMD instructions (vectorization) to improve performance. The library is optimized for CPUs with the `SSSE3` instruction set (which is supported by most x86_64 processors), and can also be used with ARM processors and other 32-bit architectures, although it will fall back to scalar implementations in those cases.

With `libstreamvbyte`, you can quickly and efficiently compress integer sequences, reducing the amount of storage space and network bandwidth required. The library is easy to use and integrates seamlessly with `Python` via `pybind11` bindings. Whether you're working with large datasets or building a distributed computing system, `libstreamvbyte` can help you improve performance and reduce the resources needed to handle your data.

Currently supports `Python 3.10+` on Windows, Linux (`manylinux_2_17`, `musllinux_1_1`) and macOS (`universal2`).

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
encode(arg0: numpy.ndarray[numpy.uint32]) -> numpy.ndarray[numpy.uint8]

# Decode a byte array into an array of unsigned integers.
decode(arg0: numpy.ndarray[numpy.uint8], arg1: int) -> numpy.ndarray[numpy.uint32]

# Encode an array of signed integers into an array of unsigned integers.
zigzag_encode(arg0: numpy.ndarray[numpy.int32]) -> numpy.ndarray[numpy.uint32]

# Decode an array of unsigned integers into an array of signed integers.
zigzag_decode(arg0: numpy.ndarray[numpy.uint32]) -> numpy.ndarray[numpy.int32]

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
Load Average: 0.62, 0.90, 0.90
-------------------------------------------------------------------------------------------------------------
Benchmark                                                        Time             CPU   Iterations Throughput
-------------------------------------------------------------------------------------------------------------
BM_streamvbyte_encode/1000000/min_time:10.000               427609 ns       427609 ns        35964 9.35434G/s
BM_streamvbyte_encode/10000000/min_time:10.000             4387786 ns      4387691 ns         3262 9.11641G/s
BM_streamvbyte_encode/100000000/min_time:10.000           45285441 ns     45285378 ns          278 8.83287G/s
BM_streamvbyte_encode/1000000000/min_time:10.000         482895663 ns    482894996 ns           27 8.28337G/s
BM_streamvbyte_decode/1000000/min_time:10.000               176918 ns       176807 ns        81674 22.6235G/s
BM_streamvbyte_decode/10000000/min_time:10.000             3460414 ns      3460293 ns         4059 11.5597G/s
BM_streamvbyte_decode/100000000/min_time:10.000           35830694 ns     35830178 ns          399 11.1638G/s
BM_streamvbyte_decode/1000000000/min_time:10.000         395000967 ns    394998152 ns           29 10.1266G/s
BM_streamvbyte_zigzag_encode/1000000/min_time:10.000        198481 ns       198481 ns        71648 20.1531G/s
BM_streamvbyte_zigzag_encode/10000000/min_time:10.000      3905349 ns      3905318 ns         3699 10.2424G/s
BM_streamvbyte_zigzag_encode/100000000/min_time:10.000    38865616 ns     38865483 ns          367 10.2919G/s
BM_streamvbyte_zigzag_encode/1000000000/min_time:10.000  431700632 ns    431698141 ns           29 9.26573G/s
BM_streamvbyte_zigzag_decode/1000000/min_time:10.000        201529 ns       201529 ns        71350 19.8483G/s
BM_streamvbyte_zigzag_decode/10000000/min_time:10.000      3740073 ns      3739945 ns         3328 10.6953G/s
BM_streamvbyte_zigzag_decode/100000000/min_time:10.000    41444965 ns     41444779 ns          332  9.6514G/s
BM_streamvbyte_zigzag_decode/1000000000/min_time:10.000  416964668 ns    416963581 ns           32 9.59316G/s
```

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
- [ ] Support ARM processors with `NEON` intrinsics.
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