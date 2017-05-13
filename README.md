Work in Porgress

Port of Open Asset Import Library (ASSIMP) to javascript with emscripten.
See https://github.com/assimp/assimp and http://assimp.sourceforge.net.

Build:

Go to https://kripken.github.io/emscripten-site/docs/getting_started/downloads.html to get emscripten.

./emsdk update
./emsdk install --build=Release latest
./emsdk activate --build=Release latest

source ${YOUR_EMSCRIPTEN_DIR}/emsdk_env.sh

make


Run:

python -m SimpleHTTPServer 8000

Then open example.html.


TODO:

Been years since messing with this so figure out where this is at.  I can't remember what these notes are about.





For unbound types:
Pay attention to ordering of sources in makefile.  Also, make sure to include the appropriate headers in embind files.

Getter setter for indexed array.
Finish mesh embind.
User array getter setters where needed.
Make aiString to std::string.

Threejs data.

Module name not working.

MAR 12: wrap meshes and things with std::vec from scene