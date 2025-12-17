# **TalysLib**

(Instruction in Russian is below English version)

## Requirements: 
1. Debian-based Linux distribution (we recommend [Linux Mint](https://linuxmint.com/))
2. [TALYS](https://tendl.web.psi.ch/tendl_2019/talys.html) 1.8 or 1.9 
If TALYS is already installed on your system in the "/path/to_talys" directory:
  1. Make sure that the path to the TALYS executable (paste your path in the lines below) is added to PATH. Otherwise:
   * Add the following line to your .bashrc file: export PATH=$PATH:/path/to_talys/talys
  2. In case it is not already defined, define a new environment variable TALYSDIR in the .bashrc file:
   * Add the following line to your .bashrc file: export TALYSDIR =/path/to_talys/talys
3. [ROOT6](https://root.cern)
4. Installed packages: libzip-dev, libsqlite3-dev
If you are using the TalysLib auto-installation script, TalysLib/Install.sh, you will install the listed packages through the apt package manager.

## Installation instruction:

    1) Go to TalysLib directory
    2) Launch Install.sh script
    3) Select the desired installation method: with or without TALYS

New lines in ~/.bashrc file added for TalysLib should look like this:
    
> export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/user_name/some_directory/TalysLib <br>
> export CPATH=$CPATH:/home/user_name/some_directory/TalysLib <br>
> export TALYSLIBDIR=/home/user_name/some_directory/TalysLib <br>

If you want to use testing feature working with EXFOR and ENDF, download http://159.93.100.133:85/C4/C4Base.db and http://159.93.100.133:85/C4/Base.root put them into same directory and add path to them in .bashrc:
export C4Base=/Path/to/C4Base.db
## IMPORTANT!
Since 17.12.2025 TalysLib has migrated from libxlsxwriter to OpenXLSX (with ROOTOpenXLSX wrapper)! Install.sh was updated. libxlsxwriter is not avalible anymore in TalysLib
## Требования: 
1. Дистрибутив Linux на основе Debian (мы рекомендуем [Linux Mint](https://linuxmint.com/))
2. [TALYS](https://tendl.web.psi.ch/tendl_2019/talys.html) 1.8 or 1.9 
Если TALYS уже установлен в вашей системе в директории "/path/to_talys":
  1. Убедитесь, что путь к исполняемому файлу TALYS (вставьте в строки ниже свой путь) добавлен в PATH. В ином случае:
   * Добавьте следующую строку в свой .bashrc файл: export PATH=$PATH:/path/to_talys/talys
  2. В случае, если она ещё не определена, определите новую переменную окружения TALYSDIR в .bashrc файле:
   * Добавьте следующую строку в свой .bashrc файл: export TALYSDIR =/path/to_talys/talys 
3. [ROOT6](https://root.cern)
4. Установленные пакеты: libzip-dev, libsqlite3-dev
Если вы используете скрипт по автоматической установке TalysLib, TalysLib/Install.sh, вы установите перечисленные пакеты через манеджер пакетов apt.

## Инструкция по установке:

    1) Перейдите в директорию TalysLib
    2) Запустите скрипт Install.sh
    3) Выберите требуемый способ установки: с TALYS или без

Новые записи в ~/.bashrc для TalysLib должны выглядеть примерно так:
    
> export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/user_name/some_directory/TalysLib <br>
> export CPATH=$CPATH:/home/user_name/some_directory/TalysLib <br>
> export TALYSLIBDIR=/home/user_name/some_directory/TalysLib <br>
## Важно!
С 17.12.2025 библиотека TalysLib перешла с libxlsxwriter на OpenXLSX (с использованием оболочки ROOTOpenXLSX)! Файл Install.sh был обновлен. libxlsxwriter больше недоступен.
