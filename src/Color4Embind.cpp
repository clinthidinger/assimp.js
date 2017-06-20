
#include <emscripten/bind.h>
#include <cmath>
#include "UtilEmbind.h"
#include "assimp/color4.h"
#include "assimp/color4.inl"

using namespace emscripten;

#define TReal float

namespace aiColor4DEmbind
{
    DefineGetterSetter(aiColor4D, TReal, r, R)
    DefineGetterSetter(aiColor4D, TReal, g, G)
    DefineGetterSetter(aiColor4D, TReal, b, B)
    DefineGetterSetter(aiColor4D, TReal, a, A)
    void set(aiColor4D &c, TReal r, TReal g, TReal b, TReal a)
    {
        c.r = r;
        c.g = g;
        c.b = b;
        c.a = a;
    }
}

EMSCRIPTEN_BINDINGS(assimp_color4)
{
	class_<aiColor4D>("aiColor4D")
		.constructor()
		.constructor<TReal, TReal, TReal, TReal>()
    	//.constructor<TReal>()
    	.constructor<const aiColor4D&>()
    	.function("op_plus_equals", &aiColor4D::operator+=)
    	.function("op_minus_equals", &aiColor4D::operator-=)
    	.function("op_mult_equals", &aiColor4D::operator*=)
    	.function("op_div_equals", &aiColor4D::operator/=)
    	.function("op_equal_to", &aiColor4D::operator==)
    	.function("op_not_equal_to", &aiColor4D::operator!=)
    	.function("op_less_than", &aiColor4D::operator<)
    	.function("at", select_overload<TReal(unsigned int) const>(&aiColor4D::operator[]))
    	.function("at", select_overload<TReal &(unsigned int)>(&aiColor4D::operator[]))
    	.function("isBlack", &aiColor4D::IsBlack)
    	.function("getR", &aiColor4DEmbind::getR)
    	.function("setR", &aiColor4DEmbind::setR)
    	.function("getG", &aiColor4DEmbind::getG)
    	.function("setG", &aiColor4DEmbind::setG)
    	.function("getB", &aiColor4DEmbind::getB)
    	.function("setB", &aiColor4DEmbind::setB)
    	.function("set", &aiColor4DEmbind::set)
    	;
} // end EMSCRIPTEN_BINDINGS
