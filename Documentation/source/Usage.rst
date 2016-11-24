.. _Usage:

Usage
===============

This page explains how to use SuperElastix.

Commandline tool
----------------

The SuperElastix commandline tool can be found at:
  
- Windows: :code:`<build-path>\SuperElastixApplications-build\CommandlineProgram\Release` 
- Linux: :code:`<build-path>/SuperElastixApplications-build/CommandlineProgram/` 

Demo Experiments
----------------

To run the demo experiments SuperElastix needs to be installed:

- Windows:

  - open :code:`<build-path>\SuperElastixApplications-build\SuperElastixApplications.sln`
  - in project solution explorer right-click on InstallDemo -> Project Only -> Build Only InstallDemo
  
- Linux: 

  - change dir to :code:`<build-path>/SuperElastixApplications-build/`
  - :code:`make InstallDemo`

By building the :code:`InstallDemo` target the SuperElastix executable, image data, configuration files and commandline scripts will be copied to the :code:`<INSTALLDEMO_PREFIX>` directory. The :code:`<INSTALLDEMO_PREFIX>` can be set by CMake and defaults to :code:`<build-path>/SuperElastixApplications-build/Demo`
These four scripts run the Demo experiments as described in [1]_:

- :code:`1A_SuperElastix_elastix_NC`
- :code:`1B_SuperElastix_elastix_MSD`
- :code:`2A_SuperElastix_itkv4_NC`
- :code:`2B_SuperElastix_itkv4_MSD`

.. [1] *The design of SuperElastix - a unifying framework for a wide range of image registration methodologies, F. Berendsen, K. Marstal, S. Klein and M. Staring*, found at :code:`<source-path>\Documentation\source\paperWBIR16`.


Library use
-----------

- The SuperElastix commandline tool in :code:`<source-path>\Applications` serves as an example of the usage of the SuperElastix library.
