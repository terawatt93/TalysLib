#!/bin/bash
make clean
rm *.so *.cxx *.rootmap *.pcm *.d
make clean
make -C  libxlsxwriter clean
make 
make -C  libxlsxwriter
