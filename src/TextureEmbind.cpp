
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/texture.h"

using namespace emscripten;

namespace aiTexelEmbind
{
    DefineGetterSetter(aiTexel, unsigned char, b, B)
    DefineGetterSetter(aiTexel, unsigned char, g, G)
    DefineGetterSetter(aiTexel, unsigned char, r, R)
    DefineGetterSetter(aiTexel, unsigned char, a, A)

    void set(aiTexel &texel, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        texel.r = r;
        texel.g = g;
        texel.b = b;
        texel.a = a;
    }
}

namespace aiTextureEmbind
{
    DefineGetterSetter(aiTexture, unsigned int, mWidth, Width)
    DefineGetterSetter(aiTexture, unsigned int, mHeight, Height)
    DefineGetterSetter(aiTexture, aiTexel *, pcData, Data)

    std::string getAchFormatHint(const aiTexture &texture)
    {
        return std::string(texture.achFormatHint);
    }

    aiTexel *at(aiTexture &texture, unsigned int index)
    {
        return &texture.pcData[index];
    }

    aiTexel *at(aiTexture &texture,unsigned int rowIndex, unsigned int colIndex)
    {
        unsigned int index = (colIndex * texture.mWidth) + rowIndex;
        return at(texture, index);
    }
}

EMSCRIPTEN_BINDINGS(assimp_texture)
{	
    class_<aiTexel>("aiTexel")
        .function("op_equal_to", &aiTexel::operator==)
        .function("op_not_equal_to", &aiTexel::operator!=)
        .function("color4_cast", &aiTexel::operator aiColor4D)
        .function("getB", &aiTexelEmbind::getB)
        .function("setB", &aiTexelEmbind::setB)
        .function("getG", &aiTexelEmbind::getG)
        .function("setG", &aiTexelEmbind::setG)
        .function("getR", &aiTexelEmbind::getR)
        .function("setR", &aiTexelEmbind::setR)
        .function("getA", &aiTexelEmbind::getA)
        .function("setA", &aiTexelEmbind::setA)
        .function("set", &aiTexelEmbind::set)
        ;
        
    class_<aiTexture>("aiTexture")
        .constructor<aiTexture>()
        .function("getWidth", &aiTextureEmbind::getWidth)
        .function("setWidth", &aiTextureEmbind::setWidth)
        .function("getHeight", &aiTextureEmbind::getHeight)
        .function("setHeight", &aiTextureEmbind::setHeight)
        .function("getAchFormatHint", &aiTextureEmbind::getAchFormatHint, allow_raw_pointers())
        .function("at", select_overload<aiTexel *(aiTexture &, unsigned int, unsigned int)>(&aiTextureEmbind::at), allow_raw_pointers())
        .function("at", select_overload<aiTexel *(aiTexture &, unsigned int)>(&aiTextureEmbind::at), allow_raw_pointers())
        .function("getData", &aiTextureEmbind::getData, allow_raw_pointers())
        .function("setData", &aiTextureEmbind::setData, allow_raw_pointers())
        .function("checkFormat", &aiTexture::CheckFormat, allow_raw_pointers())
        ;
} // end EMSCRIPTEN_BINDINGS
