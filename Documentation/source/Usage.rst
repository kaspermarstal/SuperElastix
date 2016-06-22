.. _Usage:

Usage
===============

This page explains how to use SuperElastix.

Commandline tool
----------------

The SuperElastix commandline tool can be found at:
  
- Window: :code:`<build-path>\SuperElastix-build\bin\Release` 
- Linux: :code:`<build-path>/SuperElastix-build/bin/` 

Demo Experiments
----------------


To reproduce the results of the WBIR conference paper 
*The design of SuperElastix - a unifying framework for a wide range of image registration methodologies, F. Berendsen, K. Marstal, S. Klein and M. Staring*, found at :code:`<source-path>\Documentation\source\paperWBIR16`, 
follow these instructions.
Create a directory and copy the following files to it:

- :code:`<build-path>\SuperElastix-build\bin\Release\SuperElastix.exe`
- :code:`<build-path>\SuperElastix-build\Testing\Unit\Data\Input\coneA2d64.mhd`
- :code:`<build-path>\SuperElastix-build\Testing\Unit\Data\Input\coneA2d64.raw`
- :code:`<build-path>\SuperElastix-build\Testing\Unit\Data\Input\coneB2d64.mhd`
- :code:`<build-path>\SuperElastix-build\Testing\Unit\Data\Input\coneB2d64.raw`
- :code:`<source-path>\Testing\Unit\Data\Configuration\itkv4_SVF_MSD.json`
- :code:`<source-path>\Testing\Unit\Data\Configuration\itkv4_SVF_ANTsCC.json` 
- :code:`<source-path>\Testing\Unit\Data\Configuration\elastix_Bspline_MSD.json`
- :code:`<source-path>\Testing\Unit\Data\Configuration\elastix_Bspline_NC.json`

Run each of the following experiments from a commandline prompt.

Experiment 1A:
::

    SuperElastix.exe --conf elastix_Bspline_NC.json --graphout 1A_graph_elastix_NC.dot --in FixedImage=coneA2d64.mhd MovingImage=coneB2d64.mhd --out ResultImage=1A_image_elastix_NC.mhd

Experiment 1B:

::

    SuperElastix.exe --conf elastix_Bspline_MSD.json --graphout 1B_graph_elastix_MSD.dot --in FixedImage=coneA2d64.mhd MovingImage=coneB2d64.mhd --out ResultImage=1B_image_elastix_MSD.mhd

Experiment 2A:

::

    SuperElastix.exe --conf itkv4_SVF_ANTsCC.json --graphout 2A_graph_itkv4_NC.dot --in FixedImage=coneA2d64.mhd MovingImage=coneB2d64.mhd --out ResultImage=2A_image_itkv4_NC.mhd ResultDisplacementField=2A_deformation_itkv4_NC.mhd

Experiment 2B:

::

    SuperElastix.exe --conf itkv4_SVF_ANTsCC.json --graphout 2B_graph_itkv4_MSD.dot --in FixedImage=coneA2d64.mhd MovingImage=coneB2d64.mhd --out ResultImage=2B_image_itkv4_MSD.mhd ResultDisplacementField=2B_deformation_itkv4_MSD.mhd


Library use
-----------
