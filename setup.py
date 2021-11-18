import random

from setuptools import Extension as E, setup

# from Cython.Build import cythonize as _c


# def c(_):
#   return _c(_)[0]

v = "0.0.1a"
ls = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

for i in range(5):
  v += ls[random.randint(0, len(ls)-1)]

# ext = Extension(name="tcy", sources=["tcy/__init__.pyx",])
# ext2 = Extension(name="tcy.hell", sources=["tcy/hi.pyx",])

setup(ext_modules=[E(name="t", sources=["t.c"])], version=v,name="tcy")
