from setuptools import setup, Extension

from pathlib import Path
this_directory = Path(__file__).parent
long_description = (this_directory / "README.md").read_text()

ext = Extension(
      'benchtools',
      sources=["src/main.c", "src/benchmark.c"],
      include_dirs=["src/"]
)

setup(
      name="BenchTools",
      version="1.0.3.rev2",
      description="Is an simple bench tool.",
      author="Bruno Dalagnol",
      author_email="dalagnolbruno88@gmail.com",
      license="MIT",
      url="https://github.com/PothpothBR/benchtools",
      ext_modules=[ext],
      long_description=long_description,
      long_description_content_type='text/markdown'
)