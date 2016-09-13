.. _Usage:

Usage
===============

This page explains how to use SuperElastix.

Commandline tool
----------------

The SuperElastix commandline tool can be found at:
  
- Windows: :code:`<build-path>\SuperElastix-build\bin\Release` 
- Linux: :code:`<build-path>/SuperElastix-build/bin/` 

Demo Experiments
----------------

To run the demo experiments SuperElastix needs to be installed:

- Windows:

  - open :code:`<build-path>\SuperElastix-build\SuperElastix.sln`
  - in project solution explorer right-click on INSTALL -> Project Only -> Build Only INSTALL
  
- Linux: 

  - change dir to :code:`<build-path>/SuperElastix-build/`
  - :code:`make install`

The four Demo experiments as described in [1]_:

- :code:`1A_SuperElastix_elastix_NC`
- :code:`1B_SuperElastix_elastix_MSD`
- :code:`2A_SuperElastix_itkv4_NC`
- :code:`2B_SuperElastix_itkv4_MSD`
can be found in :code:`<build-path>/SuperElastix-build/bin/installed/Scripts_[Windows|Linux]/`

.. [1] *The design of SuperElastix - a unifying framework for a wide range of image registration methodologies, F. Berendsen, K. Marstal, S. Klein and M. Staring*, found at :code:`<source-path>\Documentation\source\paperWBIR16`.


Library use
-----------

To be written

- please take a look at :code:`commandline.cxx` or :code:`WBIRDemoTest.cxx`