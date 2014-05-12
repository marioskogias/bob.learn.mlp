/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Thu 24 Apr 17:32:07 2014 CEST
 */

#ifndef XBOB_LEARN_MLP_H
#define XBOB_LEARN_MLP_H

#include <Python.h>
#include <boost/shared_ptr.hpp>
#include <xbob.learn.mlp/config.h>

#include "machine.h"
#include "cost.h"
#include "square_error.h"
#include "cross_entropy.h"
#include "shuffler.h"
#include "trainer.h"
#include "backprop.h"

#define XBOB_LEARN_MLP_MODULE_PREFIX xbob.learn.mlp
#define XBOB_LEARN_MLP_MODULE_NAME _library

/*******************
 * C API functions *
 *******************/

/* Enum defining entries in the function table */
enum _PyBobLearnMLP_ENUM {
  PyXbobLearnMLP_APIVersion_NUM = 0,
  // Bindings for xbob.learn.mlp.Machine
  PyBobLearnMLPMachine_Type_NUM,
  PyBobLearnMLPMachine_Check_NUM,
  // Bindings for xbob.learn.mlp.Cost and variants
  PyBobLearnCost_Type_NUM,
  PyBobLearnCost_Check_NUM,
  PyBobLearnCost_NewFromCost_NUM,
  PyBobLearnSquareError_Type_NUM,
  PyBobLearnCrossEntropyLoss_Type_NUM,
  // Bindings for xbob.learn.mlp.DataShuffler
  PyBobLearnDataShuffler_Type_NUM,
  PyBobLearnDataShuffler_Check_NUM,
  // Bindings for xbob.learn.mlp.Trainer
  PyBobLearnMLPTrainer_Type_NUM,
  PyBobLearnMLPTrainer_Check_NUM,
  PyBobLearnMLPBackProp_Type_NUM,
  PyBobLearnMLPBackProp_Check_NUM,
  // Total number of C API pointers
  PyXbobLearnMLP_API_pointers
};

/**************
 * Versioning *
 **************/

#define PyXbobLearnMLP_APIVersion_TYPE int

/***************************************
 * Bindings for xbob.learn.mlp.Machine *
 ***************************************/

typedef struct {
  PyObject_HEAD
  bob::learn::mlp::Machine* cxx;
} PyBobLearnMLPMachineObject;

#define PyBobLearnMLPMachine_Type_TYPE PyTypeObject

#define PyBobLearnMLPMachine_Check_RET int
#define PyBobLearnMLPMachine_Check_PROTO (PyObject* o)

typedef struct {
  PyObject_HEAD
  boost::shared_ptr<bob::learn::mlp::Cost> cxx;
} PyBobLearnCostObject;

#define PyBobLearnCost_Type_TYPE PyTypeObject

#define PyBobLearnCost_Check_RET int
#define PyBobLearnCost_Check_PROTO (PyObject* o)

#define PyBobLearnCost_NewFromCost_RET PyObject*
#define PyBobLearnCost_NewFromCost_PROTO (boost::shared_ptr<bob::learn::mlp::Cost>)

typedef struct {
  PyBobLearnCostObject parent;
  boost::shared_ptr<bob::learn::mlp::SquareError> cxx;
} PyBobLearnSquareErrorObject;

#define PyBobLearnSquareError_Type_TYPE PyTypeObject

typedef struct {
  PyBobLearnCostObject parent;
  boost::shared_ptr<bob::learn::mlp::CrossEntropyLoss> cxx;
} PyBobLearnCrossEntropyLossObject;

#define PyBobLearnCrossEntropyLoss_Type_TYPE PyTypeObject

typedef struct {
  PyObject_HEAD
  bob::learn::mlp::DataShuffler* cxx;
} PyBobLearnDataShufflerObject;

#define PyBobLearnDataShuffler_Type_TYPE PyTypeObject

#define PyBobLearnDataShuffler_Check_RET int
#define PyBobLearnDataShuffler_Check_PROTO (PyObject* o)

/***************************************
 * Bindings for xbob.learn.mlp.Trainer *
 ***************************************/

typedef struct {
  PyObject_HEAD
  bob::learn::mlp::Trainer* cxx;
} PyBobLearnMLPTrainerObject;

#define PyBobLearnMLPTrainer_Type_TYPE PyTypeObject

#define PyBobLearnMLPTrainer_Check_RET int
#define PyBobLearnMLPTrainer_Check_PROTO (PyObject* o)

typedef struct {
  PyBobLearnMLPTrainerObject parent;
  bob::learn::mlp::BackProp* cxx;
} PyBobLearnMLPBackPropObject;

#define PyBobLearnMLPBackProp_Type_TYPE PyTypeObject

#define PyBobLearnMLPBackProp_Check_RET int
#define PyBobLearnMLPBackProp_Check_PROTO (PyObject* o)

#ifdef XBOB_LEARN_MLP_MODULE

  /* This section is used when compiling `xbob.learn.mlp' itself */

  /**************
   * Versioning *
   **************/

  extern int PyXbobLearnMLP_APIVersion;

  /***************************************
   * Bindings for xbob.learn.mlp.Machine *
   ***************************************/

  extern PyBobLearnMLPMachine_Type_TYPE PyBobLearnMLPMachine_Type;

  PyBobLearnMLPMachine_Check_RET PyBobLearnMLPMachine_Check PyBobLearnMLPMachine_Check_PROTO;

  /************************************
   * Bindings for xbob.learn.mlp.Cost *
   ************************************/

  extern PyBobLearnCost_Type_TYPE PyBobLearnCost_Type;

  PyBobLearnCost_Check_RET PyBobLearnCost_Check PyBobLearnCost_Check_PROTO;

  extern PyBobLearnSquareError_Type_TYPE PyBobLearnSquareError_Type;

  extern PyBobLearnCrossEntropyLoss_Type_TYPE PyBobLearnCrossEntropyLoss_Type;

  PyBobLearnCost_NewFromCost_RET PyBobLearnCost_NewFromCost PyBobLearnCost_NewFromCost_PROTO;

  /********************************************
   * Bindings for xbob.learn.mlp.DataShuffler *
   ********************************************/

  extern PyBobLearnDataShuffler_Type_TYPE PyBobLearnDataShuffler_Type;

  PyBobLearnDataShuffler_Check_RET PyBobLearnDataShuffler_Check PyBobLearnDataShuffler_Check_PROTO;

  /***************************************
   * Bindings for xbob.learn.mlp.Trainer *
   ***************************************/

  extern PyBobLearnMLPTrainer_Type_TYPE PyBobLearnMLPTrainer_Type;

  PyBobLearnMLPTrainer_Check_RET PyBobLearnMLPTrainer_Check PyBobLearnMLPTrainer_Check_PROTO;

  extern PyBobLearnMLPBackProp_Type_TYPE PyBobLearnMLPBackProp_Type;

  PyBobLearnMLPBackProp_Check_RET PyBobLearnMLPBackProp_Check PyBobLearnMLPBackProp_Check_PROTO;

#else

  /* This section is used in modules that use `xbob.learn.mlp's' C-API */

/************************************************************************
 * Macros to avoid symbol collision and allow for separate compilation. *
 * We pig-back on symbols already defined for NumPy and apply the same  *
 * set of rules here, creating our own API symbol names.                *
 ************************************************************************/

#  if defined(PY_ARRAY_UNIQUE_SYMBOL)
#    define XBOB_LEARN_MLP_MAKE_API_NAME_INNER(a) XBOB_LEARN_MLP_ ## a
#    define XBOB_LEARN_MLP_MAKE_API_NAME(a) XBOB_LEARN_MLP_MAKE_API_NAME_INNER(a)
#    define PyXbobLearnMLP_API XBOB_LEARN_MLP_MAKE_API_NAME(PY_ARRAY_UNIQUE_SYMBOL)
#  endif

#  if defined(NO_IMPORT_ARRAY)
  extern void **PyXbobLearnMLP_API;
#  else
#    if defined(PY_ARRAY_UNIQUE_SYMBOL)
  void **PyXbobLearnMLP_API;
#    else
  static void **PyXbobLearnMLP_API=NULL;
#    endif
#  endif

  /**************
   * Versioning *
   **************/

# define PyXbobLearnMLP_APIVersion (*(PyXbobLearnMLP_APIVersion_TYPE *)PyXbobLearnMLP_API[PyXbobLearnMLP_APIVersion_NUM])

  /***************************************
   * Bindings for xbob.learn.mlp.Machine *
   ***************************************/

# define PyBobLearnMLPMachine_Type (*(PyBobLearnMLPMachine_Type_TYPE *)PyXbobLearnMLP_API[PyBobLearnMLPMachine_Type_NUM])

# define PyBobLearnMLPMachine_Check (*(PyBobLearnMLPMachine_Check_RET (*)PyBobLearnMLPMachine_Check_PROTO) PyXbobLearnMLP_API[PyBobLearnMLPMachine_Check_NUM])

  /************************************
   * Bindings for xbob.learn.mlp.Cost *
   ************************************/

# define PyBobLearnCost_Type (*(PyBobLearnCost_Type_TYPE *)PyXbobLearnMLP_API[PyBobLearnCost_Type_NUM])

# define PyBobLearnCost_Check (*(PyBobLearnCost_Check_RET (*)PyBobLearnCost_Check_PROTO) PyXbobLearnMLP_API[PyBobLearnCost_Check_NUM])

# define PyBobLearnCost_NewFromCost (*(PyBobLearnCost_NewFromCost_RET (*)PyBobLearnCost_NewFromCost_PROTO) PyXbobLearnMLP_API[PyBobLearnCost_NewFromCost_NUM])

# define PyBobLearnSquareError_Type (*(PyBobLearnSquareError_Type_TYPE *)PyXbobLearnMLP_API[PyBobLearnSquareError_Type_NUM])

# define PyBobLearnCrossEntropyLoss_Type (*(PyBobLearnCrossEntropyLoss_Type_TYPE *)PyXbobLearnMLP_API[PyBobLearnCrossEntropyLoss_Type_NUM])

  /********************************************
   * Bindings for xbob.learn.mlp.DataShuffler *
   ********************************************/

# define PyBobLearnDataShuffler_Type (*(PyBobLearnDataShuffler_Type_TYPE *)PyXbobLearnMLP_API[PyBobLearnDataShuffler_Type_NUM])

# define PyBobLearnDataShuffler_Check (*(PyBobLearnDataShuffler_Check_RET (*)PyBobLearnDataShuffler_Check_PROTO) PyXbobLearnMLP_API[PyBobLearnDataShuffler_Check_NUM])

  /***************************************
   * Bindings for xbob.learn.mlp.Trainer *
   ***************************************/

# define PyBobLearnMLPTrainer_Type (*(PyBobLearnMLPTrainer_Type_TYPE *)PyXbobLearnMLP_API[PyBobLearnMLPTrainer_Type_NUM])

# define PyBobLearnMLPTrainer_Check (*(PyBobLearnMLPTrainer_Check_RET (*)PyBobLearnMLPTrainer_Check_PROTO) PyXbobLearnMLP_API[PyBobLearnMLPTrainer_Check_NUM])

# define PyBobLearnMLPBackProp_Type (*(PyBobLearnMLPBackProp_Type_TYPE *)PyXbobLearnMLP_API[PyBobLearnMLPBackProp_Type_NUM])

# define PyBobLearnMLPBackProp_Check (*(PyBobLearnMLPBackProp_Check_RET (*)PyBobLearnMLPBackProp_Check_PROTO) PyXbobLearnMLP_API[PyBobLearnMLPBackProp_Check_NUM])

# if !defined(NO_IMPORT_ARRAY)

  /**
   * Returns -1 on error, 0 on success. PyCapsule_Import will set an exception
   * if there's an error.
   */
  static int import_xbob_learn_mlp(void) {

    PyObject *c_api_object;
    PyObject *module;

    module = PyImport_ImportModule(BOOST_PP_STRINGIZE(XBOB_LEARN_MLP_MODULE_PREFIX) "." BOOST_PP_STRINGIZE(XBOB_LEARN_MLP_MODULE_NAME));

    if (module == NULL) return -1;

    c_api_object = PyObject_GetAttrString(module, "_C_API");

    if (c_api_object == NULL) {
      Py_DECREF(module);
      return -1;
    }

#   if PY_VERSION_HEX >= 0x02070000
    if (PyCapsule_CheckExact(c_api_object)) {
      PyXbobLearnMLP_API = (void **)PyCapsule_GetPointer(c_api_object,
          PyCapsule_GetName(c_api_object));
    }
#   else
    if (PyCObject_Check(c_api_object)) {
      XbobLearnMLP_API = (void **)PyCObject_AsVoidPtr(c_api_object);
    }
#   endif

    Py_DECREF(c_api_object);
    Py_DECREF(module);

    if (!XbobLearnMLP_API) {
      PyErr_Format(PyExc_ImportError,
#   if PY_VERSION_HEX >= 0x02070000
          "cannot find C/C++ API capsule at `%s.%s._C_API'",
#   else
          "cannot find C/C++ API cobject at `%s.%s._C_API'",
#   endif
          BOOST_PP_STRINGIZE(XBOB_LEARN_MLP_MODULE_PREFIX),
          BOOST_PP_STRINGIZE(XBOB_LEARN_MLP_MODULE_NAME));
      return -1;
    }

    /* Checks that the imported version matches the compiled version */
    int imported_version = *(int*)PyXbobLearnMLP_API[PyXbobLearnMLP_APIVersion_NUM];

    if (XBOB_LEARN_MLP_API_VERSION != imported_version) {
      PyErr_Format(PyExc_ImportError, "%s.%s import error: you compiled against API version 0x%04x, but are now importing an API with version 0x%04x which is not compatible - check your Python runtime environment for errors", BOOST_PP_STRINGIZE(XBOB_LEARN_MLP_MODULE_PREFIX), BOOST_PP_STRINGIZE(XBOB_LEARN_MLP_MODULE_NAME), XBOB_LEARN_MLP_API_VERSION, imported_version);
      return -1;
    }

    /* If you get to this point, all is good */
    return 0;

  }

# endif //!defined(NO_IMPORT_ARRAY)

#endif /* XBOB_LEARN_MLP_MODULE */

#endif /* XBOB_LEARN_MLP_H */
