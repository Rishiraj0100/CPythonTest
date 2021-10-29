import random

from distutils.core import Extension, setup
from Cython.Build import cythonize as _c


def c(_):
  return _c(_)[0]

v = "0.0.1a"
ls = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

for i in range(5):
  v += ls[random.randint(0, len(ls)-1)]

ext = Extension(name="tcy", sources=["tcy/__init__.pyx",])
ext2 = Extension(name="tcy.hi", sources=["tcy/hi.pyx",])
setup(ext_modules=[c(ext), c(ext2)], version=v,name="tcy")
