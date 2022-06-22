#!/bin/bash
if [ ! -e libxlsxwriter/include/xlsxwriter.h ]
then
rm -rf libxlsxwriter
wget https://github.com/jmcnamara/libxlsxwriter/archive/refs/heads/main.zip
unzip main.zip
rm main.zip
mv libxlsxwriter-main/ libxlsxwriter
fi

if [ ! -e ResponseDataBase/ResponseDB.root ]
then
	mkdir ResponseDataBase
	cd ResponseDataBase
	wget http://159.93.100.133:85/TalysLibData/ResponseDB.root
	cd ../
fi

make clean
rm *.so *.cxx *.rootmap *.pcm *.d
make clean
make -C  libxlsxwriter clean
make 
make -C  libxlsxwriter
