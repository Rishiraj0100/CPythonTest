import random

from setuptools import setup
from Cython.Build import cythonize


v = "0.0.1a"
ls = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

for i in range(5):
  v += ls[random.randint(0, len(ls)-1)]

setup(
    name = "_tcy",
    version = v,
    ext_modules = cythonize("tcy/*.pyx"),
    zip_safe = False
)
