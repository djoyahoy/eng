#Eng
A small and simple (and messy) 2D game engine that I've abandoned in favor of Unity.

My goal was enjoyable player movement (ie. Megaman X). In that respect, the player can:
* Jump
* Roll
* Attack
* Wall Jump
* Climb

The machinery for enemies and props is built into the game engine, but there are no pre-fabs implemented.

Stage and pre-fab generation is somewhat convoluted, but it occurs in scripts, with enemy and prop artifacts generated to gen.

##Dependencies
* Cmake 3.0 - http://www.cmake.org/
* SDL 2.0 - https://www.libsdl.org/
* jsoncpp - https://github.com/open-source-parsers/jsoncpp
* python 3.4.2 - https://www.python.org/
* virtualenv - https://virtualenv.pypa.io/en/latest/

##Build
1. Modify the CMakesList.txt to use FindSDL or point to your local SDL includes/libs.
2. Use virtualenv to setup an environment `.env` in scripts. Use pip to install the requirements.txt.
3. `mkdir build`
4. `cd build`
5. `cmake ..`
6. `make`

##Note
* The game requires a game pad.
