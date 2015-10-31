
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/anim.h"

using namespace emscripten;
using namespace Assimp;


EMSCRIPTEN_BINDINGS(ASSIMP)
{       
     class_<aiVectorKey>("aiVectorKey")
        .constructor<aiVectorKey>()
        .constructor<aiVectorKey>(double, const aiVector3D &)
        ;
} // end EMSCRIPTEN_BINDINGS
