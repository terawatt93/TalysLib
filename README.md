# TalysLib
This library requires ROOT6 (https://root.cern/, compiled with mathmore flag) and TALYS 1.8 or 1.9 (https://tendl.web.psi.ch/tendl_2019/talys.html)

Installation instruction:

    A. In case of TALYS installation:
    1) Copy the talys.setup and LoadAndInstallTalys.sh files to directory where TALYS will be installed
    2) Launch LoadAndInstallTalys.sh script in the directory
    3) Go to TalysLib directory
    4) Launch MakeLibraries.sh script in the directory
    5) Execute "make install"

    B. In case TALYS is already installed:
    1) Be sure that path to the Talys executable file is added to PATH
    2) Define a new variable TALYSDIR=/path/to/talys in ~/.bashrc 
    3) Go to TalysLib directory
    4) Launch MakeLibraries.sh script in the directory
    5) Execute "make install"

Command "make install" to be executed in terminal only once!

    export TALYSDIR=/path/to/talys
    export TALYSLIBDIR=/path/to/TalysLib
    export PATH=$PATH:/path/to/talys
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/TalysLib
    export CPATH=$CPATH:/path/to/TalysLib

Для этой библиотеки требуется ROOT6 (https://root.cern/, скомпилированный с флагом mathmore) и TALYS 1.8 или 1.9 (https://tendl.web.psi.ch/tendl_2019/talys.html)

Инструкция по установке:

    A. В случае установки TALYS:
    1) Скопируйте файлы talys.setup и LoadAndInstallTalys.sh в каталог, в который будет установлен TALYS.
    2) Запустить скрипт LoadAndInstallTalys.sh в каталоге
    3) Перейти в каталог TalysLib
    4) Запустите скрипт MakeLibraries.sh в каталоге
    5) Выполните «make install».

    Б. Если TALYS уже установлен:
    1) Убедитесь, что путь к исполняемому файлу Talys добавлен в PATH
    2) Определите новую переменную TALYSDIR=/path/to/talys в ~/.bashrc
    3) Перейти в каталог TalysLib
    4) Запустите скрипт MakeLibraries.sh в каталоге
    5) Выполните «make install». 
 Команда "make install" выполняется однократно, при перекомпиляции и/или обновлении ее не нужно выполнять
 Новые записи в ~/.bashrc должны выглядеть так:
    
    export TALYSDIR=/path/to/talys
    export TALYSLIBDIR=/path/to/TalysLib
    export PATH=$PATH:/path/to/talys
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/TalysLib
    export CPATH=$CPATH:/path/to/TalysLib
