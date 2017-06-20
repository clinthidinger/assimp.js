
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/vector2.h"
#include "assimp/vector2.inl"

using namespace emscripten;

#define TReal float

namespace aiVector2DEmbind
{
    DefineGetterSetter(aiVector2D, TReal, x, X)
    DefineGetterSetter(aiVector2D, TReal, y, Y)
    void set(aiVector2D &v, TReal x, TReal y)
    {
        v.x = x;
        v.y = y;
    }
    void op_equals(aiVector2D &v, TReal f)
    {
        v = f;
    }
    TReal at(aiVector2D &v, int index) // This func exists bc of warning.
    {
        return (index == 1) ? v.y : v.x;
    }
}


EMSCRIPTEN_BINDINGS(assimp_vector2)
{	
    class_<aiVector2D>("aiVector2D")
        .constructor<>()
        .constructor<TReal, TReal>()
        .constructor<const aiVector2D&>()
        .function("op_plus_equals", &aiVector2D::operator+=)
        .function("op_minus_equals", &aiVector2D::operator-=)
        .function("op_mult_equals", &aiVector2D::operator*=)
        .function("op_div_equals", &aiVector2D::operator/=)
        .function("op_equal_to", &aiVector2D::operator==)
        .function("op_not_equal_to", &aiVector2D::operator!=)
        //.function("at", select_overload<TReal(unsigned int) const>(&aiVector2D::operator[]))
        //.function("at", select_overload<TReal &(unsigned int)>(&aiVector2D::operator[]))
        .function("at", &aiVector2DEmbind::at)
        .function("squareLength", &aiVector2D::SquareLength)
        .function("length", &aiVector2D::Length)
        .function("normalize", &aiVector2D::Normalize)
        .function("equal", &aiVector2D::Equal)
        .function("op_equals", &aiVector2DEmbind::op_equals)
        .function("symMul", &aiVector2D::SymMul)
        .function("getX", &aiVector2DEmbind::getX)
        .function("setX", &aiVector2DEmbind::setX)
        .function("getY", &aiVector2DEmbind::getY)
        .function("setY", &aiVector2DEmbind::setY)
        .function("set", &aiVector2DEmbind::set)
        ;
} // end EMSCRIPTEN_BINDINGS
