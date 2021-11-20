#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *str(const char *txt) {
  Py_BuildValue("s", txt);
}

static char *gethi() {
  return "Hi";
}

static PyObject *hello(PyObject *self,) {
  return str(gethi());
}

static struct PyListObj {
  PyObject_HEAD

  long size;
  int *data;
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

    return 0;
}

static PyObject *PyListObj_repr(struct PyListObj *self) {
  char repr;

  sprintf(repr, "[%d]", self->size);
  return str(repr);
}
static PyMethodDef PyListObj_methods[] = {
  {NULL}
}
static PyTypeObject PyListObjType = {
    PyVarObject_HEAD_INIT,
    "tcy.List",
    sizeof(struct PyListObj),
    0,                         /*tp_itemsize*/
    0, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    (reprfunc)PyIntArrayObject_repr,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "Integer array Class",           /* tp_doc */
    0,                     /* tp_traverse */
    0,                     /* tp_clear */
    0,                     /* tp_richcompare */
    0,                     /* tp_weaklistoffset */
    0,                     /* tp_iter */
    0,                     /* tp_iternext */
    PyIntArrayObject_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)PyIntArrayObject_init,      /* tp_init */
    0,                         /* tp_alloc */
    PyType_GenericNew,                 /* tp_new */
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
