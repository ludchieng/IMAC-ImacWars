#!/bin/bash
cmake CMakeLists.txt
make
if [ $# -ne 1 ]; then
	read -p "Run imacwars or tests? [i/t]: " inpt 
else
	inpt=$1
fi
case $inpt in
	t ) ./bin/tests;;
	i ) ./bin/imacwars;;
esac
