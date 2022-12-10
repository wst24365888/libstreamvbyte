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
# Encode a list of integers into a byte array.
# Currently only supports np.uint32
encode(arg0: numpy.ndarray[numpy.uint32]) -> numpy.ndarray[numpy.uint8]

# Decode a byte array into a list of integers.
decode(arg0: numpy.ndarray[numpy.uint8], arg1: int) -> numpy.ndarray[numpy.uint32]
```

#### For `C++`

Include `streamvbyte.h` first.

```cpp
#include "streamvbyte.h"
```

And here are the APIs.

```cpp
/*
    Encodes a sequence of 32-bit unsigned integers to a byte array.

    @param in: a sequence of 32-bit unsigned integers
    @param count: the number of unsigned integers to encode
    @param out: a byte array

    @return the number of bytes written to out
*/
std::size_t encode(const uint32_t* in, std::size_t count, uint8_t* out);

/*
    Encodes a sequence of 32-bit unsigned integers to a byte array.

    @param in: a vector of 32-bit unsigned integers

    @return the number of bytes written to out
*/
std::vector<uint8_t> encode(const std::vector<uint32_t>& in);

/*
    Decodes a sequence of 32-bit unsigned integers from a byte array.

    @param in: a byte array
    @param out: a sequence of 32-bit unsigned integers
    @param count: the number of unsigned integers to decode

    @return the number of bytes written to in
*/
std::size_t decode(const uint8_t* in, uint32_t* out, std::size_t count);

/*
    Decodes a sequence of 32-bit unsigned integers from a byte array.

    @param in: a vector of bytes
    @param count: the number of unsigned integers to decode

    @return the number of bytes written to in
*/
std::vector<uint32_t> decode(const std::vector<uint8_t>& in, std::size_t count);

/*
    Returns the maximum number of bytes that can be written by encode().

    @param size: the number of unsigned integers to encode

    @return the maximum number of bytes that can be written by encode()
*/
static inline size_t max_compressed_size(const uint32_t size);
```

### Example

#### For `Python`

```python
import libstreamvbyte as svb

N = 2**20

# type(before_encode) == np.ndarray
# before_encode.dtype == np.uint32
before_encode = np.random.randint(0, 2**32, N, dtype=np.uint32)

# type(compressed_bytes) == np.ndarray
# compressed_bytes.dtype == np.uint8
compressed_bytes = svb.encode(before_encode)

# type(after_decode) == np.ndarray
# after_decode.dtype == np.uint32
after_decode = svb.decode(compressed_bytes, N)
```

#### For `C++`

```cpp
#include "streamvbyte.h"

int main() {
    std::size_t N = (1 << 20);

    uint32_t* before_encode = static_cast<uint32_t*>(malloc(N * sizeof(uint32_t)));
    
    uint8_t* compressed_bytes = static_cast<uint8_t*>(malloc(streamvbyte::max_compressed_size(N)));
    std::size_t bytes_encoded = streamvbyte::encode(before_encode, N, compressed_bytes);

    uint32_t* after_decode = static_cast<uint32_t*>(malloc(N * sizeof(uint32_t)));
    std::size_t bytes_decoded = streamvbyte::decode(compressed_bytes, after_decode, N);

    free(compressed_bytes);
    free(before_encode);
    free(after_decode);

    return 0;
}
```

Compile it with linking to `libstreamvbyte`.

```bash
g++ -o example example.cpp -lstreamvbyte
```

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- ROADMAP -->

## Roadmap

- [ ] Zigzag encoding/decoding.
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