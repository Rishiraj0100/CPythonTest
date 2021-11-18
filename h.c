#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *hello(PyObject *self) {
	return PyUnicode_FromFormat("Hello C extension!");
}

char hellofunc_docs[] = "Hello world description.";

static PyMethodDef helloworld_funcs[] = {
  {
    "hello",
    hello,
    METH_NOARGS,
    hellofunc_docs
  },
  {NULL, NULL, 0, NULL}
};

char helloworldmod_docs[] = "This is hello world module.";

static struct PyModuleDef helloworld_mod = {
	PyModuleDef_HEAD_INIT,
	"helloworld",
	helloworldmod_docs,
	-1,
	helloworld_funcs
};

PyMODINIT_FUNC PyInit_t(void) {
	return PyModule_Create(&helloworld_mod);
}
