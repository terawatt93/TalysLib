#!/bin/bash
#######################################################
# This script takes care of the TalysLib installation.
#######################################################
#
# 1. Install libzip package from apt package manager
sudo apt install -y libzip-dev
talyslibdir=`pwd` # Define the TalysLib directory
#
# 2. Check whether TALYS directory is set in .bashrc, go there
if [ -z ${TALYSDIR+x} ];
then
  echo 'TALYSDIR vairable is NOT defined in .bashrc! Define it!'
  exit
else
  echo 'TALYSDIR vairable is defined in .bashrc! Proceeding.'
  cd ${TALYSDIR} # Go to TALYS directory
fi
#
# 3. Check whether TALYS has been installed
if [ -e talys ] 
then
  echo 'TALYS instalation is confirmed! Proceeding.'
  mkdir CalculationResults # Create directory for TalysLib calculation results
else
  echo 'TALYS instalation is NOT confirmed! Use Instal.sh or check TALYSDIR vairable!'
  exit
fi
#
# 4. Return to your TalysLib directory
cd ${talyslibdir}
#
# 5. Downloading and installing libxlsxwriter library
./MakeLibraries.sh
make install

