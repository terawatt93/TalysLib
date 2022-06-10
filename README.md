# TalysLib

This library requires ROOT6 (https://root.cern/, compiled with mathmore flag) and TALYS 1.8 or 1.9 (https://tendl.web.psi.ch/tendl_2019/talys.html)

Installation instruction:

    A. In case of join TALYS installation:
    1) Go to TalysLib directory
    2) Launch Install.sh script

    B. In case TALYS has already been installed in your system in directory "/path/to_talys":
    1) Make sure that path to the TALYS executable file (insert your path in lines below) is added to PATH. Otherwise:
        1.1) Add next line in .bashrc file: export PATH=$PATH:/path/to_talys/talys
    2) In case it hasn't been defined, define a new variable TALYSDIR in .bashrc file:
        2.1) Add next line in .bashrc file: export TALYSDIR =/path/to_talys/talys 
    3) Go to TalysLib directory
    '4) Launch Install_Without_TALYS.sh script'

New lines in ~/.bashrc file added for TalysLib should look like this:
    
    'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/user_name/some_directory/TalysLib'
    'export CPATH=$CPATH:/home/user_name/some_directory/TalysLib'
    'export TALYSLIBDIR=/home/user_name/some_directory/TalysLib'

Для этой библиотеки требуется ROOT6 (https://root.cern/, скомпилированный с флагом mathmore) и TALYS 1.8 или 1.9 (https://tendl.web.psi.ch/tendl_2019/talys.html)

Инструкция по установке:

    A. В случае установки вместе с TALYS:
    1) Перейдите в директорию TalysLib
    2) Запустите скипт Install.sh

    Б. Если TALYS уже установлен в вашей системе в директории "/path/to_talys":
    1) Убедитесь, что путь к исполняемому файлу TALYS (вставьте в строки ниже свой путь) добавлен в PATH. В ином случае:
        1.1) Добавьте следующую строку в свой .bashrc файл: export PATH=$PATH:/path/to_talys/talys
    2) В случае, если она ещё не определена, определите новую переменную окружения TALYSDIR в .bashrc файле:
        2.1) Добавьте следующую строку в свой .bashrc файл: export TALYSDIR =/path/to_talys/talys 
    3) Перейдите в директорию TalysLib
    '4) Запустите скрипт Install_Without_TALYS.sh'

Новые записи в ~/.bashrc для TalysLib должны выглядеть примерно так:
    
    'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/user_name/some_directory/TalysLib'
    'export CPATH=$CPATH:/home/user_name/some_directory/TalysLib'
    'export TALYSLIBDIR=/home/user_name/some_directory/TalysLib'

