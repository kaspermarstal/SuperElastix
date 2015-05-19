Documentation
=============

This is the source code for the project documentation at [simpleelastix.readthedocs.org](http://simpleelastix.readthedocs.org/). The documentation is updated on every commit to the `Github repository <https://github.com/kaspermarstal/SuperElastix>`_. You can build it locally by installing sphinx: 

```bash
$ pip install sphinx
```

and run the following make command in `Documentation/`:

```bash
$ make html
```

The docs will be generated and the output files will be placed in the `build/html/` directory which can be browsed (locally) with your favorite browser. The documentation can be automatically generated whenever a file changes (useful for development) using `sphinx-autobuild`:

```bash
$ make livehtml
```

Install `sphinx-autobuild` with `pip install sphinx-autobuild`.
