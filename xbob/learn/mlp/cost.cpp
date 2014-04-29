/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Tue 29 Apr 09:26:02 2014 CEST
 *
 * @brief Bindings for Cost functions
 *
 * Copyright (C) 2011-2014 Idiap Research Institute, Martigny, Switzerland
 */

#define XBOB_LEARN_MLP_MODULE
#include <xbob.blitz/cppapi.h>
#include <xbob.blitz/cleanup.h>
#include <xbob.learn.mlp/api.h>
#include <structmember.h>

/****************************************
 * Implementation of Machine base class *
 ****************************************/

PyDoc_STRVAR(s_machine_str, XBOB_EXT_MODULE_PREFIX ".Machine");

PyDoc_STRVAR(s_machine_doc,
"Machine(shape)\n\
Machine(config)\n\
Machine(other)\n\
\n\
A Multi-layer Perceptron Machine.\n\
\n\
An MLP Machine is a representation of a Multi-Layer Perceptron.\n\
This implementation is feed-forward and fully-connected. The\n\
implementation allows setting of input normalization values and\n\
a global activation function. References to fully-connected\n\
feed-forward networks:\n\
\n\
  Bishop's Pattern Recognition and Machine Learning, Chapter 5.\n\
  Figure 5.1 shows what we mean.\n\
\n\
MLPs normally are multi-layered systems, with 1 or more hidden\n\
layers. As a special case, this implementation also supports\n\
connecting the input directly to the output by means of a single\n\
weight matrix. This is equivalent of a\n\
:py:class:`xbob.learn.linear.Machine`, with the advantage it can\n\
be trained by trainers defined in this package.\n\
\n\
An MLP can be constructed in different ways. In the first form,\n\
the user specifies the machine shape as sequence (e.g. a tuple).\n\
The sequence should contain the number of inputs (first element),\n\
number of outputs (last element) and the number of neurons in\n\
each hidden layer (elements between the first and last element\n\
of given tuple). The activation function will be set to\n\
hyperbolic tangent. The machine is remains **uninitialized**.\n\
In the second form the user passes a pre-opened HDF5 file\n\
pointing to the machine information to be loaded in memory.\n\
Finally, in the last form (copy constructor), the user passes\n\
another :py:class:`Machine` that will be fully copied.\n\
");

