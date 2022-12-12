# -*- coding: utf-8 -*-
from build import *
from setuptools import setup
import os
import pathlib
from typing import Dict, Any
import sys
from setuptools import setup
from setuptools import Extension
from setuptools.command.build_ext import build_ext
import re
import subprocess

PLAT_TO_CMAKE = {
    "win32": "Win32",
    "win-amd64": "x64",
    "win-arm32": "ARM",
    "win-arm64": "ARM64",
}


class CMakeExtension(Extension):
    def __init__(self, name: str, sourcedir: str = ""):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def run(self):
        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext: CMakeExtension):
        ext_dir = pathlib.Path(self.get_ext_fullpath(
            ext.name)).parent.absolute()

        debug = int(os.environ.get("DEBUG", 0)
                    ) if self.debug is None else self.debug
        cfg = "Debug" if debug else "Release"

        cmake_args = [
            f"-DBUILD_SHARED_LIBS=OFF",
            f"-DBUILD_PYBIND11=ON",
            f"-DPRINT_BENCHMARK=OFF",
            f"-DBUILD_TESTS=OFF",
            f"-DBUILD_BENCHMARKS=OFF",
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={ext_dir}",
            f"-DPYTHON_EXECUTABLE={sys.executable}",
            f"-DCMAKE_BUILD_TYPE={cfg}",
        ]
        build_args = []

        cmake_generator = os.environ.get("CMAKE_GENERATOR", "")

        if sys.platform.startswith("win"):
            # Single config generators are handled "normally"
            single_config = any(
                x in cmake_generator for x in {"NMake", "Ninja"})

            # CMake allows an arch-in-generator style for backward compatibility
            contains_arch = any(x in cmake_generator for x in {"ARM", "Win64"})

            # Specify the arch if using MSVC generator, but only if it doesn't
            # contain a backward-compatibility arch spec already in the
            # generator name.
            if not single_config and not contains_arch:
                cmake_args += ["-A", PLAT_TO_CMAKE[self.plat_name]]

            # Multi-config generators have a different way to specify configs
            if not single_config:
                cmake_args += [
                    f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{cfg.upper()}={ext_dir}"
                ]
                build_args += ["--config", cfg]

        if sys.platform.startswith("darwin"):
            archs = re.findall(r"-arch (\S+)", os.environ.get("ARCHFLAGS", ""))
            if archs:
                cmake_args += [
                    "-DCMAKE_OSX_ARCHITECTURES={}".format(";".join(archs))]

        build_temp = pathlib.Path(self.build_temp)
        build_temp.mkdir(parents=True, exist_ok=True)

        subprocess.run(
            ["cmake", ext.sourcedir] + cmake_args,
            cwd=build_temp,
            check=True,
        )
        subprocess.run(
            ["cmake", "--build", "."] + build_args,
            cwd=build_temp,
            check=True,
        )


setup(
    name='libstreamvbyte',
    version='0.2.4',
    description='A C++ implementation with Python bindings of StreamVByte.',
    long_description=open('README.md').read(),
    author='HSING-HAN WU (Xyphuz)',
    author_email='xyphuzwu@gmail.com',
    maintainer='HSING-HAN WU (Xyphuz)',
    maintainer_email='xyphuzwu@gmail.com',
    url='https://github.com/wst24365888/libstreamvbyte',
    python_requires='>=3.10,<4.0',
    ext_modules=[CMakeExtension("libstreamvbyte")],
    cmdclass=dict(build_ext=CMakeBuild),
    long_description_content_type='text/markdown',
)
