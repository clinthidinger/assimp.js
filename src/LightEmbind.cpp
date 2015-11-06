
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/light.h"

using namespace emscripten;

namespace aiLightEmbind
{
    DefineGetterSetter(aiLight, aiString &, mName, Name)
    DefineGetterSetter(aiLight, aiLightSourceType, mType, Type)
    DefineGetterSetter(aiLight, aiVector3D &, mPosition, Position)
    DefineGetterSetter(aiLight, aiVector3D &, mDirection, Direction)
    DefineGetterSetter(aiLight, float, mAttenuationConstant, AttenuationConstant)
    DefineGetterSetter(aiLight, float, mAttenuationLinear, AttenuationLinear)
    DefineGetterSetter(aiLight, float, mAttenuationQuadratic, AttenuationQuadratic)
    DefineGetterSetter(aiLight, aiColor3D &, mColorDiffuse, ColorDiffuse)
    DefineGetterSetter(aiLight, aiColor3D &, mColorSpecular, ColorSpecular)
    DefineGetterSetter(aiLight, aiColor3D &, mColorAmbient, ColorAmbient)
    DefineGetterSetter(aiLight, float, mAngleInnerCone, AngleInnerCone)
    DefineGetterSetter(aiLight, float, mAngleOuterCone, AngleOuterCone)
}

EMSCRIPTEN_BINDINGS(assimp_light)
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
        .function("getName", &aiLightEmbind::getName)
        .function("setName", &aiLightEmbind::setName)
        .function("getType", &aiLightEmbind::getType)
        .function("setType", &aiLightEmbind::setType)
        .function("getPosition", &aiLightEmbind::getPosition)
        .function("setPosition", &aiLightEmbind::setPosition)
        .function("getDirection", &aiLightEmbind::getDirection)
        .function("setDirection", &aiLightEmbind::setDirection)
        .function("getAttenuationConstant", &aiLightEmbind::getAttenuationConstant)
        .function("setAttenuationConstant", &aiLightEmbind::setAttenuationConstant)
        .function("getAttenuationLinear", &aiLightEmbind::getAttenuationLinear)
        .function("setAttenuationLinear", &aiLightEmbind::setAttenuationLinear)
        .function("getAttenuationQuadratic", &aiLightEmbind::getAttenuationQuadratic)
        .function("setAttenuationQuadratic", &aiLightEmbind::setAttenuationQuadratic)
        .function("getColorDiffuse", &aiLightEmbind::getColorDiffuse)
        .function("setColorDiffuse", &aiLightEmbind::setColorDiffuse)
        .function("getColorSpecular", &aiLightEmbind::getColorSpecular)
        .function("setColorSpecular", &aiLightEmbind::setColorSpecular)
        .function("getColorAmbient", &aiLightEmbind::getColorAmbient)
        .function("setColorAmbient", &aiLightEmbind::setColorAmbient)
        .function("getAngleInnerCone", &aiLightEmbind::getAngleInnerCone)
        .function("setAngleInnerCone", &aiLightEmbind::setAngleInnerCone)
        .function("getAngleOuterCone", &aiLightEmbind::getAngleOuterCone)
        .function("setAngleOuterCone", &aiLightEmbind::setAngleOuterCone)
        ;
} // end EMSCRIPTEN_BINDINGS
