#!/bin/bash

LIB_DIRECTORY="./lib" 

if ! [ -d "$LIB_DIRECTORY" ]; then
    mkdir -p "$LIB_DIRECTORY";
fi

# load glew library

GLEW_PATH="./lib/glew-2.1.0"

if ! [ -d "$GLEW_PATH" ]; then
    echo Installing GLEW;
    git clone https://github.com/nigels-com/glew.git "$GLEW_PATH"
    make -C "$GLEW_PATH" extensions
    make -C "$GLEW_PATH" -j4;
fi

# load glfw library

GLFW_PATH="./lib/glfw-3.2.1"

if ! [ -d "$GLFW_PATH" ]; then
    echo Installing GLFW;
    git clone https://github.com/glfw/glfw.git "$GLFW_PATH";
    cmake "$GLFW_PATH/CMakeLists.txt" -G 'Unix Makefiles';
    make -C "$GLFW_PATH" -j4;
fi

# load glm

GLM_PATH="./lib/glm"

if ! [ -d "$GLM_PATH" ]; then
    echo Installing GLM;
    git clone https://github.com/g-truc/glm.git "$GLM_PATH";
    cmake "$GLM_PATH/CMakeLists.txt" -G 'Unix Makefiles';
    make -C "$GLM_PATH" -j4;
fi

# load assimp library

ASSIMP_PATH="./lib/assimp-4.1.0"

if ! [ -d "$ASSIMP_PATH" ]; then
    echo Installing assimp library;
    git clone https://github.com/assimp/assimp.git "$ASSIMP_PATH"
    cmake "$ASSIMP_PATH/CMakeLists.txt" -G 'Unix Makefiles'
    make -C "$ASSIMP_PATH" -j4;
fi

# load stb_image library

STB_IMAGE_PATH="./lib/stb_image"

if ! [ -d "$STB_IMAGE_PATH" ]; then
    echo Installing std_image library;
    git clone https://github.com/kzahreba/stb_image.git "$STB_IMAGE_PATH"
fi

# load OpenAL library
OPENAL_PATH="./lib/open_al"
if ! [ -d "$OPENAL_PATH" ]; then
	echo Installing openal library;
	git clone https://github.com/kcat/openal-soft "$OPENAL_PATH"
	cmake "$OPENAL_PATH/CMakeLists.txt"
	export LD_LIBRARY_PATH=lib/open_al
	make -C "$OPENAL_PATH" -j4;
fi

# load alut library
ALUT_PATH="./lib/alut"
if ! [ -d "$ALUT_PATH" ]; then
	echo Installing glut library;
	git clone https://github.com/vancegroup/freealut.git "$ALUT_PATH"
	cmake "$ALUT_PATH/CMakeLists.txt"
	make -C "$ALUT_PATH" -j4;
fi

FREETYPE_PATH="./lib/freetype"
if ! [ -d "$FREETYPE_PATH" ]; then
	echo Installing freetype library;
	git clone https://github.com/aseprite/freetype2.git "$FREETYPE_PATH"
	cd $FREETYPE_PATH
	cp src/base/ftmac.c builds/mac/ftmac.c
	export MACOSX_DEPLOYMENT_TARGET=10.2
	cmake -E remove CMakeCache.txt
	cmake -E remove_directory CMakeFiles
	cmake -E make_directory build
	cmake -E chdir build cmake ..
	make -C build/
fi

SOIL_PATH="./lib/SOIL"
if ! [ -d "$SOIL_PATH" ]; then
	echo Installing SOIL library;
	git clone https://github.com/DeVaukz/SOIL.git "$SOIL_PATH"
	cmake "$SOIL_PATH/CMakeLists.txt"
	make -C "$SOIL_PATH" -j4;
fi

