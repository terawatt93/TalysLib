#!/bin/bash
talyslibdir=`pwd`
cd ..
wget https://tendl.web.psi.ch/tendl_2019/talys/talys.tar
tar -xzf talys.tar
cd talys
unalias -a
#
# This script takes care of the TALYS installation.
# All you have to do is adapt the next variables to your own situation,
# and run.....
#
compiler='gfortran'       
#compiler='lf95 --staticlink' 
Thome=${HOME}
#
# From here on, the rest should work automatically
#
# 1. Define the talys directory
#
cd ..
talysdir=`pwd`
#
# 2. Ensure that all directories have execute permission and that 
#    all files have a read and write permission   
#
chmod -R u+rwX talys
#
# 3. Ensure that TALYS can read the structure database by replacing
#    the path name in subroutine machine.f
#
datapath=${talysdir}'/'
datapathnew=`echo $datapath | sed 's/\//\\\\\//g'`
cd ${talysdir}'/talys/source/'
sed "s/ home='.*'/ home='${datapathnew}'/" machine.f  > machine_tmp.f
mv -f machine_tmp.f machine.f
# 
# 4. Compile TALYS.
#    Please note that the compilation of ecis06t.f
#    may result in some trivial warning messages
#
${compiler} -c *.f
${compiler} *.o -o talys
#
# 5. Check whether the setup procedure has been successful
#
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
  echo  'export TALYSDIR='`pwd`>>~/.bashrc 
  echo 'export PATH=$PATH:'`pwd`>>~/.bashrc
  mkdir CalculationResults
  cd ..
  rm talys.tar
else
  echo 'TALYS setup failed'
fi

cd ${talyslibdir}
./MakeLibraries.sh
make install

