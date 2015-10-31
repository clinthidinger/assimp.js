
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/texture.h"

using namespace emscripten;
using namespace Assimp;


EMSCRIPTEN_BINDINGS(ASSIMP)
{	
    class_<aiTexel>("aiTexel")
        .function("op_equal_to", &aiTexel::operator==)
        .function("op_not_equal_to", &aiTexel::operator!=)
        .function("color_cast", &aiTexel::operator  aiColor4D)
        .function("getB", &getB)
        .function("setB", &setB)
        .function("getG", &getG)
        .function("setG", &setG)
        .function("getR", &getR)
        .function("setR", &setR)
        .function("getA", &getA)
        .function("setA", &setA)
        .function("set", &set)
        .function("at", &at)
        ;
        
    class_<aiTexture>("aiTexture")
        .constructor<aiTexture>()
        .function("getWidth", &getWidth)
        .function("setWidth", &setWidth)
        .function("getHeight", &getHeight)
        .function("setHeight", &setHeight)
        .function("getAchFormatHint", &getAchFormatHint)
        .function("setAchFormatHint", &setAchFormatHint)
        .function("at", &at, allow_raw_pointers())
        .function("getData", &getData, allow_raw_pointers())
        .function("setData", &setData, allow_raw_pointers())
        .function("checkFormat", &aiTexture::CheckFormat)
        ;
} // end EMSCRIPTEN_BINDINGS
