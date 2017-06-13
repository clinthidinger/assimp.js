
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
    //DefineGetterSetter(aiNodeAnim, aiVectorKey *, mPositionKeys, PositionKeys)
    DefineArrayIndexRefGetterSetter(aiNodeAnim, aiVectorKey, mPositionKeys, PositionKey)
    DefineGetterSetter(aiNodeAnim, unsigned int, mNumRotationKeys, NumRotationKeys)
    //DefineGetterSetter(aiNodeAnim, aiQuatKey *, mRotationKeys, RotationKeys)
    DefineArrayIndexRefGetterSetter(aiNodeAnim, aiQuatKey, mRotationKeys, RotationKey)
    DefineGetterSetter(aiNodeAnim, unsigned int, mNumScalingKeys, NumScalingKeys)
    //DefineGetterSetter(aiNodeAnim, aiVectorKey *, mScalingKeys, ScalingKeys)
    DefineArrayIndexRefGetterSetter(aiNodeAnim, aiVectorKey, mScalingKeys, ScalingKey)
    DefineGetterSetter(aiNodeAnim, aiAnimBehaviour, mPreState, PreState)
    DefineGetterSetter(aiNodeAnim, aiAnimBehaviour, mPostState, PostState)
}

namespace aiMeshAnimEmbind
{
    DefineGetterSetter(aiMeshAnim, aiString, mName, Name)
    DefineGetterSetter(aiMeshAnim, unsigned int, mNumKeys, NumKeys)
    //DefineGetterSetter(aiMeshAnim, aiMeshKey *, mKeys, Keys)
    DefineArrayIndexRefGetterSetter(aiMeshAnim, aiMeshKey, mKeys, Key)
}

namespace aiAnimationEmbind
{
    DefineGetterSetter(aiAnimation, aiString, mName, Name)
    DefineGetterSetter(aiAnimation, double, mDuration, Duration)
    DefineGetterSetter(aiAnimation, double, mTicksPerSecond, TicksPerSecond)
    DefineGetterSetter(aiAnimation, unsigned int, mNumChannels, NumChannels)
    //DefineGetterSetter(aiAnimation, aiNodeAnim **, mChannels, Channels)
    DefineArrayIndexGetterSetter(aiAnimation, aiNodeAnim *, mChannels, Channel)
    DefineGetterSetter(aiAnimation, unsigned int, mNumMeshChannels, NumMeshChannels)
    //DefineGetterSetter(aiAnimation, aiMeshAnim**, mMeshChannels, MeshChannel)
    DefineArrayIndexGetterSetter(aiAnimation, aiMeshAnim *, mMeshChannels, MeshChannel)
}

EMSCRIPTEN_BINDINGS(assimp_anim)
{       
    class_<aiVectorKey>("aiVectorKey")
        .constructor<>()
        .constructor<double, const aiVector3D &>()
        .function("getTime", &aiVectorKeyEmbind::getTime)
        .function("setTime", &aiVectorKeyEmbind::setTime)
        .function("getValue", &aiVectorKeyEmbind::getValue)
        .function("setValue", &aiVectorKeyEmbind::setValue)
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
        .function("getValue", &aiQuatKeyEmbind::getValue)
        .function("setValue", &aiQuatKeyEmbind::setValue)
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
        .function("getValue", &aiMeshKeyEmbind::getValue)
        .function("setValue", &aiMeshKeyEmbind::setValue)
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
        .function("getPositionKey", &aiNodeAnimEmbind::getPositionKey, allow_raw_pointers())
        .function("setPositionKey", &aiNodeAnimEmbind::setPositionKey, allow_raw_pointers())
        .function("getNumRotationKeys", &aiNodeAnimEmbind::getNumRotationKeys)
        .function("setNumRotationKeys", &aiNodeAnimEmbind::setNumRotationKeys)
        .function("getRotationKey", &aiNodeAnimEmbind::getRotationKey, allow_raw_pointers())
        .function("setRotationKey", &aiNodeAnimEmbind::setRotationKey, allow_raw_pointers())
        .function("getNumScalingKeys", &aiNodeAnimEmbind::getNumScalingKeys)
        .function("setNumScalingKeys", &aiNodeAnimEmbind::setNumScalingKeys)
        .function("getScalingKey", &aiNodeAnimEmbind::getScalingKey, allow_raw_pointers())
        .function("setScalingKey", &aiNodeAnimEmbind::setScalingKey, allow_raw_pointers())
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
        .function("getKey", &aiMeshAnimEmbind::getKey, allow_raw_pointers())
        .function("setKey", &aiMeshAnimEmbind::setKey, allow_raw_pointers())
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
        .function("getChannel", &aiAnimationEmbind::getChannel, allow_raw_pointers())
        .function("setChannel", &aiAnimationEmbind::setChannel, allow_raw_pointers())
        .function("getNumMeshChannels", &aiAnimationEmbind::getNumMeshChannels)
        .function("setNumMeshChannels", &aiAnimationEmbind::setNumMeshChannels)
        .function("getMeshChannel", &aiAnimationEmbind::getMeshChannel, allow_raw_pointers())
        .function("setMeshChannel", &aiAnimationEmbind::setMeshChannel, allow_raw_pointers())
        ;

} // end EMSCRIPTEN_BINDINGS
