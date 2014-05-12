/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Tue  6 May 12:32:39 2014 CEST
 *
 * @brief Shared utilities
 *
 * Copyright (C) 2011-2014 Idiap Research Institute, Martigny, Switzerland
 */

#ifndef BOB_LEARN_MLP_UTILS_H
#define BOB_LEARN_MLP_UTILS_H

#define XBOB_LEARN_MLP_MODULE
#include <xbob.blitz/cppapi.h>
#include <xbob.blitz/cleanup.h>
#include <xbob.learn.mlp/api.h>

template <int N>
PyObject* convert_vector(const std::vector<blitz::Array<double,N>>& v) {
  PyObject* retval = PyTuple_New(v.size());
  auto retval_ = make_safe(retval);
  if (!retval) return 0;
  for (int k=0; k<v.size(); ++k) {
    auto arr = PyBlitzArrayCxx_NewFromConstArray(v[k]);
    if (!arr) return 0;
    PyTuple_SET_ITEM(retval, k, PyBlitzArray_NUMPY_WRAP(arr));
  }
  Py_INCREF(retval);
  return retval;
}

template <int N>
int convert_tuple(PyObject* self, const char* attr,
    PyObject* o, std::vector<blitz::Array<double,N>>& seq) {

  if (!PyIter_Check(o) && !PySequence_Check(o)) {
    PyErr_Format(PyExc_TypeError, "setting attribute `%s' of `%s' requires an iterable, but you passed `%s' which does not implement the iterator protocol", Py_TYPE(self)->tp_name, attr, Py_TYPE(o)->tp_name);
    return -1;
  }

  /* Checks and converts all entries */
  std::vector<boost::shared_ptr<PyBlitzArrayObject>> seq_;

  PyObject* iterator = PyObject_GetIter(o);
  if (!iterator) return -1;
  auto iterator_ = make_safe(iterator);

  while (PyObject* item = PyIter_Next(iterator)) {
    auto item_ = make_safe(item);

    PyBlitzArrayObject* bz = 0;

    if (!PyBlitzArray_Converter(item, &bz)) {
      PyErr_Format(PyExc_TypeError, "`%s' (while setting `%s') could not convert object of type `%s' at position %" PY_FORMAT_SIZE_T "d of input sequence into an array - check your input", Py_TYPE(self)->tp_name, attr, Py_TYPE(item)->tp_name, seq.size());
      return -1;
    }

    if (bz->ndim != N || bz->type_num != NPY_FLOAT64) {
      PyErr_Format(PyExc_TypeError, "`%s' only supports 2D 64-bit float arrays for attribute `%s' (or any other object coercible to that), but at position %" PY_FORMAT_SIZE_T "d I have found an object with %" PY_FORMAT_SIZE_T "d dimensions and with type `%s' which is not compatible - check your input", Py_TYPE(self)->tp_name, attr, seq.size(), bz->ndim, PyBlitzArray_TypenumAsString(bz->type_num));
      Py_DECREF(bz);
      return -1;
    }

    seq_.push_back(make_safe(bz)); ///< prevents data deletion
    seq.push_back(*PyBlitzArrayCxx_AsBlitz<double,N>(bz)); ///< only a view!
  }

  if (PyErr_Occurred()) return -1;

  return 0;
}

#endif /* BOB_LEARN_MLP_UTILS_H */
