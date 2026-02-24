# Game Engine from scratch

**A custom, lightweight game engine built entirely in C.**

---

## About this Program

After completing my first semester C programming course, I wanted to use my knowledge to create something practical and fun. 
Through creating this project, I was able to learn more about the language and improve my C programming skills significantly.
Moreover, I have added multiple comments inside the code base to help showcase my way of thinking and make the code easier to understand.

## Features
* Library with helpful functions
* Unit Testing (Unity Framework)
* Input handling
* Automated execution

## How to run

The "execute.sh" file is a quality of life improvement i decided to make to automate the execution of the program as I wasn't aware of the CMake framework
when I first created the project. Editting and formatting the commands to your liking is incredibly easy.

```bash
ctest="gcc -c engine.c -o engine.o && ar rcs libengine.a engine.o && gcc -I./libs/Unity/src Testengine.c engine.c libs/Unity/src/unity.c -L. -lengine && ./a.out"
crpg="gcc -c engine.c -o engine.o && ar rcs libengine.a engine.o && gcc rpg.c -L. -lengine && ./a.out"
cluck="gcc -c engine.c -o engine.o && ar rcs libengine.a engine.o && gcc luck.c -L. -lengine && ./a.out"
