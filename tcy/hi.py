import cython

@cython.cdef
def h():
  return 'hi'

def hi():
  return h()
