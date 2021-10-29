from setuptools import setup
from Cython.Build import cythonize

setup(
    name = "_tcy",
    ext_modules = cythonize("tcy/*.py"),
    zip_safe = False
)
