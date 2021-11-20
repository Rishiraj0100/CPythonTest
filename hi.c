#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *str(const char *txt) {
  Py_BuildValue("s", txt);
}
static char *gethi() {
  return "Hi";
}
static PyObject *hello(PyObject *self, PyObject *a) {
  return str(gethi());
}

static PyMethodDef helloworld_funcs[] = {
  {
    "hello",
    hello,
    METH_VARARGS,
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

PyMODINIT_FUNC PyInit_hi(void) {
  return PyModule_Create(&helloworld_mod);
}
