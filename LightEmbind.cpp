
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/light.h"

using namespace emscripten;
using namespace Assimp;


EMSCRIPTEN_BINDINGS(ASSIMP)
{   
    enum_<aiLightSourceType>("aiLightSourceType")
        .value("UNDEFINED", aiLightSource_UNDEFINED)
        .value("DIRECTIONAL", aiLightSource_DIRECTIONAL)
        .value("POINT", aiLightSource_POINT)
        .value("SPOT", aiLightSource_SPOT)
        .value("AMBIENT", aiLightSource_AMBIENT)
        ;   

    class_<aiLight>("aiLight")
        .constructor<aiLight>()
        .function("getName", &getName)
        .function("setName", &setName)
        .function("getType", &getType)
        .function("setType", &setType)
        .function("getPosition", &getPosition)
        .function("setPosition", &setPosition)
        .function("getDirection", &getDirection)
        .function("setDirection", &setDirection)
        .function("getAttenuationConstant", &getAttenuationConstant)
        .function("setAttenuationConstant", &setAttenuationConstant)
        .function("getAttenuationQuadratic", &getAttenuationQuadratic)
        .function("setAttenuationQuadratic", &setAttenuationQuadratic)
        .function("getColorDiffuse", &getColorDiffuse)
        .function("setColorDiffuse", &setColorDiffuse)
        .function("getColorSpecular", &getColorSpecular)
        .function("setColorSpecular", &setColorSpecular)
        .function("getColorAmbient", &getColorAmbient)
        .function("setColorAmbient", &setColorAmbient)
        .function("getAngleInnerCone", &getAngleInnerCone)
        .function("setAngleInnerCone", &setAngleInnerCone)
        .function("getAngleOuterCone", &getAngleOuterCone)
        .function("setAngleOuterCone", &setAngleOuterCone)
        ;
} // end EMSCRIPTEN_BINDINGS
