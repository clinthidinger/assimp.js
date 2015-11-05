
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/anim.h"

using namespace emscripten;

//#define TReal float

namespace aiVectorKeyEmbind
{
    DefineGetterSetter(aiVectorKey, double, mTime, Time)
    DefineGetterSetter(aiVectorKey, aiVector3D, mValue, Value)
}

namespace aiQuatKeyEmbind
{
    DefineGetterSetter(aiQuatKey, double, mTime, Time)
    DefineGetterSetter(aiQuatKey, aiQuaternion, mValue, Value)
}

namespace aiMeshKeyEmbind
{
    DefineGetterSetter(aiMeshKey, double, mTime, Time)
    DefineGetterSetter(aiMeshKey, unsigned int, mValue, Value)
}

namespace aiNodeAnimEmbind
{
    DefineGetterSetter(aiNodeAnim, aiString, mNodeName, NodeName)
    DefineGetterSetter(aiNodeAnim, unsigned int, mNumPositionKeys, NumPositionKeys)
    DefineGetterSetter(aiNodeAnim, aiVectorKey *, mPositionKeys, PositionKeys)
    DefineGetterSetter(aiNodeAnim, unsigned int, mNumRotationKeys, NumRotationKeys)
    DefineGetterSetter(aiNodeAnim, aiQuatKey *, mRotationKeys, RotationKeys)
    DefineGetterSetter(aiNodeAnim, unsigned int, mNumScalingKeys, NumScalingKeys)
    DefineGetterSetter(aiNodeAnim, aiVectorKey *, mScalingKeys, ScalingKeys)
    DefineGetterSetter(aiNodeAnim, aiAnimBehaviour, mPreState, PreState)
    DefineGetterSetter(aiNodeAnim, aiAnimBehaviour, mPostState, PostState)
}

namespace aiMeshAnimEmbind
{
    DefineGetterSetter(aiMeshAnim, aiString, mName, Name)
    DefineGetterSetter(aiMeshAnim, unsigned int, mNumKeys, NumKeys)
    DefineGetterSetter(aiMeshAnim, aiMeshKey *, mKeys, Keys)
}

namespace aiAnimationEmbind
{
    DefineGetterSetter(aiAnimation, aiString, mName, Name)
    DefineGetterSetter(aiAnimation, double, mDuration, Duration)
    DefineGetterSetter(aiAnimation, double, mTicksPerSecond, TicksPerSecond)
    DefineGetterSetter(aiAnimation, unsigned int, mNumChannels, NumChannels)
    DefineGetterSetter(aiAnimation, aiNodeAnim **, mChannels, Channels)
    DefineGetterSetter(aiAnimation, unsigned int, mNumMeshChannels, NumMeshChannels)
    DefineGetterSetter(aiAnimation, aiMeshAnim**, mMeshChannels, MeshChannels)
}

EMSCRIPTEN_BINDINGS(assimp_anim)
{       
    class_<aiVectorKey>("aiVectorKey")
        .constructor<>()
        .constructor<double, const aiVector3D &>()
        .function("getTime", &aiVectorKeyEmbind::getTime)
        .function("setTime", &aiVectorKeyEmbind::setTime)
        .function("getTime", &aiVectorKeyEmbind::getValue)
        .function("setTime", &aiVectorKeyEmbind::setValue)
        .function("op_equal_to", &aiVectorKey::operator==)
        .function("op_not_equal_to", &aiVectorKey::operator!=)
        .function("op_less_than", &aiVectorKey::operator<)
        .function("op_greater_than", &aiVectorKey::operator>)
        ;

    class_<aiQuatKey>("aiQuatKey")
        .constructor<>()
        .constructor<double, const aiQuaternion &>()
        .function("getTime", &aiQuatKeyEmbind::getTime)
        .function("setTime", &aiQuatKeyEmbind::setTime)
        .function("getTime", &aiQuatKeyEmbind::getValue)
        .function("setTime", &aiQuatKeyEmbind::setValue)
        .function("op_equal_to", &aiQuatKey::operator==)
        .function("op_not_equal_to", &aiQuatKey::operator!=)
        .function("op_less_than", &aiQuatKey::operator<)
        .function("op_greater_than", &aiQuatKey::operator>)
        ;

    class_<aiMeshKey>("aiMeshKey")
        .constructor<>()
        .constructor<double, const unsigned int>()
        .function("getTime", &aiMeshKeyEmbind::getTime)
        .function("setTime", &aiMeshKeyEmbind::setTime)
        .function("getTime", &aiMeshKeyEmbind::getValue)
        .function("setTime", &aiMeshKeyEmbind::setValue)
        .function("op_equal_to", &aiMeshKey::operator==)
        .function("op_not_equal_to", &aiMeshKey::operator!=)
        .function("op_less_than", &aiMeshKey::operator<)
        .function("op_greater_than", &aiMeshKey::operator>)
        ;  

    enum_<aiAnimBehaviour>("aiAnimBehaviour")
        .value("DEFAULT", aiAnimBehaviour_DEFAULT)
        .value("CONSTANT", aiAnimBehaviour_CONSTANT)
        .value("LINEAR", aiAnimBehaviour_LINEAR)
        .value("REPEAT", aiAnimBehaviour_REPEAT)
        ;

    class_<aiNodeAnim>("aiNodeAnim")
        .constructor<>()
        .function("getNodeName", &aiNodeAnimEmbind::getNodeName)
        .function("setNodeName", &aiNodeAnimEmbind::setNodeName)
        .function("getNumPositionKeys", &aiNodeAnimEmbind::getNumPositionKeys)
        .function("setNumPositionKeys", &aiNodeAnimEmbind::setNumPositionKeys)
        .function("getPositionKeys", &aiNodeAnimEmbind::getPositionKeys, allow_raw_pointers())
        .function("setPositionKeys", &aiNodeAnimEmbind::setPositionKeys, allow_raw_pointers())
        .function("getNumRotationKeys", &aiNodeAnimEmbind::getNumRotationKeys)
        .function("setNumRotationKeys", &aiNodeAnimEmbind::setNumRotationKeys)
        .function("getRotationKeys", &aiNodeAnimEmbind::getRotationKeys, allow_raw_pointers())
        .function("setRotationKeys", &aiNodeAnimEmbind::setRotationKeys, allow_raw_pointers())
        .function("getNumScalingKeys", &aiNodeAnimEmbind::getNumScalingKeys)
        .function("setNumScalingKeys", &aiNodeAnimEmbind::setNumScalingKeys)
        .function("getScalingKeys", &aiNodeAnimEmbind::getScalingKeys, allow_raw_pointers())
        .function("setScalingKeys", &aiNodeAnimEmbind::setScalingKeys, allow_raw_pointers())
        .function("getPreState", &aiNodeAnimEmbind::getPreState)
        .function("setPreState", &aiNodeAnimEmbind::setPreState) 
        .function("getPostState", &aiNodeAnimEmbind::getPostState)
        .function("setPostState", &aiNodeAnimEmbind::setPostState)
        ;

    class_<aiMeshAnim>("aiMeshAnim")
        .constructor<>()
        .function("getName", &aiMeshAnimEmbind::getName)
        .function("setName", &aiMeshAnimEmbind::setName)
        .function("getNumKeys", &aiMeshAnimEmbind::getNumKeys)
        .function("setNumKeys", &aiMeshAnimEmbind::setNumKeys)
        .function("getKeys", &aiMeshAnimEmbind::getKeys, allow_raw_pointers())
        .function("setKeys", &aiMeshAnimEmbind::setKeys, allow_raw_pointers())
        ;

    class_<aiAnimation>("aiAnimation")
        .constructor<>()
        .function("getName", &aiAnimationEmbind::getName)
        .function("setName", &aiAnimationEmbind::setName)
        .function("getDuration", &aiAnimationEmbind::getDuration)
        .function("setDuration", &aiAnimationEmbind::setDuration)
        .function("getTicksPerSecond", &aiAnimationEmbind::getTicksPerSecond)
        .function("setTicksPerSecond", &aiAnimationEmbind::setTicksPerSecond)
        .function("getNumChannels", &aiAnimationEmbind::getNumChannels)
        .function("setNumChannels", &aiAnimationEmbind::setNumChannels)
        .function("getChannels", &aiAnimationEmbind::getChannels, allow_raw_pointers())
        .function("setChannels", &aiAnimationEmbind::setChannels, allow_raw_pointers())
        .function("getNumMeshChannels", &aiAnimationEmbind::getNumMeshChannels)
        .function("setNumMeshChannels", &aiAnimationEmbind::setNumMeshChannels)
        .function("getMeshChannels", &aiAnimationEmbind::getMeshChannels, allow_raw_pointers())
        .function("setMeshChannels", &aiAnimationEmbind::setMeshChannels, allow_raw_pointers())
        ;

} // end EMSCRIPTEN_BINDINGS
