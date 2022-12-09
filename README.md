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

`libstreamvbyte` is a `C++` implementation of [StreamVByte](#reference), with `Python` bidings using `pybind11`. 

[StreamVByte](#reference) is a integer compression technique that use SIMD instructions (vectorization) to improve performance. The library is optimized for CPUs with the `SSSE3` instruction set (which is supported by most x86_64 processors), and can also be used with ARM processors and other 32-bit architectures, although it will fall back to scalar implementations in those cases.

With `libstreamvbyte`, you can quickly and efficiently compress integer sequences, reducing the amount of storage space and network bandwidth required. The library is easy to use and integrates seamlessly with `Python` via `pybind11` bindings. Whether you're working with large datasets or building a distributed computing system, `libstreamvbyte` can help you improve performance and reduce the resources needed to handle your data.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- GETTING STARTED -->

## Getting Started

### Installation

#### Using `pip`

`pip install libstreamvbyte`

#### Using `.whl`

See [releases](https://github.com/wst24365888/libstreamvbyte/releases).

### Usage

Import `libstreamvbyte` first.

```python
import libstreamvbyte as svb
```

Then here is the API.

```python
# Encode a list of integers into a byte array.
# Currently only supports np.uint32
def encode(arg0: numpy.ndarray[numpy.uint32]) -> numpy.ndarray[numpy.uint8]

# Decode a byte array into a list of integers.
def decode(arg0: numpy.ndarray[numpy.uint8], arg1: int) -> numpy.ndarray[numpy.uint32]
```

### Example

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