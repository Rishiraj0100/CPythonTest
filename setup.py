import random
import numpy as np

from setuptools import setup, extension
from Cython.Build import cythonize
from Cython.Distutils import build_ext


SRC_DIR="tcy"
e = Extension(SRC_DIR + ".hi",
                  [SRC_DIR + "/hi.pyx"],
                  libraries=[],
                  include_dirs=[np.get_include()])


v = "0.0.1a"
ls = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

for i in range(5):
  v += ls[random.randint(0, len(ls)-1)]

setup(
    name = "_tcy",
    version = v,
    ext_modules = [e],
    zip_safe = False,
    cmdclass={"build_ext": build_ext}
)
