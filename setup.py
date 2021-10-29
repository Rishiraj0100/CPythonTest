import random

from distutils.core import Extension, setup
from Cython.Build import cythonize


v = "0.0.1a"
ls = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

for i in range(5):
  v += ls[random.randint(0, len(ls)-1)]

ext = Extension(name="hello", sources=["tcy/__init__.pyx"])
setup(ext_modules=cythonize(ext), version=v,)
