# TalysLib
This library requires ROOT6 (https://root.cern/) and TALYS 1.8 or 1.9 (https://tendl.web.psi.ch/tendl_2019/talys.html)
Compilation: make
Variable TALYSDIR=PATH_TO_TALYS_DIRECTORY should be defined in .bashrc; Path to Talys executable file should be written in PATH variable.
A modified talys.setup macro could be used for Talys installation to assign these variables automatically.

Installation instruction:
1) Copy the talys.setup and LoadAndInstallTalys.sh to folder where TALYS will be installed
2) Launch LoadAndInstallTalys.sh
3) Execute MakeLibraries.sh
4) Execute "make install"

Make install is needed only one time!

Example of changes in .bashrc
export TALYSDIR=/path/to/talys
export TALYSLIBDIR=/path/to/TalysLib
export PATH=$PATH:/path/to/talys
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/TalysLib
export CPATH=$CPATH:/path/to/TalysLib
