from setuptools import setup, Extension

ext = Extension(
      'benchtools',
      sources=["src/main.c", "src/benchmark.c"],
      include_dirs=["src/"]
)

setup(
      name="BenchTools",
      version="1.0.3",
      description="Is an simple bench tool.",
      author="Bruno Dalagnol",
      author_email="dalagnolbruno88@gmail.com",
      license="MIT",
      url="https://github.com/PothpothBR/benchtools",
      ext_modules=[ext]
)