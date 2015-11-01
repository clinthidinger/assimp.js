
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/camera.h"

using namespace emscripten;
//using namespace Assimp;

namespace aiCameraEmbind
{
    DefineGetterSetter(aiCamera, aiString, mName, Name)
    DefineGetterSetter(aiCamera, aiVector3D, mPosition, Position)
    DefineGetterSetter(aiCamera, aiVector3D, mUp, Up)
    DefineGetterSetter(aiCamera, aiVector3D, mLookAt, LookAt)
    DefineGetterSetter(aiCamera, float, mHorizontalFOV, HorizontalFOV)
    DefineGetterSetter(aiCamera, float, mClipPlaneNear, ClipPlaneNear)
    DefineGetterSetter(aiCamera, float, mClipPlaneFar, ClipPlaneFar)
    DefineGetterSetter(aiCamera, float, mAspect, Aspect)
}

EMSCRIPTEN_BINDINGS(ASSIMP)
{	
    class_<aiCamera>("aiCamera")
        .constructor<aiCamera>()
        .function("getCameraMatrix", &aiCamera::GetCameraMatrix)
        .function("getName", &aiCameraEmbind::getName)
        .function("setName", &aiCameraEmbind::setName)
        .function("getPosition", &aiCameraEmbind::getPosition)
        .function("setPosition", &aiCameraEmbind::setPosition)
        .function("getUp", &aiCameraEmbind::getUp)
        .function("setUp", &aiCameraEmbind::setUp)
        .function("getLookAt", &aiCameraEmbind::getLookAt)
        .function("setLookAt", &aiCameraEmbind::setLookAt)
        .function("getHorizontalFOV", &aiCameraEmbind::getHorizontalFOV)
        .function("setHorizontalFOV", &aiCameraEmbind::setHorizontalFOV)
        .function("getClipPlaneNear", &aiCameraEmbind::getClipPlaneNear)
        .function("setClipPlaneNear", &aiCameraEmbind::setClipPlaneNear)
        .function("getClipPlaneFar", &aiCameraEmbind::getClipPlaneFar)
        .function("setClipPlaneFar", &aiCameraEmbind::setClipPlaneFar)
        .function("getAspect", &aiCameraEmbind::getAspect)
        .function("setAspect", &aiCameraEmbind::setAspect)
        ;
} // end EMSCRIPTEN_BINDINGS
