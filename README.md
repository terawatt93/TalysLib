# TalysLib

This library requires ROOT6 (https://root.cern/) and TALYS 1.8 or 1.9 (https://tendl.web.psi.ch/tendl_2019/talys.html)

## Installation instruction:

 1. Run Install.sh

Command "make install" to be executed in terminal only once!

 New liones in ~/.bashrc should look like that:

    export TALYSDIR=/path/to/talys
    export TALYSLIBDIR=/path/to/TalysLib
    export PATH=$PATH:/path/to/talys
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/TalysLib
    export CPATH=$CPATH:/path/to/TalysLib

Для этой библиотеки требуется ROOT6 (https://root.cern/) и TALYS 1.8 или 1.9 (https://tendl.web.psi.ch/tendl_2019/talys.html)

## Инструкция по установке:

  1. Выполнить в терминале Install.sh 

 Команда "make install" выполняется однократно, при перекомпиляции и/или обновлении ее не нужно выполнять

 Новые записи в ~/.bashrc должны выглядеть так:
    
    export TALYSDIR=/path/to/talys
    export TALYSLIBDIR=/path/to/TalysLib
    export PATH=$PATH:/path/to/talys
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/TalysLib
    export CPATH=$CPATH:/path/to/TalysLib
