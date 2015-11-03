
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/types.h"

using namespace emscripten;

namespace aiStringEmbind
{
    DefineGetterSetter(aiString, size_t, length, Length)
    DefineGetter(aiString, char *, data, Data)
}

namespace aiColor3DEmbind
{
    DefineGetterSetter(aiColor3D, float, r, R)
    DefineGetterSetter(aiColor3D, float, g, G)
    DefineGetterSetter(aiColor3D, float, b, B)
}

namespace aiRayEmbind
{
    DefineGetterSetter(aiRay, aiVector3D, pos, Pos)
    DefineGetterSetter(aiRay, aiVector3D, dir, Dir)
}

namespace aiPlaneEmbind
{
    DefineGetterSetter(aiPlane, float, a, A)
    DefineGetterSetter(aiPlane, float, b, B)
    DefineGetterSetter(aiPlane, float, c, C)
    DefineGetterSetter(aiPlane, float, d, D)
}

namespace aiMemoryInfoEmbind
{
    DefineGetterSetter(aiMemoryInfo, unsigned int, textures, Textures)
    DefineGetterSetter(aiMemoryInfo, unsigned int, materials, Materials)
    DefineGetterSetter(aiMemoryInfo, unsigned int, meshes, Meshes)
    DefineGetterSetter(aiMemoryInfo, unsigned int, nodes, Nodes)
    DefineGetterSetter(aiMemoryInfo, unsigned int, animations, Animations)
    DefineGetterSetter(aiMemoryInfo, unsigned int, cameras, Cameras)
    DefineGetterSetter(aiMemoryInfo, unsigned int, lights, Lights)
    DefineGetterSetter(aiMemoryInfo, unsigned int, total, Total)
}

EMSCRIPTEN_BINDINGS(ASSIMP)
{	
    class_<aiPlane>("aiPlane")
        .constructor<>()
        .constructor<float, float, float, float>()
        .constructor<const aiPlane&>()
        .function("getA", &aiPlaneEmbind::getA)
        .function("setA", &aiPlaneEmbind::setA)
        .function("getB", &aiPlaneEmbind::getB)
        .function("setB", &aiPlaneEmbind::setB)
        .function("getC", &aiPlaneEmbind::getC)
        .function("setC", &aiPlaneEmbind::setC)
        .function("getD", &aiPlaneEmbind::getD)
        .function("setD", &aiPlaneEmbind::setD)
        ;

    class_<aiRay>("aiRay")
        .constructor<>()
        .constructor<const aiVector3D&, const aiVector3D&>()
        .constructor<const aiRay&>()
        .function("getPos", &aiRayEmbind::getPos)
        .function("setPos", &aiRayEmbind::setPos)
        .function("getDir", &aiRayEmbind::getDir)
        .function("setPos", &aiRayEmbind::setDir)
        ;

    class_<aiColor3D>("aiColor3D")
        .constructor<>()
        .constructor<float, float, float>()
        .constructor<float>()
        .constructor<const aiColor3D&>()
        .function("op_equal_to", &aiColor3D::operator==)
        .function("op_not_equal_to", &aiColor3D::operator!=)
        .function("op_less_to", &aiColor3D::operator<)
        .function("op_add", &aiColor3D::operator+)
        .function("op_sub", &aiColor3D::operator+)
        .function("op_mult", select_overload<aiColor3D(const aiColor3D&) const>(&aiColor3D::operator*))
        .function("op_mult", select_overload<aiColor3D(float) const>(&aiColor3D::operator*))
        .function("at", select_overload<float (unsigned int) const>(&aiColor3D::operator[]))
        .function("at", select_overload<float &(unsigned int)>(&aiColor3D::operator[]))
        .function("isBlack", &aiColor3D::IsBlack)
        .function("getR", &aiColor3DEmbind::getR)
        .function("setR", &aiColor3DEmbind::setR)
        .function("getG", &aiColor3DEmbind::getG)
        .function("setG", &aiColor3DEmbind::setG)
        .function("getB", &aiColor3DEmbind::getB)
        .function("setB", &aiColor3DEmbind::setB)
        ;

    class_<aiString>("aiString")
        .constructor<>()
        .constructor<const aiString&>()
        .constructor<const std::string&>()
        .function("set", select_overload<void(const std::string&)>(&aiString::Set))
        .function("set", select_overload<void(const char*)>(&aiString::Set), allow_raw_pointers())
        .function("op_equals", select_overload<aiString &(const char*)>(&aiString::operator=), allow_raw_pointers())
        .function("op_equals", select_overload<aiString &(const std::string&)>(&aiString::operator=))
        .function("op_equal_to", &aiString::operator==, allow_raw_pointers())
        .function("op_not_equal_to", &aiString::operator!=, allow_raw_pointers())
        .function("append", &aiString::Append, allow_raw_pointers())
        .function("clear", &aiString::Clear)
        .function("c_str", &aiString::C_Str, allow_raw_pointers())
        .function("getLength", &aiStringEmbind::getLength)
        .function("setLength", &aiStringEmbind::setLength)
        .function("getData", &aiStringEmbind::getData, allow_raw_pointers())
        ;
    
    enum_<aiReturn>("aiReturn")
        .value("SUCCESS", aiReturn_SUCCESS)
        .value("FAILURE", aiReturn_FAILURE)
        .value("OUTOFMEMORY", aiReturn_OUTOFMEMORY)
        ;

    enum_<aiOrigin>("aiOrigin")
        .value("SET", aiOrigin_SET)
        .value("CUR", aiOrigin_CUR)
        .value("END", aiOrigin_END)
        ;

    enum_<aiDefaultLogStream>("aiDefaultLogStream")
        .value("FILE", aiDefaultLogStream_FILE)
        .value("STDOUT", aiDefaultLogStream_STDOUT)
        .value("STDERR", aiDefaultLogStream_STDERR)
        .value("DEBUGGER", aiDefaultLogStream_DEBUGGER)
        .value("STDERR", aiDefaultLogStream_STDERR)
        ;

    class_<aiMemoryInfo>("aiMemoryInfo")
        .constructor<>()
        .function("getTextures", &aiMemoryInfoEmbind::getTextures)
        .function("setTextures", &aiMemoryInfoEmbind::setTextures)
        .function("getMaterials", &aiMemoryInfoEmbind::getMaterials)
        .function("setMaterials", &aiMemoryInfoEmbind::setMaterials)
        .function("getMeshes", &aiMemoryInfoEmbind::getMeshes)
        .function("setMeshes", &aiMemoryInfoEmbind::setMeshes)
        .function("getNodes", &aiMemoryInfoEmbind::getNodes)
        .function("setNodes", &aiMemoryInfoEmbind::setNodes)
        .function("getAnimations", &aiMemoryInfoEmbind::getAnimations)
        .function("setAnimations", &aiMemoryInfoEmbind::setAnimations)
        .function("getCameras", &aiMemoryInfoEmbind::getCameras)
        .function("setCameras", &aiMemoryInfoEmbind::setCameras)
        .function("getLights", &aiMemoryInfoEmbind::getLights)
        .function("setLights", &aiMemoryInfoEmbind::setLights)
        .function("getTotal", &aiMemoryInfoEmbind::getTotal)
        .function("setTotal", &aiMemoryInfoEmbind::setTotal)
        ;     

} // end EMSCRIPTEN_BINDINGS
