
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/vector3.h"
#include "assimp/quaternion.h"
#include "assimp/matrix3x3.h"
#include "assimp/matrix4x4.h"

using namespace emscripten;

#define TReal float

namespace aiMatrix4x4Embind
{
    DefineGetterSetter(aiMatrix4x4, TReal, a1, A1)
    DefineGetterSetter(aiMatrix4x4, TReal, a2, A2)
    DefineGetterSetter(aiMatrix4x4, TReal, a3, A3)
    DefineGetterSetter(aiMatrix4x4, TReal, a4, A4)
    DefineGetterSetter(aiMatrix4x4, TReal, b1, B1)
    DefineGetterSetter(aiMatrix4x4, TReal, b2, B2)
    DefineGetterSetter(aiMatrix4x4, TReal, b3, B3)
    DefineGetterSetter(aiMatrix4x4, TReal, b4, B4)
    DefineGetterSetter(aiMatrix4x4, TReal, c1, C1)
    DefineGetterSetter(aiMatrix4x4, TReal, c2, C2)
    DefineGetterSetter(aiMatrix4x4, TReal, c3, C3)
    DefineGetterSetter(aiMatrix4x4, TReal, c4, C4)
    DefineGetterSetter(aiMatrix4x4, TReal, d1, D1)
    DefineGetterSetter(aiMatrix4x4, TReal, d2, D2)
    DefineGetterSetter(aiMatrix4x4, TReal, d3, D3)
    DefineGetterSetter(aiMatrix4x4, TReal, d4, D4)

    void set(aiMatrix4x4 &m, 
             TReal a1, TReal a2, TReal a3, TReal a4,
             TReal b1, TReal b2, TReal b3, TReal b4,
             TReal c1, TReal c2, TReal c3, TReal c4,
             TReal d1, TReal d2, TReal d3, TReal d4)
    {
        m.a1 = a1;
        m.a2 = a2;
        m.a3 = a3;
        m.a4 = a4;
        m.b1 = b1;
        m.b2 = b2;
        m.b3 = b3;
        m.b4 = b4;
        m.c1 = c1;
        m.c2 = c2;
        m.c3 = c3;
        m.c4 = c4;
        m.d1 = d1;
        m.d2 = d2;
        m.d3 = d3;
        m.d4 = d4;
    }
}

EMSCRIPTEN_BINDINGS(assimp_matrix4x4)
{   
    class_<aiMatrix4x4>("aiMatrix4x4")
        .constructor<>()
        .constructor<TReal, TReal, TReal, TReal,  TReal, TReal, TReal, TReal,  TReal, TReal, TReal, TReal,  TReal, TReal, TReal, TReal>()
        .constructor<const aiMatrix3x3 &>()
        .constructor<const aiVector3D&, const aiQuaternion&, const aiVector3D&>()
        .function("at", select_overload<TReal *(unsigned int)>(&aiMatrix4x4::operator[]), allow_raw_pointers())
        .function("at", select_overload<const TReal *(unsigned int) const>(&aiMatrix4x4::operator[]), allow_raw_pointers())
        .function("op_equal_to", &aiMatrix4x4::operator==)
        .function("op_not_equal_to", &aiMatrix4x4::operator!=)
        .function("equal", &aiMatrix4x4::Equal)
        .function("op_mult_equals", &aiMatrix4x4::operator*=)
        .function("op_mult", &aiMatrix4x4::operator*)
        .function("transpose", &aiMatrix4x4::Transpose)
        .function("inverse", &aiMatrix4x4::Inverse)
        .function("determinant", &aiMatrix4x4::Determinant)
        .function("isIdentity", &aiMatrix4x4::IsIdentity)
        .function("decompose", &aiMatrix4x4::Decompose)
        .function("decomposeNoScaling", &aiMatrix4x4::DecomposeNoScaling)
        .function("fromEulerAnglesXYZ", select_overload<aiMatrix4x4& (TReal, TReal, TReal)>(&aiMatrix4x4::FromEulerAnglesXYZ))
        .function("fromEulerAnglesXYZ", select_overload<aiMatrix4x4& (const aiVector3t<TReal> &)>(&aiMatrix4x4::FromEulerAnglesXYZ))
        .class_function("rotationX", &aiMatrix4x4::RotationX)
        .class_function("rotationY", &aiMatrix4x4::RotationY)
        .class_function("rotationZ", &aiMatrix4x4::RotationZ)
        .class_function("rotation", &aiMatrix4x4::Rotation)
        .class_function("translation", &aiMatrix4x4::Translation)
        .class_function("scaling", &aiMatrix4x4::Scaling)
        .class_function("fromToMatrix", &aiMatrix4x4::FromToMatrix)
        .function("getA1", &aiMatrix4x4Embind::getA1)
        .function("setA1", &aiMatrix4x4Embind::setA1)
        .function("getA2", &aiMatrix4x4Embind::getA2)
        .function("setA2", &aiMatrix4x4Embind::setA2)
        .function("getA3", &aiMatrix4x4Embind::getA3)
        .function("setA3", &aiMatrix4x4Embind::setA3)
        .function("getA4", &aiMatrix4x4Embind::getA4)
        .function("setA4", &aiMatrix4x4Embind::setA4)
        .function("getB1", &aiMatrix4x4Embind::getB1)
        .function("setB1", &aiMatrix4x4Embind::setB1)
        .function("getB2", &aiMatrix4x4Embind::getB2)
        .function("setB2", &aiMatrix4x4Embind::setB2)
        .function("getB3", &aiMatrix4x4Embind::getB3)
        .function("setB3", &aiMatrix4x4Embind::setB3)
        .function("getB4", &aiMatrix4x4Embind::getB4)
        .function("setB4", &aiMatrix4x4Embind::setB4)
        .function("getC1", &aiMatrix4x4Embind::getC1)
        .function("setC1", &aiMatrix4x4Embind::setC1)
        .function("getC2", &aiMatrix4x4Embind::getC2)
        .function("setC2", &aiMatrix4x4Embind::setC2)
        .function("getC3", &aiMatrix4x4Embind::getC3)
        .function("setC3", &aiMatrix4x4Embind::setC3)
        .function("getC4", &aiMatrix4x4Embind::getC4)
        .function("setC4", &aiMatrix4x4Embind::setC4)
        .function("getD1", &aiMatrix4x4Embind::getD1)
        .function("setD1", &aiMatrix4x4Embind::setD1)
        .function("getD2", &aiMatrix4x4Embind::getD2)
        .function("setD2", &aiMatrix4x4Embind::setD2)
        .function("getD3", &aiMatrix4x4Embind::getD3)
        .function("setD3", &aiMatrix4x4Embind::setD3)
        .function("getD4", &aiMatrix4x4Embind::getD4)
        .function("setD4", &aiMatrix4x4Embind::setD4)
        .function("set", &aiMatrix4x4Embind::set)
        ;

} // end EMSCRIPTEN_BINDINGS
