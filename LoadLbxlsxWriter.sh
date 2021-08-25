#!/bin/bash
sudo apt-get install -y zlib1g-dev
git clone https://github.com/jmcnamara/libxlsxwriter.git
#if it is needed to get libxlsxwriter by other method, try use these commands, instead of least two:
#wget http://github.com/jmcnamara/libxlsxwriter/archive/master.tar.gz
#tar -xzf master.tar.gz
cd master.tar.gz
make
sudo make install
echo ' '
echo 'The LbxlsxWriter setup has been completed.'
echo ' '
