/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Tue  6 May 12:32:39 2014 CEST
 *
 * @brief Bindings for an MLP
 *
 * Copyright (C) 2011-2014 Idiap Research Institute, Martigny, Switzerland
 */

#define XBOB_LEARN_MLP_MODULE
#include <xbob.blitz/cppapi.h>
#include <xbob.blitz/cleanup.h>
#include <xbob.learn.mlp/api.h>
#include <structmember.h>

/****************************************
 * Implementation of base Trainer class *
 ****************************************/

PyDoc_STRVAR(s_trainer_str, XBOB_EXT_MODULE_PREFIX ".Trainer");

PyDoc_STRVAR(s_trainer_doc,
"Trainer(batch_size, cost, [trainer, [train_biases]]) -> new Trainer\n\
Trainer(other) -> new Trainer\n\
\n\
The base python class for MLP trainers based on cost derivatives.\n\
\n\
You should use this class when you want to create your own MLP\n\
trainers and re-use the base infrastructured provided by this\n\
module, such as the computation of partial derivatives (using\n\
the :py:meth:`backward_step` method).\n\
\n\
To create a new trainer, either pass another trainer you'd like\n\
the parameters copied from or pass the batch-size, cost functor,\n\
machine and a biases-training flag.\n\
");

static int PyBobLearnMLPTrainer_init_discrete
(PyBobLearnMLPTrainerObject* self, PyObject* args, PyObject* kwds) {

  /* Parses input arguments in a single shot */
  static const char* const_kwlist[] = {
    "batch_size",
    "cost",
    "machine",
    "train_biases",
    0
  };
  static char** kwlist = const_cast<char**>(const_kwlist);

  Py_ssize_t batch_size = 0;
  PyBobLearnCostObject* cost = 0;
  PyBobLearnMLPMachineObject* machine = 0;
  PyObject* train_biases = 0;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "nO!|O!O", kwlist,
        &batch_size,
        &PyBobLearnCost_Type, &cost,
        &PyBobLearnMLPMachine_Type, &machine,
        &train_biases)) return -1;

  try {
    if (machine && train_biases) {
      self->cxx = new bob::learn::mlp::Trainer(batch_size, cost->cxx,
          *machine->cxx, PyObject_IsTrue(train_biases));
    }
    else if (machine) {
      self->cxx = new bob::learn::mlp::Trainer(batch_size, cost->cxx,
          *machine->cxx);
    }
    else if (train_biases) {
      PyErr_Format(PyExc_RuntimeError, "cannot provide a flag for `train_biases' and do not provide a `machine' upon initialisation of type `%s'", Py_TYPE(self)->tp_name);
      return -1;
    }
    else {
      self->cxx = new bob::learn::mlp::Trainer(batch_size, cost->cxx);
    }
  }
  catch (std::exception& ex) {
    PyErr_SetString(PyExc_RuntimeError, ex.what());
    return -1;
  }
  catch (...) {
    PyErr_Format(PyExc_RuntimeError, "cannot create new object of type `%s' - unknown exception thrown", Py_TYPE(self)->tp_name);
    return -1;
  }

  return 0;

}

static int PyBobLearnMLPTrainer_init_copy
(PyBobLearnMLPTrainerObject* self, PyObject* args, PyObject* kwds) {

  /* Parses input arguments in a single shot */
  static const char* const_kwlist[] = {"other", 0};
  static char** kwlist = const_cast<char**>(const_kwlist);

  PyObject* other = 0;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
        &PyBobLearnMLPTrainer_Type, &other)) return -1;

  auto copy = reinterpret_cast<PyBobLearnMLPTrainerObject*>(other);

  try {
    self->cxx = new bob::learn::mlp::Trainer(*(copy->cxx));
  }
  catch (std::exception& ex) {
    PyErr_SetString(PyExc_RuntimeError, ex.what());
    return -1;
  }
  catch (...) {
    PyErr_Format(PyExc_RuntimeError, "cannot create new object of type `%s' - unknown exception thrown", Py_TYPE(self)->tp_name);
    return -1;
  }

  return 0;

}

static int PyBobLearnMLPTrainer_init(PyBobLearnMLPTrainerObject* self,
    PyObject* args, PyObject* kwds) {

  Py_ssize_t nargs = (args?PyTuple_Size(args):0) + (kwds?PyDict_Size(kwds):0);

  switch (nargs) {

    case 1:

      return PyBobLearnMLPTrainer_init_copy(self, args, kwds);

    default:

      return PyBobLearnMLPTrainer_init_discrete(self, args, kwds);
  }

  return -1;

}

static void PyBobLearnMLPTrainer_delete
(PyBobLearnMLPTrainerObject* self) {

  delete self->cxx;
  Py_TYPE(self)->tp_free((PyObject*)self);

}

int PyBobLearnMLPTrainer_Check(PyObject* o) {
  return PyObject_IsInstance(o, reinterpret_cast<PyObject*>(&PyBobLearnMLPTrainer_Type));
}

static PyObject* PyBobLearnMLPTrainer_new
(PyTypeObject* type, PyObject*, PyObject*) {

  /* Allocates the python object itself */
  PyBobLearnMLPTrainerObject* self = (PyBobLearnMLPTrainerObject*)type->tp_alloc(type, 0);

  self->cxx = 0;

  return reinterpret_cast<PyObject*>(self);

}

PyTypeObject PyBobLearnMLPTrainer_Type = {
    PyVarObject_HEAD_INIT(0, 0)
    s_trainer_str,                                 /* tp_name */
    sizeof(PyBobLearnMLPTrainerObject),            /* tp_basicsize */
    0,                                             /* tp_itemsize */
    (destructor)PyBobLearnMLPTrainer_delete,       /* tp_dealloc */
    0,                                             /* tp_print */
    0,                                             /* tp_getattr */
    0,                                             /* tp_setattr */
    0,                                             /* tp_compare */
    0, //(reprfunc)PyBobLearnMLPTrainer_Repr,           /* tp_repr */
    0,                                             /* tp_as_number */
    0,                                             /* tp_as_sequence */
    0,                                             /* tp_as_mapping */
    0,                                             /* tp_hash */
    0,                                             /* tp_call */
    0, //(reprfunc)PyBobLearnMLPTrainer_Repr,           /* tp_str */
    0,                                             /* tp_getattro */
    0,                                             /* tp_setattro */
    0,                                             /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,      /* tp_flags */
    s_trainer_doc,                                 /* tp_doc */
    0,                                             /* tp_traverse */
    0,                                             /* tp_clear */
    0,                                             /* tp_richcompare */
    0,                                             /* tp_weaklistoffset */
    0,                                             /* tp_iter */
    0,                                             /* tp_iternext */
    0, //PyBobLearnMLPTrainer_methods,                  /* tp_methods */
    0,                                             /* tp_members */
    0, //PyBobLearnMLPTrainer_getseters,                /* tp_getset */
    0,                                             /* tp_base */
    0,                                             /* tp_dict */
    0,                                             /* tp_descr_get */
    0,                                             /* tp_descr_set */
    0,                                             /* tp_dictoffset */
    (initproc)PyBobLearnMLPTrainer_init,           /* tp_init */
    0,                                             /* tp_alloc */
    PyBobLearnMLPTrainer_new,                      /* tp_new */
};
