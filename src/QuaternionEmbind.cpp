
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/quaternion.h"
#include "assimp/vector3.h"
#include "assimp/matrix3x3.h"

using namespace emscripten;

#define TReal float

namespace aiQuaternionEmbind
{
    DefineGetterSetter(aiQuaternion, TReal, x, X)
    DefineGetterSetter(aiQuaternion, TReal, y, Y)
    DefineGetterSetter(aiQuaternion, TReal, z, Z)
    DefineGetterSetter(aiQuaternion, TReal, w, W)
    void set(aiQuaternion &q, TReal w, TReal x, TReal y, TReal z)
    {
        q.w = w;
        q.x = x;
        q.y = y;
        q.z = z;
    }
    void setFromEuler(aiQuaternion &q, TReal x, TReal, TReal y, TReal z)
    {
        q = aiQuaternion(x, y, z);
    }
    void setFromAngleAxis(aiQuaternion &q, const aiVector3D &axis, TReal angle)
    {
        q = aiQuaternion(axis, angle);
    }
    void setFromRotationMatrix(aiQuaternion &q, const aiMatrix3x3 &mtx)
    {
        q = aiQuaternion(mtx);
    }
}


EMSCRIPTEN_BINDINGS(assimp_quaternion)
{	
    class_<aiQuaternion>("aiQuaternion")
        .constructor<>()
        .constructor<TReal, TReal, TReal, TReal>()
        //.constructor<const aiMatrix3x3t<TReal>&>()
        //.constructor<TReal, TReal, TReal>()
        //.constructor<aiVector3D, TReal>()
        //.constructor<aiVector3D>()
        .constructor<const aiQuaternion&>()
        .function("op_mult", &aiQuaternion::operator*)
        .function("op_equal_to", &aiQuaternion::operator==)
        .function("op_not_equal_to", &aiQuaternion::operator!=)
        .function("rotate", &aiQuaternion::Rotate)
        .function("conjugate", &aiQuaternion::Conjugate)
        .function("normalize", &aiQuaternion::Normalize)
        .function("equal", &aiQuaternion::Equal)
        .class_function("interpolate", &aiQuaternion::Interpolate)
        .function("getMatrix", &aiQuaternion::GetMatrix)
        .function("getX", &aiQuaternionEmbind::getX)
        .function("setX", &aiQuaternionEmbind::setX)
        .function("getY", &aiQuaternionEmbind::getY)
        .function("setY", &aiQuaternionEmbind::setY)
        .function("getZ", &aiQuaternionEmbind::getZ)
        .function("setZ", &aiQuaternionEmbind::setZ)
        .function("getW", &aiQuaternionEmbind::getW)
        .function("setW", &aiQuaternionEmbind::setW)
        .function("set", &aiQuaternionEmbind::set)
        .function("setFromEuler", &aiQuaternionEmbind::setFromEuler)
        .function("setFromAngleAxis", &aiQuaternionEmbind::setFromAngleAxis)
        .function("setFromRotationMatrix", &aiQuaternionEmbind::setFromRotationMatrix)
        ;
} // end EMSCRIPTEN_BINDINGS
