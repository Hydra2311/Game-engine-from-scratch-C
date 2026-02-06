#!/bin/bash

#Bash script to automate compiling and running the unit tests, the engine and the games

ctest="gcc -c engine.c -o engine.o && ar rcs libengine.a engine.o && gcc -I./libs/Unity/src Testengine.c engine.c libs/Unity/src/unity.c -L. -lengine && ./a.out"
crpg="gcc -c engine.c -o engine.o && ar rcs libengine.a engine.o && gcc rpg.c -L. -lengine && ./a.out"
cluck="gcc -c engine.c -o engine.o && ar rcs libengine.a engine.o && gcc luck.c -L. -lengine && ./a.out"

echo "Testing..."
eval "$ctest"

#Automatically exits if the tests aren't successful
if [ $? -ne 0 ]; then
    echo "Tests failed. Exiting with error."
    exit 1
fi

echo "1.Rpg 2.Luck 3.Exit"
read answer

if [[ "$answer" == 1 ]]; then
    echo "Executing rpg.c"
    eval "$crpg"
elif [[ "$answer" == 2 ]]; then
    echo "Executing luck.c"
    eval "$cluck"
else
    echo "Exiting..."
    exit 0
fi
