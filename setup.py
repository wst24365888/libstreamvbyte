# -*- coding: utf-8 -*-
from setuptools import setup

packages = \
['libstreamvbyte']

package_data = \
{'': ['*'], 'libstreamvbyte': ['decode/*', 'encode/*', 'util/*']}

install_requires = \
['setuptools>=65.6.3,<66.0.0']

setup_kwargs = {
    'name': 'libstreamvbyte',
    'version': '0.1.0',
    'description': 'A C++ implementation with Python binding for StreamVByte',
    'long_description': '',
    'author': 'HSING-HAN WU (Xyphuz)',
    'author_email': 'xyphuzwu@gmail.com',
    'maintainer': 'None',
    'maintainer_email': 'None',
    'url': 'None',
    'packages': packages,
    'package_data': package_data,
    'install_requires': install_requires,
    'python_requires': '>=3.10,<4.0',
}
from build import *
build(setup_kwargs)

setup(**setup_kwargs)
