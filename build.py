import os
import pathlib
from typing import Dict, Any
import sys
from setuptools import setup
from setuptools import Extension
from setuptools.command.build_ext import build_ext


class CMakeExtension(Extension):
    def __init__(self, name: str, sourcedir: str = ""):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def run(self):
        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext: CMakeExtension):
        cwd = pathlib.Path().absolute()

        cmake_args = [
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{'DEBUG' if self.debug else  'RELEASE'}={cwd}/dist",
            f"-DCMAKE_BUILD_TYPE={'Debug' if self.debug else 'Release'}",
            f"-DPYTHON_EXECUTABLE={sys.executable}",
        ]

        pathlib.Path(self.build_temp).mkdir(parents=True, exist_ok=True)

        self.spawn(["cmake", ext.sourcedir] + cmake_args)
        self.spawn(["cmake", "--build", ".", "--config",
                   'Debug' if self.debug else 'Release'])


def build(setup_kwargs: Dict[str, Any]):
    setup_kwargs.update(
        name="libstreamvbyte",
        version="0.1.0",
        author="HSING-HAN WU (Xyphuz)",
        author_email="xyphuzwu@gmail.com",
        description="A C++ implementation with Python binding for StreamVByte",
        long_description="",
        ext_modules=[CMakeExtension("libstreamvbyte")],
        cmdclass=dict(build_ext=CMakeBuild),
    )
