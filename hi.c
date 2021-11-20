#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *py_str(const char *txt) {
  Py_BuildValue("s", txt);
}

static PyObject *py_int(const char *txt) {
  Py_BuildValue("i", txt);
}

static char *mk_hi() {
  return "Hi";
}

static PyObject *hello(PyObject *self) {
  return py_str(mk_hi());
}

typedef struct  {
  PyObject_HEAD

  long size;
  int *data;
} PyListObj;

static PyObject *PyListObj_add(struct PyListObj *self) {
  self->state++;
  return py_int(self->state);
}
static PyObject *PyListObj_sub(struct PyListObj *self) {
  self->state--;
  return py_int(self->state);
}

static int PyListObj_init(struct PyListObj *self, PyObject *args) {
    long size=0;

    if (!PyArg_ParseTuple(args, "l", &size)) {
        return -1;
    }

    self->data = calloc((size_t)size, sizeof(long));
    if (NULL == self->data) {
        PyErr_SetString(PyExc_MemoryError,"out of memory");
        return -1;
    }
    self->size = size;
    self->state = 0;
    return 0;
}
static PyObject *PyListObj_asn(struct PyListObj *self) {
  return py_int(self->state);
}
static PyObject *PyListObj_repr(struct PyListObj *self) {
  char repr;

  sprintf(repr, "size=%d", self->size);
  return py_str(repr);
}
static PyMethodDef PyListObj_methods[] = {
  {"add", (PyCFunction) PyListObj_add, METH_NOARGS, "add 1"},
  {"sub", (PyCFunction) PyListObj_sub, METH_NOARGS, "minus 1"},
  {NULL}  /* Sentinel */
};

static PyTypeObject PyListObjType = {
    PyVarObject_HEAD_INIT(NULL,0)
    .tp_name = "tcy.List",
    .tp_basicsize = sizeof(struct PyListObj),
    .tp_repr = (reprfunc)PyIntArrayObject_repr,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "Integer array Class",
    .tp_methods = PyIntArrayObject_methods,
    .tp_init = (initproc)PyIntArrayObject_init,
    .tp_new = PyType_GenericNew,
    .tp_as_number = PyListObj_asn,
}

static PyMethodDef helloworld_funcs[] = {
  {
    "hello",
    hello,
    METH_NOARGS,
    "Hello world description."
  },
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef helloworld_mod = {
  PyModuleDef_HEAD_INIT,
  "helloworld",
  "This is hello world module.",
 -1,
  helloworld_funcs
};

PyMODINIT_FUNC PyInit_tcy(void) {
  if (PyType_Ready(&PyListObjType) < 0) {
    return NULL;
  }
  m = PyModule_Create(&helloworld_mod);
  if (m==NULL) {
    return NULL;
  }
  Py_INCREF(&PyIntArrayType);
  PyModule_AddObject(m, "List", (PyObject *)&PyListObjType);
  return m;
}
