.. _GettingStarted:

Getting Started
===============

This page explains how to install SuperElastix.

.. _Linux:

SuperBuild On Linux
-------------------

The SuperElastix SuperBuld is a script that automatically downloads and installs dependencies before compiling the main project. SuperElastix depends on ITK and elastix. The following steps assume that CMake, git and a compiler toolchain is installed. To build SuperElastix, clone the repository and invoke the SuperBuild. 

::

    $ git clone https://github.com/SuperElastix/SuperElastix
    $ mkdir build
    $ cd build
    $ cmake ../SuperElastix/SuperBuild
    $ make -j4

To check that SuperElastix was build successfully, go into the :code:`SuperElastix-build` directory and run the test suite with the following command

::
    
    ctest -j4

.. warning::

    Be careful not to run out of memory during the build. A rule of thumb is that we need 4GB of memory per core. For example, if we compile SuperElastix with 4 cores (e.g. :code:`make -j4`) we need a machine with at least 16GB of RAM.

.. _MacOSX:

SuperBuild On Mac OS X
----------------------

The Mac OS X installation procedure is identical to that of Linux, so simply follow the Linux installation steps above to install SuperElastix. It is assumed that a CMake, git and a compiler toolchain has already been installed. We can check for a working compiler by opening the OS X terminal and run :code:`make`. OS X will know if the Xcode Command Line Tools is missing and prompt you to install them if this is the case. 

.. _Windows:

SuperBuild On Windows
---------------------

In this guide we will use CMake to generate build files and the Visual Studio compiler to compile the project. 

1. Setup directories.
    - Download and install `CMake GUI <http://www.cmake.org/download/>`_.
    - :code:`git clone https://github.com/SuperElastix/SuperElastix` into a source folder of your choice.
    - Point the CMake source directory to the :code:`SuperElastix/SuperBuild` folder inside the source directory.
    - Point the CMake build directory to a clean directory. Note that Visual Studio may complain during the build if the path is longer than 50 characters. Make a build directory with a short name at the root of your harddrive to avoid any issues.


2. Select compiler.
    - Press configure to bring up the compiler selection window.
    - Preferably, choose Visual Studio 12 2013 Win64 as the generator for the project. SuperElastix can only be compiled with Visual Studio 12 or later, and if the OS is 64-bit that is also the prefered for the compiler. 

3. Open Visual Studio, select File -> Open Project/Solution -> Open and choose :code:`SuperElastixSuperBuild` solution.

4. Make sure "Release" build type is selected and build the :code:`ALL_BUILD` project.

5. Right-click on :code:`ALL_BUILD` and click :code:`Build`.
    - When building in Visual Studio 2015 you will get a number of error messages during compilation of ITK. Just press the 'Ignore' button for all of them.

6. The SuperBuildSuperElastix solution only shows each library as a project. To have a more detailed view of SuperElastix open the SuperElastix solution file  :code:`<build-path>\SuperElastix-build\SuperElastix.sln` in a new Visual Studio environment.

7. Optionally, Unit Tests and example code can be run by right-clicking on :code:`RUN_TESTS` and clicking :code:`Project Only -> Build Only RUN_TESTS`. Alternatively, individual tests can be run by right-clicking on a specific selx<...>Test project and choosing :code:`Set as StartUp Project`.

8. The SuperElastix commandline executable can be found in :code:`<build-path>\SuperElastixApplications-build\CommandlineProgram\Release`.



Manually Building the Required Libraries
----------------------------------------
Instead of letting the SuperBuild download and build the required libraries manually build libraries can be used as well.
The following approach allows us to use a system version of ITK or our own version of elastix. 

1. Build ITK. 
    - Clone ITK from `github.com/InsightSoftwareConsortium/ITK <https://github.com/InsightSoftwareConsortium/ITK>`_.
    - Configure CMake. Set the following CMake variables: BUILD_SHARED_LIBS=OFF, ITK_USE_REVIEW=ON, ITK_WRAP_*=OFF.
    - Compile ITK. Make sure to note the build settings, e.g. Release x64.

2. Build Boost
	
3. Build elastix. 
    - Clone elastix from `github.com/kaspermarstal/elastix <https://github.com/kaspermarstal/elastix>`_.
    - Set ITK_DIR to the location of the ITK build directory
    - Configure CMake. Set the following CMake variables: BUILD_EXECUTABLE=OFF, USE_KNNGraphAlphaMutualInformationMetric=OFF 
    - Set appropriate ELASTIX_IMAGE_2/3/4D_PIXELTYPES and any components that you might require.
    - If you are developing your own elastix components, make sure they are properly registered by the elastix build system.
    - Compile elastix. Make sure to configure the build settings exactly the same as ITK e.g. Release x64.

4. Build SuperElastix. 
    - Clone SuperElastix from `github.com/SuperElastix/SuperElastix <https://github.com/SuperElastix/SuperElastix>`_.
    - Configure CMake. Point ITK_DIR to the location of the ITK build directory and ELASTIX_DIR to the location of the elastix build directory.
    - Build SuperElastix. Make sure to configure the build settings exactly the same as ITK e.g. Release x64.
