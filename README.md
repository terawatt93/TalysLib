# TalysLib
This library requires ROOT6 (https://root.cern/) and TALYS 1.8 or 1.9 (https://tendl.web.psi.ch/tendl_2019/talys.html)

Compilation: make

Before installation make sure there are needed variables in the .bashrc file: 

Variable TALYSDIR=PATH_TO_TALYS_DIRECTORY should be defined in .bashrc; 
Path to Talys executable file should be written in PATH variable.
A modified talys.setup macro can be used for TALYS installation to assign these variables automatically.

Installation instruction:

    A. In case of TALYS installation:
    1) Copy the talys.setup and LoadAndInstallTalys.sh files to directory where TALYS will be installed
    2) Launch LoadAndInstallTalys.sh script in the directory
    3) Go to TalysLib directory
    4) Launch MakeLibraries.sh script in the directory
    5) Execute "make install"

    B. In case TALYS is already installed:
    1) Go to TalysLib directory
    2) Launch MakeLibraries.sh script in the directory
    3) Execute "make install"

Command "make install" to be executed in terminal only once!

Example of changes in .bashrc:
export TALYSDIR=/path/to/talys
export TALYSLIBDIR=/path/to/TalysLib
export PATH=$PATH:/path/to/talys
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/TalysLib
export CPATH=$CPATH:/path/to/TalysLib
