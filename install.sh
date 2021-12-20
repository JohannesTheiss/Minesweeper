#!/bin/bash

APPLICATION_NAME=Minesweeper

[[ $EUID -ne 0 ]] && echo "This script must be run as root." && exit 1

# default install directory
prefix=/opt

folderName=$APPLICATION_NAME
installationPath=${prefix}/${folderName}

echo
echo -e "\e[1;32m${APPLICATION_NAME} Installer\e[0m"
echo

# build
numberOfCores=$(grep -c '^processor' /proc/cpuinfo || 1)

echo "build..."
qmake build.pro
make -j ${numberOfCores}
if [ $? -eq 0 ]; then
    echo
    echo -e "\e[1;32mbuild successfully\e[0m" 
else
    echo
    echo -e "\e[1;31mbuild failed\e[0m" 
    exit 1
fi

# create installation path
sudo mkdir -p ${installationPath}

#git clone --depth 1 https://github.com/JohannesTheiss/${APPLICATION_NAME}.git
# copy the software
echo -e "\e[1;32mcopy software to ${installationPath}\e[0m" 
sudo cp -r . ${installationPath}

dotDesktopFolder=/usr/share/applications
echo -e "\e[1;32mcopy .desktop file to ${dotDesktopFolder}\e[0m" 
sudo cp minesweeper.desktop ${dotDesktopFolder}

echo
echo -e "\e[1;32mInstallation complete.\e[0m" 
echo
