import random

from setuptools import Extension as E, setup

# from Cython.Build import cythonize as _c


# def c(_):
#   return _c(_)[0]

v = "0.0.1a"
ls = "1234567890"+"000001111222334"+"555556666777889"

for i in range(3):
  v += ls[random.randint(0, len(ls)-1)]

# ext = Extension(name="tcy", sources=["tcy/__init__.pyx",])
# ext2 = Extension(name="tcy.hell", sources=["tcy/hi.pyx",])

setup(ext_modules=[E(name="tcy", sources=["hi.c"])], version=v,name="tcy")
