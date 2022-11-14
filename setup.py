from setuptools import setup, Extension
ext = Extension('benchtools', sources=["main.c", "benchmark.c"])
setup(
      name="BenchTools",
      version="1.0.0-b0",
      description="Is an simple bench tool.",
      author="Bruno Dalagnol",
      author_email="dalagnolbruno88@gmail.com",
      license="MIT",
      url="https://github.com/PothpothBR/benchtools",
      ext_modules=[ext]
)