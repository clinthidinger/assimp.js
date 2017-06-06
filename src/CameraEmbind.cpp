
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/camera.h"

using namespace emscripten;

namespace aiCameraEmbind
{
    const std::string getName(aiCamera &camera)
    {
        return std::string(camera.mName.C_Str());
    }
    void setName(aiCamera &camera, const std::string &name)
    {
        camera.mName = aiString(name);
    }
    void setPosition(aiCamera &camera, float x, float y, float z)
    {
        camera.mPosition.Set(x, y, z);
    }
    void setUp(aiCamera &camera, float x, float y, float z)
    {
        camera.mUp.Set(x, y, z);
    }
    void setLookAt(aiCamera &camera, float x, float y, float z)
    {
        camera.mUp.Set(x, y, z);
    }

    DefineGetter(aiCamera, aiVector3D, mPosition, Position)
    DefineGetter(aiCamera, aiVector3D, mUp, Up)
    DefineGetter(aiCamera, aiVector3D, mLookAt, LookAt)
    DefineGetterSetter(aiCamera, float, mHorizontalFOV, HorizontalFOV)
    DefineGetterSetter(aiCamera, float, mClipPlaneNear, ClipPlaneNear)
    DefineGetterSetter(aiCamera, float, mClipPlaneFar, ClipPlaneFar)
    DefineGetterSetter(aiCamera, float, mAspect, Aspect)
}

EMSCRIPTEN_BINDINGS(assimp_camera)
{	
    class_<aiCamera>("aiCamera")
        .constructor<>()
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
