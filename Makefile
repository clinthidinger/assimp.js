CC=emcc
IFLAGS=-I. -Iassimp/include -Iassimp/code -Iassimp/code/BoostWorkaround -Iassimp/contrib \
           -Iassimp/contrib/openddlparser/include -Iassimp/build
CFLAGS=--bind -O2 -std=c++11 -s EXPORT_NAME="'ASSIMP'" -s WARN_ON_UNDEFINED_SYMBOLS=1 -s VERBOSE=1 \
       -Dprivate=public -Dprotected=public #--closure 1
# MODULARIZE
# COPY zconf.h
OBJ = assimp.js
#EMBINDSRC = AnimEmbind.cpp CameraEmbind.cpp Color4Embind.cpp ExporterEmbind.cpp LightEmbind.cpp ImporterEmbind.cpp \
#      		MaterialEmbind.cpp Matrix3x3Embind.cpp Matrix4x4Embind.cpp MeshEmbind.cpp PostProcessEmbind.cpp \
#      		QuaternionEmbind.cpp SceneEmbind.cpp TextureEmbind.cpp TypesEmbind.cpp Vector2Embind.cpp \
#            Vector3Embind.cpp 
EMBINDSRC = src/*.cpp

 #ASSIMPSRC = $(filter-out src/bar.cpp, $(wildcard assimp/code/*.cpp))
 #ASSIMPSRC = assimp/code/*.cpp
 #Exclude c4d.
 #EXCLUDE=$(subst assimp/code/C4DImporter.cpp,,${ASSIMPSRC})
 # Exclude c4d since it is for msvc only.
ASSIMPSRC := $(shell find assimp/code ! -name "C4DImporter.cpp" -name "*.cpp")
SRC = $(ASSIMPSRC) $(EMBINDSRC)
# TODO SRC = src/*.cpp assimp/code/*.cpp

#SRC = AnimEmbind.cpp CameraEmbind.cpp TypesEmbind.cpp
#assimpjsmake_min: use closure compiler

assimpjsmake: $(SRC)
	$(CC) $(IFLAGS) $(CFLAGS) -o $(OBJ) $(SRC)

.PHONY: clean

clean:
	rm -f $(OBJ)

#emcc --bind  -std=c++11 -o assimp.js -Iassimp/include/ -s WARN_ON_UNDEFINED_SYMBOLS=1 -s VERBOSE=1 -Dprivate=public assimpEmbind.cpp	
#incstructions
#0) install emscripten and make sure emcc is in path
#!1) git clone
#2) git submodule update --init --recursive
#3) mkdir assimp/build
#4) cd assimp/build
#5) cmake ..
#
