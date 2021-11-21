#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *py_str(char *txt) {
  return Py_BuildValue("s", txt);
};

static PyObject *py_int(long txt) {
  return Py_BuildValue("i", txt);
};

static char *mk_hi() {
  return "Hi";
};

static PyObject *hello(PyObject *self) {
  return py_str(mk_hi());
};

typedef struct  {
  PyObject_HEAD

  int num;
} PyListObj;

static PyObject *PyListObj_add(PyListObj *self, PyObject *args) {
  int num = 1;
  if (!PyArg_ParseTuple(args, "i", &num)) {
    num = 1;
  }
  self->num = self->num + num;
  return py_int(self->num);
};
static PyObject *PyListObj_sub(PyListObj *self, PyObject *args) {
  int num = 1;
  if (!PyArg_ParseTuple(args, "i", &num)) {
    num = 1;
  }
  self->num = self->num - num;
  return py_int(self->num);
};
static PyObject *PyListObj_mul(PyListObj *self, PyObject *args) {
  int num = 1;
  if (!PyArg_ParseTuple(args, "i", &num)) {
    num = 1;
  }
  self->num = self->num * num;
  return py_int(self->num);
};
static PyObject *PyListObj_div(PyListObj *self, PyObject *args) {
  int num = 1;
  if (!PyArg_ParseTuple(args, "i", &num)) {
    num = 1;
  }
  self->num = self->num / num;
  return py_int(self->num);
};
static int PyListObj_init(PyListObj *self, PyObject *args) {
    int num;

    if (!PyArg_ParseTuple(args, "i", &num)) {
        num = 0;
    }
    self->num = num;
    return 0;
}
static PyObject *PyListObj_asn(PyListObj *self) {
  return py_int(self->num);
};

static PyObject *PyListObj_as_s(PyListObj *self) {
  return py_str(self->num);
};
static PyObject *PyListObj_repr(PyListObj *self) {
  char repr;

  sprintf(repr, "%d", self->num);
  return py_str(repr);
};
static PyMethodDef PyListObj_methods[] = {
  {"add", (PyCFunction) PyListObj_add, METH_NOARGS, ".add(2)"},
  {"sub", (PyCFunction) PyListObj_sub, METH_NOARGS, ".sub(3)"},
  {"mul", (PyCFunction) PyListObj_mul, METH_NOARGS, ".mul(5)"},
  {"div", (PyCFunction) PyListObj_div, METH_NOARGS, ".div(5)"},
  {"__add__", (PyCFunction) PyListObj_add, METH_NOARGS, "+ 1"},
  {"__sub__", (PyCFunction) PyListObj_sub, METH_NOARGS, "- 1"},
  {"__mul__", (PyCFunction) PyListObj_mul, METH_NOARGS, "* 1"},
  {"__truediv__", (PyCFunction) PyListObj_div, METH_NOARGS, "/ 5"},
  {NULL}  /* Sentinel */
};

static PyTypeObject PyListObjType = {
    PyVarObject_HEAD_INIT(NULL,0)
    .tp_name = "tcy.Number",
    .tp_basicsize = sizeof(PyListObj),
    .tp_repr = (reprfunc)PyListObj_repr,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "Integer array Class",
    .tp_methods = PyListObj_methods,
    .tp_init = (initproc)PyListObj_init,
    .tp_new = PyType_GenericNew,
    .tp_as_number = PyListObj_asn,
    .tp_str = PyListObj_as_s,
};

static PyMethodDef helloworld_funcs[] = {
  {
    "hello",
    (PyCFunction)hello,
    METH_NOARGS,
    "Hello world description."
  },
  {NULL}
};

static struct PyModuleDef helloworld_mod = {
  PyModuleDef_HEAD_INIT,
  "helloworld",
  "This is hello world module.",
 -1,
  helloworld_funcs
};

PyMODINIT_FUNC PyInit_tcy(void) {
  PyObject *m;
  if (PyType_Ready(&PyListObjType) < 0) {
    return NULL;
  }
  m = PyModule_Create(&helloworld_mod);
  if (m==NULL) {
    return NULL;
  }
  Py_INCREF(&PyListObjType);
  PyModule_AddObject(m, "Number", (PyObject *)&PyListObjType);
  return m;
}
