#!/usr/bin/env python
# vim: set fileencoding=utf-8 :
# Andre Anjos <andre.anjos@idiap.ch>
# Mon 16 Apr 08:18:08 2012 CEST

from setuptools import setup, find_packages, dist
dist.Distribution(dict(setup_requires=['bob.blitz', 'bob.io.base', 'bob.learn.activation', 'bob.core']))
from bob.blitz.extension import Extension
import bob.io.base
import bob.core
import bob.learn.activation

import os
package_dir = os.path.dirname(os.path.realpath(__file__))
package_dir = os.path.join(package_dir, 'bob', 'learn', 'mlp', 'include')
include_dirs = [
    package_dir,
    bob.blitz.get_include(),
    bob.io.base.get_include(),
    bob.learn.activation.get_include(),
    bob.core.get_include(),
    ]

packages = ['bob-io >= 2.0.0a2', 'bob-machine >= 2.0.0a2']
version = '2.0.0a0'

setup(

    name='bob.learn.mlp',
    version=version,
    description='Bindings for bob.machine\'s Multi-layer Perceptron and Trainers',
    url='http://github.com/bioidiap/bob.learn.mlp',
    license='BSD',
    author='Andre Anjos',
    author_email='andre.anjos@idiap.ch',

    long_description=open('README.rst').read(),

    packages=find_packages(),
    include_package_data=True,
    zip_safe=False,

    install_requires=[
      'setuptools',
      'bob.blitz',
      'bob.io.base',
      'bob.learn.activation',
      'bob.core',
    ],

    namespace_packages=[
      "bob",
      "bob.learn",
      ],

    ext_modules = [
      Extension("bob.learn.mlp.version",
        [
          "bob/learn/mlp/version.cpp",
          ],
        packages = packages,
        include_dirs = include_dirs,
        version = version,
        ),
      Extension("bob.learn.mlp._library",
        [
          "bob/learn/mlp/roll.cpp",
          "bob/learn/mlp/rprop.cpp",
          "bob/learn/mlp/backprop.cpp",
          "bob/learn/mlp/trainer.cpp",
          "bob/learn/mlp/shuffler.cpp",
          "bob/learn/mlp/cost.cpp",
          "bob/learn/mlp/machine.cpp",
          "bob/learn/mlp/main.cpp",
          "bob/learn/mlp/cxx/roll.cpp",
          "bob/learn/mlp/cxx/machine.cpp",
          "bob/learn/mlp/cxx/cross_entropy.cpp",
          "bob/learn/mlp/cxx/square_error.cpp",
          "bob/learn/mlp/cxx/shuffler.cpp",
          "bob/learn/mlp/cxx/trainer.cpp",
          "bob/learn/mlp/cxx/backprop.cpp",
          "bob/learn/mlp/cxx/rprop.cpp",
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
