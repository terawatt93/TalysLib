#!/bin/bash
wget https://tendl.web.psi.ch/tendl_2019/talys/talys.tar
tar -xzf talys.tar
mv talys.setup talys/
cd talys
./talys.setup
