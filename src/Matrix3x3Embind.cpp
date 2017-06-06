
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/vector2.h"
#include "assimp/vector2.inl"
#include "assimp/vector3.h"
#include "assimp/vector3.inl"
#include "assimp/matrix3x3.h"
#include "assimp/matrix3x3.inl"
#include "assimp/matrix4x4.h"
#include "assimp/matrix4x4.inl"


using namespace emscripten;

#define TReal float

namespace aiMatrix3x3Embind
{
    DefineGetterSetter(aiMatrix3x3, TReal, a1, A1)
    DefineGetterSetter(aiMatrix3x3, TReal, a2, A2)
    DefineGetterSetter(aiMatrix3x3, TReal, a3, A3)
    DefineGetterSetter(aiMatrix3x3, TReal, b1, B1)
    DefineGetterSetter(aiMatrix3x3, TReal, b2, B2)
    DefineGetterSetter(aiMatrix3x3, TReal, b3, B3)
    DefineGetterSetter(aiMatrix3x3, TReal, c1, C1)
    DefineGetterSetter(aiMatrix3x3, TReal, c2, C2)
    DefineGetterSetter(aiMatrix3x3, TReal, c3, C3)

    void set(aiMatrix3x3 &m, 
             TReal a1, TReal a2, TReal a3,
             TReal b1, TReal b2, TReal b3,
             TReal c1, TReal c2, TReal c3)
    {
        m.a1 = a1;
        m.a2 = a2;
        m.a3 = a3;
        m.b1 = b1;
        m.b2 = b2;
        m.b3 = b3;
        m.c1 = c1;
        m.c2 = c2;
        m.c3 = c3;
    }
}

EMSCRIPTEN_BINDINGS(assimp_matrix3x3)
{   
    class_<aiMatrix3x3>("aiMatrix3x3")
        .constructor<>()
        .constructor<TReal, TReal, TReal, TReal, TReal, TReal, TReal, TReal, TReal>()
        .function("op_mult_equals", &aiMatrix3x3::operator*=)
        .function("op_mult", &aiMatrix3x3::operator*)
        .function("op_equal_to", &aiMatrix3x3::operator==)
        .function("op_not_equal_to", &aiMatrix3x3::operator!=)
        .function("at", select_overload<TReal *(unsigned int)>(&aiMatrix3x3::operator[]), allow_raw_pointers())
        .function("at", select_overload<const TReal *(unsigned int) const>(&aiMatrix3x3::operator[]), allow_raw_pointers())
        .function("equal", &aiMatrix3x3::Equal)
        .function("transpose", &aiMatrix3x3::Transpose)
        .function("inverse", &aiMatrix3x3::Inverse)
        .function("determinant", &aiMatrix3x3::Determinant)
        .class_function("rotationZ", &aiMatrix3x3::RotationZ)
        .class_function("rotation", &aiMatrix3x3::Rotation)
        .class_function("translation", &aiMatrix3x3::Translation)
        .class_function("fromToMatrix", &aiMatrix3x3::FromToMatrix)
        .function("getA1", &aiMatrix3x3Embind::getA1)
        .function("setA1", &aiMatrix3x3Embind::setA1)
        .function("getA2", &aiMatrix3x3Embind::getA2)
        .function("setA2", &aiMatrix3x3Embind::setA2)
        .function("getA3", &aiMatrix3x3Embind::getA3)
        .function("setA3", &aiMatrix3x3Embind::setA3)
        .function("getB1", &aiMatrix3x3Embind::getB1)
        .function("setB1", &aiMatrix3x3Embind::setB1)
        .function("getB2", &aiMatrix3x3Embind::getB2)
        .function("setB2", &aiMatrix3x3Embind::setB2)
        .function("getB3", &aiMatrix3x3Embind::getB3)
        .function("setB3", &aiMatrix3x3Embind::setB3)
        .function("getC1", &aiMatrix3x3Embind::getC1)
        .function("setC1", &aiMatrix3x3Embind::setC1)
        .function("getC2", &aiMatrix3x3Embind::getC2)
        .function("setC2", &aiMatrix3x3Embind::setC2)
        .function("getC3", &aiMatrix3x3Embind::getC3)
        .function("setC3", &aiMatrix3x3Embind::setC3)
        .function("set", &aiMatrix3x3Embind::set)
        ;

} // end EMSCRIPTEN_BINDINGS
