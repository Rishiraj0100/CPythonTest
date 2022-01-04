#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *py_str(char *txt) {
  return Py_BuildValue("s", txt);
};

static PyObject *py_slf(int txt) {
  return PyObject_CallOneArg(PyObject_GetAttrString(PyImport_ImportModule("tcy"),"Number"),py_int(txt));
};

static PyObject *py_int(int txt) {
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
} PyNumObj;

static PyObject *PyNumObj_add(PyNumObj *self, PyObject *args) {
  int num = 1;
  if (!PyArg_ParseTuple(args, "i", &num)) {
    num = 1;
  }
  self->num = self->num + num;
  return py_slf(self->num);
};
static PyObject *PyNumObj_sub(PyNumObj *self, PyObject *args) {
  int num = 1;
  if (!PyArg_ParseTuple(args, "i", &num)) {
    num = 1;
  }
  self->num = self->num - num;
  return py_slf(self->num);
};
static PyObject *PyNumObj_mul(PyNumObj *self, PyObject *args) {
  int num = 1;
  if (!PyArg_ParseTuple(args, "i", &num)) {
    num = 1;
  }
  self->num = self->num * num;
  return py_slf(self->num);
};
static PyObject *PyNumObj_div(PyNumObj *self, PyObject *args) {
  int num = 1;
  if (!PyArg_ParseTuple(args, "i", &num)) {
    num = 1;
  }
  self->num = self->num / num;
  return py_slf(self->num);
};
static int PyNumObj_init(PyNumObj *self, PyObject *args) {
    int num = 0;

    if (!PyArg_ParseTuple(args, "i", &num)) {
        num = 1;
    }
    self->num = num;
    return 0;
}
static PyObject *PyNumObj_asn(PyNumObj *self) {
  return py_int(self->num);
};

static PyObject *PyNumObj_as_s(PyNumObj *self) {
  char repr;

  sprintf(repr, "%d", self->num);
  return py_str(repr);
};
static PyObject *PyNumObj_repr(PyNumObj *self) {
  char repr;

  sprintf(repr, "%d", self->num);
  return py_str(repr);
};
static PyMethodDef PyNumObj_methods[] = {
  {"add", (PyCFunction) PyNumObj_add, METH_VARARGS, ".add(2)"},
  {"sub", (PyCFunction) PyNumObj_sub, METH_VARARGS, ".sub(3)"},
  {"mul", (PyCFunction) PyNumObj_mul, METH_VARARGS, ".mul(5)"},
  {"div", (PyCFunction) PyNumObj_div, METH_VARARGS, ".div(5)"},
  {"__repr__", (PyCFunction) PyNumObj_repr, METH_NOARGS, ""},
  {"__int__", (PyCFunction) PyNumObj_asn, METH_NOARGS, ""},
  {"__str__", (PyCFunction) PyNumObj_as_s, METH_NOARGS, ""},
  {NULL}  /* Sentinel */
};
/*
static PyNumberMethods PyNumObj_as_n_ = {
    .nb_add = PyNumObj_add,
};
*/
static PyTypeObject PyNumObjType = {
    PyVarObject_HEAD_INIT(NULL,0)
    .tp_name = "tcy.Number",
    .tp_basicsize = sizeof(PyNumObj),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Custom Int Class",
    .tp_methods = PyNumObj_methods,
    .tp_init = PyNumObj_init,
    .tp_new = PyType_GenericNew,
/*    .tp_as_number = &PyNumObj_as_n_,*/
};

static PyMethodDef helloworld_funcs[] = {
  {
    "hello",
    (PyCFunction)hello,
    METH_NOARGS,
    "Hello world description."
  },
  {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef helloworld_mod = {
  PyModuleDef_HEAD_INIT,
  .m_name = "helloworld",
  .m_doc = "This is hello world module.",
  .m_size = -1,
  .m_methods = helloworld_funcs
};

PyMODINIT_FUNC PyInit_tcy(void) {
  PyObject *m;
  Py_INCREF(&PyNumObjType);
  if (PyType_Ready(&PyNumObjType) < 0) {
    Py_DECREF(&PyNumObjType);
    return NULL;
  }
  Py_INCREF(&helloworld_mod);
  m = PyModule_Create(&helloworld_mod);
  Py_INCREF(m);
  if (m==NULL) {
    Py_DECREF(m);
    return NULL;
  }
  Py_INCREF(&PyNumObjType);
  if (PyModule_AddObject(m, "Number", (PyObject *)&PyNumObjType) < 0) {
    Py_DECREF(&PyNumObjType);
    Py_DECREF(m);
    return NULL;
  }
  return m;
}
