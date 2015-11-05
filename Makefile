CC=emcc
CFLAGS=-I. -Iassimp/include -Iassimp/code --bind -std=c++11 -s EXPORT_NAME="'ASSIMP'" -s WARN_ON_UNDEFINED_SYMBOLS=1 -s VERBOSE=1 -Dprivate=public -Dprotected=public
# 

OBJ = assimp.js
SRC = AnimEmbind.cpp CameraEmbind.cpp Color4Embind.cpp ExporterEmbind.cpp LightEmbind.cpp ImporterEmbind.cpp \
      MaterialEmbind.cpp Matrix3x3Embind.cpp Matrix4x4Embind.cpp MeshEmbind.cpp QuaternionEmbind.cpp \
      SceneEmbind.cpp TextureEmbind.cpp TypesEmbind.cpp Vector2Embind.cpp Vector3Embind.cpp

#SRC = AnimEmbind.cpp CameraEmbind.cpp TypesEmbind.cpp


assimpjsmake: $(SRC)
	$(CC) $(CFLAGS) -o $(OBJ) $(SRC)

.PHONY: clean

clean:
	rm -f $(OBJ)

#emcc --bind  -std=c++11 -o assimp.js -Iassimp/include/ -s WARN_ON_UNDEFINED_SYMBOLS=1 -s VERBOSE=1 -Dprivate=public assimpEmbind.cpp	