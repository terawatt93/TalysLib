#!/bin/bash
#######################################################
# This script takes care of the TalysLib installation.
#######################################################
#
# 1. Install libzip and gfortran package from apt package manager
sudo apt install -y libzip-dev
sudo apt install -y gfortran
talyslibdir=`pwd` # Define the TalysLib directory
cd ..
#
# 2. Download and unpack archive with TALYS
wget https://tendl.web.psi.ch/tendl_2019/talys/talys.tar 
echo 'The TALYS archive has been downloaded.'
tar -xzf talys.tar
echo 'The TALYS archive has been uncompressed.'
cd talys
unalias -a # Note: The unalias utility shall remove the definition 
#           for each alias name specified
#
# 3. Define Fortran compiler for TALYS
compiler='gfortran'       
#compiler='lf95 --staticlink' 
Thome=${HOME}
cd ..
talysdir=`pwd` # Define the TALYS directory
#
# 4. Ensure that all directories have execute permission and that 
#    all files have a read and write permission   
chmod -R u+rwX talys
#
# 5. Ensure that TALYS can read the structure database by replacing
#    the path name in subroutine machine.f
datapath=${talysdir}'/'
datapathnew=`echo $datapath | sed 's/\//\\\\\//g'`
cd ${talysdir}'/talys/source/'
sed "s/ home='.*'/ home='${datapathnew}'/" machine.f  > machine_tmp.f
mv -f machine_tmp.f machine.f
# 
# 6. Compile TALYS
#    Please note that the compilation of ecis06t.f
#    may result in some trivial warning messages
${compiler} -c *.f
${compiler} *.o -o talys
#
# 7. Check whether TALYS setup procedure has been successful
if [ -e talys ] 
then
  mv -f talys ../talys
  cd ../
  echo ' '
  echo 'The TALYS setup has been completed.'
  echo ' '
  echo 'You will find a talys executable in your' `pwd` 'directory.'
  echo ' '
  echo 'You are all set to run the sample problems in the samples directory'
  echo 'with the verify script.'
  echo 'export TALYSDIR='`pwd`>>~/.bashrc 
  echo 'export PATH=$PATH:'`pwd`>>~/.bashrc
  mkdir CalculationResults # Create directory for TalysLib calculation results
  cd ..
  rm talys.tar # Delete used TALYS archive
else
  echo 'TALYS setup failed'
fi
#
# 8. Return to your TalysLib directory
cd ${talyslibdir}
#
# 9. Downloading and installing libxlsxwriter library
./MakeLibraries.sh
make install

