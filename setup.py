import random

from setuptools import setup
from Cython.Build import cythonize


v = "0.0.1a"
ls = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

for i in range(5):
  v += ls.index(random.randint(0, len(ls)-1))

setup(
    name = "_tcy",
    version = v
    ext_modules = cythonize("tcy/*.py"),
    zip_safe = False
)
