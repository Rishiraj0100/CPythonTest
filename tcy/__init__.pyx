from libc.math cimport pow
from hi cimport hi as _hi

cdef double square_and_add (double x):
    return pow(x, 2.0) + x

cpdef print_result (double x):
    print("({} ^ 2) + {} = {}".format(x, x, square_and_add(x)))

cpdef get_hi ():
  return hi()
