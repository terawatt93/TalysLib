#!/bin/bash
if [ ! -e libxlsxwriter/include/xlsxwriter.h ]
then
rm -rf libxlsxwriter
wget https://github.com/jmcnamara/libxlsxwriter/archive/refs/heads/main.zip
unzip main.zip
rm main.zip
mv libxlsxwriter-main/ libxlsxwriter
fi
make clean
rm *.so *.cxx *.rootmap *.pcm *.d
make clean
make -C  libxlsxwriter clean
make 
make -C  libxlsxwriter
