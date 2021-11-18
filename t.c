#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *hello(PyObject *self) {
  return PyUnicode_FromFormat("Hello C extension!");
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

PyMODINIT_FUNC PyInit_t(void) {
	return PyModule_Create(&helloworld_mod);
}
