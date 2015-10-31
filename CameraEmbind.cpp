
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/vector3.h"

using namespace emscripten;
using namespace Assimp;


EMSCRIPTEN_BINDINGS(ASSIMP)
{	
    class_<aiCamera>("aiCamera")
        .constructor<aiCamera>()
        .function("getCameraMatrix", &aiCamera::GetCameraMatrix)
        .function("getName", &getName)
        .function("setName", &setName)
        .function("getPosition", &getPosition)
        .function("setPosition", &setPosition)
        .function("getUp", &getUp)
        .function("setUp", &setUp)
        .function("getLookAt", &getLookAt)
        .function("setLookAt", &setLookAt)
        .function("getHorizontalFOV", &getHorizontalFOV)
        .function("setHorizontalFOV", &setHorizontalFOV)
        .function("getClipPlaneNear", &getClipPlaneNear)
        .function("setClipPlaneNear", &setClipPlaneNear)
        .function("getClipPlaneFar", &getClipPlaneFar)
        .function("setClipPlaneFar", &setClipPlaneFar)
        .function("getAspect", &getAspect)
        .function("setAspect", &setAspect)
        ;
} // end EMSCRIPTEN_BINDINGS
