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

Update to latest assimp.  Will have to put printf("...\n") statements in Importer::ReadFile() to figure out problem.  Most likely need to add a cpp file.

ASSERTIONS=2 causes "RangeError: Maximum call stack size exceeded"
This is supposed to fix it, but doesn't seem to work:
On Linux and Mac OS X, you can just do NODE_JS = ['node', '--stack_size=8192'] in the Emscripten Compiler Configuration File (.emscripten). On Windows, you will also need --max-stack-size=8192, and also run editbin /stack:33554432 node.exe.

Using "-s SAFE_HEAP=1" will cause a crash on export due to mem alignment issues.  They will likely happen in the material export.  Look into "-s WASM=1".

For unbound types:
Pay attention to ordering of sources in makefile.  Also, make sure to include the appropriate headers in embind files.
