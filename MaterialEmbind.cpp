
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/vector3.h"

using namespace emscripten;
using namespace Assimp;


EMSCRIPTEN_BINDINGS(ASSIMP)
{	
    enum_<aiTextureOp>("aiTextureOp")
        .value("Multiply", aiTextureOp_Multiply)
        .value("Add", aiTextureOp_Add)
        .value("Subtract", aiTextureOp_Subtract)
        .value("Divide", aiTextureOp_Divide)
        .value("SmoothAdd", aiTextureOp_SmoothAdd)
        .value("SignedAdd", aiTextureOp_SignedAdd)
        ;

    enum_<aiTextureMapMode>("aiTextureMapMode")
        .value("Wrap", aiTextureMapMode_Wrap)
        .value("Clamp", aiTextureMapMode_Clamp)
        .value("Decal", aiTextureMapMode_Decal)
        .value("Mirror", aiTextureMapMode_Mirror)
        ;
    
} // end EMSCRIPTEN_BINDINGS
