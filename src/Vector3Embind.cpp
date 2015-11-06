
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/vector3.h"
#include "assimp/matrix3x3.h"
#include "assimp/matrix4x4.h"

using namespace emscripten;

#define TReal float

namespace aiVector3DEmbind
{
    DefineGetterSetter(aiVector3D, TReal, x, X)
    DefineGetterSetter(aiVector3D, TReal, y, Y)
    DefineGetterSetter(aiVector3D, TReal, z, Z)
    void set(aiVector3D &v, TReal x, TReal y, TReal z)
    {
        v.x = x;
        v.y = y;
        v.z = z;
    }
}

EMSCRIPTEN_BINDINGS(assimp_vector3)
{	
     class_<aiVector3D>("aiVector3D")
        .constructor<>()
        .constructor<TReal, TReal, TReal>()
        .constructor<const aiVector3D&>()
        .function("op_plus_equals", &aiVector3D::operator+=)
        .function("op_minus_equals", &aiVector3D::operator-=)
        .function("op_mult_equals", select_overload<const aiVector3D &(TReal)>(&aiVector3D::operator*=))
        .function("op_mult_equals", select_overload<aiVector3D &(const aiMatrix3x3 &)>(&aiVector3D::operator*=))
        .function("op_mult_equals", select_overload<aiVector3D &(const aiMatrix4x4&)>(&aiVector3D::operator*=))
        .function("op_div_equals", &aiVector3D::operator/=)
        .function("op_equal_to", &aiVector3D::operator==)
        .function("op_not_equal_to", &aiVector3D::operator!=)
        .function("op_less_than", &aiVector3D::operator<)
        .function("at", select_overload<TReal (unsigned int) const>(&aiVector3D::operator[]))
        .function("at", select_overload<TReal &(unsigned int)>(&aiVector3D::operator[]))
        .function("squareLength", &aiVector3D::SquareLength)
        .function("length", &aiVector3D::Length)
        .function("normalize", &aiVector3D::Normalize)
        .function("equal", &aiVector3D::Equal)
        .function("op_equals", &aiVector3D::operator=)
        .function("symMul", &aiVector3D::SymMul)
        .function("getX", &aiVector3DEmbind::getX)
        .function("setX", &aiVector3DEmbind::setX)
        .function("getY", &aiVector3DEmbind::getY)
        .function("setY", &aiVector3DEmbind::setY)
        .function("getY", &aiVector3DEmbind::getZ)
        .function("setY", &aiVector3DEmbind::setZ)
        .function("set", &aiVector3DEmbind::set)
        ;
} // end EMSCRIPTEN_BINDINGS
