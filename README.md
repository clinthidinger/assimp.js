Work in Porgress

Port of Open Asset Import Library (ASSIMP) to javascript with emscripten.
See https://github.com/assimp/assimp and http://assimp.sourceforge.net.

Build:

Go to https://kripken.github.io/emscripten-site/docs/getting_started/downloads.html to get emscripten.

./emsdk update
./emsdk install --build=Release latest
./emsdk activate --build=Release latest

Posssibly do:
source ${YOUR_EMSCRIPTEN_DIR}/emsdk_env.sh

git submodule update --init --recursive

make


Run from repo directory:

python -m SimpleHTTPServer 8000

Then open http://localhost:8000/examples/example.html


Rebuilding:

make clean
make

Building a debug build:

make debug

TODO:

Using "-s SAFE_HEAP=1" will cause a crash on export due to mem alignment issues.  They will likely happen in the material export.  Look into "-s WASM=1".

For unbound types:
Pay attention to ordering of sources in makefile.  Also, make sure to include the appropriate headers in embind files.

Getter setter for indexed array.
Finish mesh embind.
User array getter setters where needed.
Make aiString to std::string.

Threejs data.

Module name not working.

MAR 12: wrap meshes and things with std::vec from scene