/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Tue 29 Apr 2014 16:16:59 CEST
 *
 * @brief Bindings for the data shuffler
 *
 * Copyright (C) 2011-2014 Idiap Research Institute, Martigny, Switzerland
 */

#define XBOB_LEARN_MLP_MODULE
#include <xbob.blitz/cppapi.h>
#include <xbob.blitz/cleanup.h>
#include <xbob.learn.mlp/api.h>
#include <structmember.h>

/*********************************************
 * Implementation of DataShuffler base class *
 *********************************************/

PyDoc_STRVAR(s_shuffler_str, XBOB_EXT_MODULE_PREFIX ".DataShuffler");

PyDoc_STRVAR(s_shuffler_doc,
"DataShuffler(data, target) -> New DataShuffler\n\
\n\
Serves data from a training set, in a random way.\n\
\n\
Objects of this class are capable of being populated with data\n\
from one or multiple classes and matching target values. Once\n\
setup, the shuffer can randomly select a number of vectors and\n\
accompaning targets for the different classes, filling up user\n\
containers.\n\
\n\
Data shufflers are particular useful for training neural networks.\n\
\n\
Keyword arguments:\n\
\n\
data, sequence of array-like 2D float64\n\
  The input data are divided into sets corresponding to the\n\
  elements of each input class. Within the class array, each\n\
  row is expected to correspond to one observation of that class.\n\
\n\
target, sequence of array-like 1D float64\n\
  The target arrays correspond to the targets for each of the\n\
  input arrays. The number of targets must match the number of\n\
  2D array objects given in ``data``.\n\
\n");

static int PyBobLearnDataShuffler_init
(PyBobLearnDataShufflerObject* self, PyObject* args, PyObject* kwds) {

  /* Parses input arguments in a single shot */
  static const char* const_kwlist[] = {"data", "target", 0};
  static char** kwlist = const_cast<char**>(const_kwlist);

  PyObject* data = 0;
  PyObject* target = 0;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist,
        &data, &target)) return -1;

  /* Check lengths */
  Py_ssize_t data_length = PyObject_Length(data);
  if (data_length == -1) return -1;
  Py_ssize_t target_length = PyObject_Length(target);
  if (target_length == -1) return -1;

  if (data_length < 2) {
    PyErr_Format(PyExc_RuntimeError, "`%s' requires an iterable for parameter `data' leading to, at least, two entries (representing two classes), but you have passed something that has only %" PY_FORMAT_SIZE_T "d entries", Py_TYPE(self)->tp_name, data_length);
    return 0;
  }

  if (target_length != data_length) {
    PyErr_Format(PyExc_RuntimeError, "`%s' requires an iterable for parameter `target' leading to the same number of targets (%" PY_FORMAT_SIZE_T "d) as data arrays, but you have passed something that has only %" PY_FORMAT_SIZE_T "d entries", Py_TYPE(self)->tp_name, data_length, target_length);
    return 0;
  }

  /* Checks and converts all data entries */
  std::vector<blitz::Array<double,2> > data_seq;
  std::vector<boost::shared_ptr<PyBlitzArrayObject>> data_seq_;

  PyObject* iterator = PyObject_GetIter(data);
  if (!iterator) return 0;
  auto iterator_ = make_safe(iterator);

  while (PyObject* item = PyIter_Next(iterator)) {
    auto item_ = make_safe(item);

    PyBlitzArrayObject* bz = 0;

    if (!PyBlitzArray_Converter(item, &bz)) {
      PyErr_Format(PyExc_TypeError, "`%s' could not convert object of type `%s' at position %" PY_FORMAT_SIZE_T "d of input sequence `data' into an array - check your input", Py_TYPE(self)->tp_name, Py_TYPE(item)->tp_name, data_seq.size());
      return 0;
    }

    if (bz->ndim != 2 || bz->type_num != NPY_FLOAT64) {
      PyErr_Format(PyExc_TypeError, "`%s' only supports 2D 64-bit float arrays for input sequence `data' (or any other object coercible to that), but at position %" PY_FORMAT_SIZE_T "d I have found an object with %" PY_FORMAT_SIZE_T "d dimensions and with type `%s' which is not compatible - check your input", Py_TYPE(self)->tp_name, data_seq.size(), bz->ndim, PyBlitzArray_TypenumAsString(bz->type_num));
      Py_DECREF(bz);
      return 0;
    }

    data_seq_.push_back(make_safe(bz)); ///< prevents data deletion
    data_seq.push_back(*PyBlitzArrayCxx_AsBlitz<double,2>(bz)); ///< only a view!
  }

  if (PyErr_Occurred()) return 0;

  /* Checks and converts all target entries */
  std::vector<blitz::Array<double,1>> target_seq;
  std::vector<boost::shared_ptr<PyBlitzArrayObject>> target_seq_;

  iterator = PyObject_GetIter(target);
  if (!iterator) return 0;
  iterator_ = make_safe(iterator);

  while (PyObject* item = PyIter_Next(iterator)) {
    auto item_ = make_safe(item);

    PyBlitzArrayObject* bz = 0;

    if (!PyBlitzArray_Converter(item, &bz)) {
      PyErr_Format(PyExc_TypeError, "`%s' could not convert object of type `%s' at position %" PY_FORMAT_SIZE_T "d of input sequence `target' into an array - check your input", Py_TYPE(self)->tp_name, Py_TYPE(item)->tp_name, target_seq.size());
      return 0;
    }

    if (bz->ndim != 1 || bz->type_num != NPY_FLOAT64) {
      PyErr_Format(PyExc_TypeError, "`%s' only supports 1D 64-bit float arrays for input sequence `target' (or any other object coercible to that), but at position %" PY_FORMAT_SIZE_T "d I have found an object with %" PY_FORMAT_SIZE_T "d dimensions and with type `%s' which is not compatible - check your input", Py_TYPE(self)->tp_name, target_seq.size(), bz->ndim, PyBlitzArray_TypenumAsString(bz->type_num));
      Py_DECREF(bz);
      return 0;
    }

    target_seq_.push_back(make_safe(bz)); ///< prevents target deletion
    target_seq.push_back(*PyBlitzArrayCxx_AsBlitz<double,1>(bz)); ///< only a view!
  }

  if (PyErr_Occurred()) return 0;

  // proceed to object initialization
  try {
    self->cxx = new bob::trainer::DataShuffler(data_seq, target_seq);
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

int PyBobLearnDataShuffler_Check(PyObject* o) {
  return PyObject_IsInstance(o, reinterpret_cast<PyObject*>(&PyBobLearnDataShuffler_Type));
}

PyTypeObject PyBobLearnDataShuffler_Type = {
    PyVarObject_HEAD_INIT(0, 0)
    s_shuffler_str,                           /* tp_name */
    sizeof(PyBobLearnDataShufflerObject),     /* tp_basicsize */
    0,                                        /* tp_itemsize */
    0,                                        /* tp_dealloc */
    0,                                        /* tp_print */
    0,                                        /* tp_getattr */
    0,                                        /* tp_setattr */
    0,                                        /* tp_compare */
    0,                                        /* tp_repr */
    0,                                        /* tp_as_number */
    0,                                        /* tp_as_sequence */
    0,                                        /* tp_as_mapping */
    0,                                        /* tp_hash */
    0,                                        /* tp_call */
    0,                                        /* tp_str */
    0,                                        /* tp_getattro */
    0,                                        /* tp_setattro */
    0,                                        /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    s_shuffler_doc,                           /* tp_doc */
    0,                                        /* tp_traverse */
    0,                                        /* tp_clear */
    0,                                        /* tp_richcompare */
    0,                                        /* tp_weaklistoffset */
    0,                                        /* tp_iter */
    0,                                        /* tp_iternext */
    0,                                        /* tp_methods */
    0,                                        /* tp_members */
    0,                                        /* tp_getset */
    0,                                        /* tp_base */
    0,                                        /* tp_dict */
    0,                                        /* tp_descr_get */
    0,                                        /* tp_descr_set */
    0,                                        /* tp_dictoffset */
    (initproc)PyBobLearnDataShuffler_init,    /* tp_init */
};
