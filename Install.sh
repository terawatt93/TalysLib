#!/bin/bash
#######################################################
# This script takes care of the TalysLib installation.
#######################################################
#
# 1. Give user freedom of chosing type of the installation. 
echo "################################################################"
echo "# Welcome to the TalysLib installation script!                 #"
echo "# Please choose your preferred TalysLib installation method:   #"
echo "# 1. With TALYS code installation.                             #"
echo "# 2. WithOUT TALYS code installation.                          #"
echo "# (In case you have already installed it)                      #"
echo "################################################################"
read choice

talyslibdir=`pwd` # Define the TalysLib directory

case $choice in
    "1")
        echo "#### Going with TALYS code installation!"
        #
        # 2. Install libzip, libsqlite and gfortran packages from apt package manager 
        # (that will do nothing if they have already been installed, no problem)
        echo 'Installing libzip-dev from apt utility.'
        sudo apt install -y libzip-dev
        echo 'Installing gfortran from apt utility.'
        sudo apt install -y gfortran
        echo 'Installing libsqlite-dev from apt utility.'
        sudo apt install -y libsqlite-dev
        echo 'Installing libsqlite-dev3 from apt utility.'
        sudo apt install -y libsqlite3-dev
        cd ..
        #
        # 1-3. Clonning of the TALYS repository
        echo 'Clonning the TALYS repository from github.'
        git clone https://github.com/arjankoning1/talys
        cd talys
        echo 'Downloading TALYS database and examples.'
        wget  -U 'Mozilla/5.0 (X11; Linux x86_64; rv:30.0) Gecko/20100101 Firefox/30.0' https://nds.iaea.org/talys/misc/structure.tar
        wget  -U 'Mozilla/5.0 (X11; Linux x86_64; rv:30.0) Gecko/20100101 Firefox/30.0' https://nds.iaea.org/talys/samples/talys_samples.tar
        echo 'Decompressing of the TALYS database.'
        tar zxf structure.tar
        tar zxf talys_samples.tar
        echo 'Removing archives.'
        rm structure.tar
        rm talys_samples.tar
  
        code=talys
        #
        # Script for fortran code installation on Linux and MacOS.
        # Adapt the following compilation variables.
        #
        FC='gfortran'
        FFLAGS='-w'
        #
        # Basic installation (verified with the sample cases)
        #
        # FC="gfortran " FFLAGS=" "
        #
        # Distribution FC & FFLAGS (options provided by J-C Sublet)
        #
        # FC="gfortran " FFLAGS=" -Ofast "
        # FC="ifort    " FFLAGS=" -Ofast "
        # FC="nagfor   " FFLAGS=" -w     "
        #
        # Development FC & FFLAGS  (options provided by J-C Sublet)
        #
        # FC="gfortran " FFLAGS=" -Wall -fcheck=all -Og -g -fbacktrace   "
        # FC="ifort    " FFLAGS=" -O0 -g -traceback -check all -debug all"
        # FC="nagfor   " FFLAGS=" -C=all -O0 -g -gline                   "
        #
        #
        # Set directories
        #
        cwd=`pwd`'/'
        sourcedir=${cwd}'source/'
        bindir=${cwd}'bin'
        cd $sourcedir
        if [ $code != endftables ] && [ $code != sacs ] ; then
          ../path_change
        fi
        #
        # Clean up previous .o and .mod files and compile code.
        #
        echo "Compiling ${code}...."
        ls *.o > /dev/null 2>&1
        if [ $? -eq 0 ] ;then
          rm *.o
        fi
        ls *.mod > /dev/null 2>&1
        if [ $? -eq 0 ] ;then
          rm *.mod
        fi
        ls *.f > /dev/null 2>&1
        if [ $? -eq 0 ] ;then
          ${FC} ${FFLAGS} -c *.f
        fi
        ls *.f90 > /dev/null 2>&1
        if [ $? -eq 0 ] ;then
          ${FC} ${FFLAGS} -c *.f90
        fi
        ${FC} ${FFLAGS} *.o -o ${code}
        rm -f *.o *.mod
        #
        # Check whether the build procedure has been successful
        #
        if [ -e $code ] ; then
          mv -f $code ../
          echo ' '
          echo 'The '${code}' build has been completed.'
          echo 'Adding paths to .bashrc'
          echo 'export TALYSDIR='`pwd`>>~/.bashrc 
          echo 'export PATH=$PATH:'`pwd`>>~/.bashrc
          echo 'export TALYSVERSION=2' >>~/.bashrc
          echo ' '
        else
          echo ${code} 'build failed'
        fi
    ;;
    "2")
        echo "#### Going withOUT TALYS code installation!"
        #
        # 2. Install libzip, libsqlite and gfortran packages from apt package manager 
        # (that will do nothing if they have already been installed, no problem)
        echo 'Installing libzip-dev from apt utility.'
        sudo apt install -y libzip-dev
        echo 'Installing gfortran from apt utility.'
        sudo apt install -y gfortran
        echo 'Installing libsqlite-dev from apt utility.'
        sudo apt install -y libsqlite-dev
        echo 'Installing libsqlite-dev3 from apt utility.'
        sudo apt install -y libsqlite3-dev
        #
        # 2-3. Check whether TALYS directory is set in .bashrc, go there
        if [ -z ${TALYSDIR+x} ];
        then
          echo 'Error: TALYSDIR vairable is NOT defined in .bashrc! Define it!'
          echo 'Aborting installation.'
          exit
        else
          echo 'TALYSDIR vairable is defined in .bashrc! Proceeding.'
          cd ${TALYSDIR} # Go to TALYS directory
        fi
        #
        # 2-4. Check whether TALYS has been installed
        if [ -e talys ] 
        then
          echo 'TALYS instalation is confirmed! Proceeding.'
          mkdir CalculationResults # Create directory for TalysLib calculation results
        else
          echo 'Error: TALYS instalation is NOT confirmed! Check your TALYSDIR vairable!'
          echo 'Aborting installation.'
          exit
        fi
    ;;
    "Quit"|"q"|"Q")
            echo "Quitting installation..."
        exit
    ;;
    *)
        echo "Invalid choice. Please enter either 1 or 2, or 'q' to quit."
    ;;
esac
#
# 4. Return to your TalysLib directory
cd ${talyslibdir}
#
# 5. Downloading and installing side libraries
./MakeLibraries.sh
make install


