from setuptools import setup, Extension
ext = Extension('benchtools', sources=["main.c", "benchmark.c"])
setup(
      ext_modules=[ext]
)