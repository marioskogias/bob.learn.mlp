#!/usr/bin/env python
# vim: set fileencoding=utf-8 :
# Andre Anjos <andre.anjos@idiap.ch>
# Mon 16 Apr 08:18:08 2012 CEST

from setuptools import setup, find_packages, dist
dist.Distribution(dict(setup_requires=['xbob.blitz', 'xbob.io', 'xbob.learn.activation', 'xbob.core']))
from xbob.blitz.extension import Extension
import xbob.io
import xbob.core
import xbob.learn.activation

import os
package_dir = os.path.dirname(os.path.realpath(__file__))
package_dir = os.path.join(package_dir, 'xbob', 'learn', 'mlp', 'include')
include_dirs = [
    package_dir,
    xbob.blitz.get_include(),
    xbob.io.get_include(),
    xbob.learn.activation.get_include(),
    xbob.core.get_include(),
    ]

packages = ['bob-machine >= 1.2.2']
version = '2.0.0a0'

setup(

    name='xbob.learn.mlp',
    version=version,
    description='Bindings for bob.machine\'s Multi-layer Perceptron and Trainers',
    url='http://github.com/bioidiap/xbob.learn.mlp',
    license='BSD',
    author='Andre Anjos',
    author_email='andre.anjos@idiap.ch',

    long_description=open('README.rst').read(),

    packages=find_packages(),
    include_package_data=True,

    install_requires=[
      'setuptools',
      'xbob.blitz',
      'xbob.io',
      'xbob.learn.activation',
      'xbob.core',
    ],

    namespace_packages=[
      "xbob",
      "xbob.learn",
      ],

    ext_modules = [
      Extension("xbob.learn.mlp.version",
        [
          "xbob/learn/mlp/version.cpp",
          ],
        packages = packages,
        include_dirs = include_dirs,
        version = version,
        ),
      Extension("xbob.learn.mlp._library",
        [
          "xbob/learn/mlp/cxx/machine.cpp",
          "xbob/learn/mlp/cxx/cross_entropy.cpp",
          "xbob/learn/mlp/cxx/square_error.cpp",
          "xbob/learn/mlp/cxx/shuffler.cpp",
          "xbob/learn/mlp/cxx/base_trainer.cpp",
          "xbob/learn/mlp/cxx/backprop.cpp",
          "xbob/learn/mlp/cxx/rprop.cpp",
          "xbob/learn/mlp/shuffler.cpp",
          "xbob/learn/mlp/cost.cpp",
          "xbob/learn/mlp/machine.cpp",
          "xbob/learn/mlp/main.cpp",
          ],
        packages = packages,
        include_dirs = include_dirs,
        version = version,
        ),
      ],

    entry_points={
      'console_scripts': [
        ],
      },

    classifiers = [
      'Development Status :: 3 - Alpha',
      'Intended Audience :: Developers',
      'License :: OSI Approved :: BSD License',
      'Natural Language :: English',
      'Programming Language :: Python',
      'Programming Language :: Python :: 3',
      'Topic :: Software Development :: Libraries :: Python Modules',
      ],

    )
