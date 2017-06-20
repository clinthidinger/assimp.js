
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/material.h"
#include "assimp/material.inl"
#include "assimp/vector2.h"
#include "assimp/vector2.inl"
#include "assimp/types.h"

using namespace emscripten;

namespace aiUVTransformEmbind
{
    void setTranslation(aiUVTransform &xform, float x, float y)
    {
        xform.mTranslation.Set(x, y);
    }
    void setScaling(aiUVTransform &xform, float x, float y)
    {
        xform.mScaling.Set(x, y);
    }
    DefineGetter(aiUVTransform, aiVector2D, mTranslation, Translation)
    DefineGetter(aiUVTransform, aiVector2D, mScaling, Scaling)
    DefineGetterSetter(aiUVTransform, float, mRotation, Rotation)
}

namespace aiMaterialPropertyEmbind
{
    //DefineGetterSetter(aiMaterialProperty, aiString, mKey, Key)
    std::string getKey(aiMaterialProperty &prop)
    {
        return std::string(prop.mKey.C_Str());
    }
    void setKey(aiMaterialProperty &prop, const std::string &key)
    {
        prop.mKey = aiString(key);
    }
    DefineGetterSetter(aiMaterialProperty, unsigned int, mSemantic, Semantic)
    DefineGetterSetter(aiMaterialProperty, unsigned int, mIndex, Index)
    DefineGetterSetter(aiMaterialProperty, unsigned int, mDataLength, DataLength)
    DefineGetterSetter(aiMaterialProperty, aiPropertyTypeInfo, mType, Type)
    DefineGetterSetter(aiMaterialProperty, char*, mData, Data)
}

namespace aiMaterialEmbind
{
    DefineGetterSetter(aiMaterial, aiMaterialProperty**, mProperties, Properties)
    DefineGetterSetter(aiMaterial, unsigned int, mNumProperties, NumProperties)
    DefineGetterSetter(aiMaterial, unsigned int, mNumAllocated, NumAllocated)

    aiMaterialProperty *getProperty(aiMaterial &mat, int index)
    {
        return mat.mProperties[index];
    }
    void setProperty(aiMaterial &mat, int index, aiMaterialProperty *prop)
    {
        mat.mProperties[index] = prop;
    }
    aiReturn getIntBuffer(const aiMaterial &mat, const char* pKey, unsigned int type, unsigned int idx, int* pOut, unsigned int* pMax)
    {
        return mat.Get(pKey, type, idx, pOut, pMax);
    }
    aiReturn getFloatBuffer(const aiMaterial &mat, const char* pKey, unsigned int type, unsigned int idx, float* pOut, unsigned int* pMax)
    {
        return mat.Get(pKey, type, idx, pOut, pMax);
    }
    int getInt(const aiMaterial &mat, const char* pKey, unsigned int type, unsigned int idx)//, int &pOut)
    {
        int pOut = 0;
        aiReturn result = mat.Get(pKey, type, idx, pOut);
        return pOut;
    }
    float getFloat(const aiMaterial &mat, const char* pKey, unsigned int type, unsigned int idx)
    {
        float pOut = 0.0f;
        aiReturn result = mat.Get(pKey, type, idx, pOut);
        return pOut;
    }
    aiString getString(const aiMaterial &mat, const char* pKey, unsigned int type, unsigned int idx)
    {
        aiString pOut;
        aiReturn result = mat.Get(pKey, type, idx, pOut);
        return pOut;
    }
    aiColor3D getColor3D(const aiMaterial &mat, const char* pKey, unsigned int type, unsigned int idx)
    {
        aiColor3D pOut;
        aiReturn result = mat.Get(pKey, type, idx, pOut);
        return pOut;
    }
    aiColor4D getColor4D(const aiMaterial &mat, const char* pKey, unsigned int type, unsigned int idx)
    {
        aiColor4D pOut;
        aiReturn result = mat.Get(pKey, type, idx, pOut);
        return pOut;
    }
    aiUVTransform getUVTransform(const aiMaterial &mat, const char* pKey, unsigned int type, unsigned int idx)
    {
        aiUVTransform pOut;
        aiReturn result = mat.Get(pKey, type, idx, pOut);
        return pOut;
    }
 
    aiReturn addStringProperty(aiMaterial &mat, const aiString* pInput, unsigned int pNumValues, const char* pKey, unsigned int type, unsigned int index)
    {
        return mat.AddProperty(pInput, pKey, type, index);
    }
    aiReturn addVector3Property(aiMaterial &mat, const aiVector3D* pInput, unsigned int pNumValues, const char* pKey, unsigned int type, unsigned int index)
    {
        return mat.AddProperty(pInput, pNumValues, pKey, type, index);
    }
    aiReturn addColor3DProperty(aiMaterial &mat, const aiColor3D* pInput, unsigned int pNumValues, const char* pKey, unsigned int type, unsigned int index)
    {
        return mat.AddProperty(pInput, pNumValues, pKey, type, index);
    }
    aiReturn addColor4DProperty(aiMaterial &mat, const aiColor4D* pInput, unsigned int pNumValues, const char* pKey, unsigned int type, unsigned int index)
    {
        return mat.AddProperty(pInput, pNumValues, pKey, type, index);
    }
    aiReturn addIntProperty(aiMaterial &mat, const int* pInput, unsigned int pNumValues, const char* pKey, unsigned int type, unsigned int index)
    {
        return mat.AddProperty(pInput, pNumValues, pKey, type, index);
    }
    aiReturn addFloatProperty(aiMaterial &mat, const float* pInput, unsigned int pNumValues, const char* pKey, unsigned int type, unsigned int index)
    {
        return mat.AddProperty(pInput, pNumValues, pKey, type, index);
    }
    aiReturn addUVTransformProperty(aiMaterial &mat, const aiUVTransform* pInput, unsigned int pNumValues, const char* pKey, unsigned int type, unsigned int index)
    {
        return mat.AddProperty(pInput, pNumValues, pKey, type, index);
    }
}


EMSCRIPTEN_BINDINGS(assimp_material)
{	
    enum_<aiTextureOp>("aiTextureOp")
        .value("Multiply", aiTextureOp_Multiply)
        .value("Add", aiTextureOp_Add)
        .value("Subtract", aiTextureOp_Subtract)
        .value("Divide", aiTextureOp_Divide)
        .value("SmoothAdd", aiTextureOp_SmoothAdd)
        .value("SignedAdd", aiTextureOp_SignedAdd)
        ;

    enum_<aiTextureMapMode>("aiTextureMapMode")
        .value("Wrap", aiTextureMapMode_Wrap)
        .value("Clamp", aiTextureMapMode_Clamp)
        .value("Decal", aiTextureMapMode_Decal)
        .value("Mirror", aiTextureMapMode_Mirror)
        ;

    enum_<aiTextureMapping>("aiTextureMapping")
        .value("UV", aiTextureMapping_UV)
        .value("SPHERE", aiTextureMapping_SPHERE)
        .value("CYLINDER", aiTextureMapping_CYLINDER)
        .value("BOX", aiTextureMapping_BOX)
        .value("PLANE", aiTextureMapping_PLANE)
        .value("OTHER", aiTextureMapping_OTHER)
        ;

    enum_<aiTextureType>("aiTextureType")
        .value("NONE", aiTextureType_NONE)
        .value("DIFFUSE", aiTextureType_DIFFUSE)
        .value("SPECULAR", aiTextureType_SPECULAR)
        .value("AMBIENT", aiTextureType_AMBIENT)
        .value("EMISSIVE", aiTextureType_EMISSIVE)
        .value("HEIGHT", aiTextureType_HEIGHT)
        .value("NORMALS", aiTextureType_NORMALS)
        .value("SHININESS", aiTextureType_SHININESS)
        .value("OPACITY", aiTextureType_OPACITY)
        .value("DISPLACEMENT", aiTextureType_DISPLACEMENT)
        .value("LIGHTMAP", aiTextureType_LIGHTMAP)
        .value("REFLECTION", aiTextureType_REFLECTION)
        .value("UNKNOWN", aiTextureType_UNKNOWN)
        ;

    enum_<aiShadingMode>("aiShadingMode")
        .value("Flat", aiShadingMode_Flat)
        .value("Gouraud", aiShadingMode_Gouraud)
        .value("Phong", aiShadingMode_Phong)
        .value("Blinn", aiShadingMode_Blinn)
        .value("Toon", aiShadingMode_Toon)
        .value("OrenNayar", aiShadingMode_OrenNayar)
        .value("Minnaert", aiShadingMode_Minnaert)
        .value("CookTorrance", aiShadingMode_CookTorrance)
        .value("NoShading", aiShadingMode_NoShading)
        .value("Fresnel", aiShadingMode_Fresnel)
        ;

    enum_<aiTextureFlags>("aiTextureFlags")
        .value("Invert", aiTextureFlags_Invert)
        .value("UseAlpha", aiTextureFlags_UseAlpha)
        .value("IgnoreAlpha", aiTextureFlags_IgnoreAlpha)
        ;

    enum_<aiBlendMode>("aiBlendMode")
        .value("Default", aiBlendMode_Default)
        .value("Additive", aiBlendMode_Additive)
        ;

    class_<aiUVTransform>("aiUVTransform")
        .function("getTranslation", &aiUVTransformEmbind::getTranslation)
        .function("setTranslation", &aiUVTransformEmbind::setTranslation)
        .function("getScaling", &aiUVTransformEmbind::getScaling)
        .function("setScaling", &aiUVTransformEmbind::setScaling)
        .function("getRotation", &aiUVTransformEmbind::getRotation)
        .function("setRotation", &aiUVTransformEmbind::setRotation)
        ;

    enum_<aiPropertyTypeInfo>("aiPropertyTypeInfo")
        .value("Float", aiPTI_Float)
        .value("String", aiPTI_String)
        .value("Integer", aiPTI_Integer)
        .value("Buffer", aiPTI_Buffer)
        ;

    
    class_<aiMaterialProperty>("aiMaterialProperty")
        .constructor<>()
        .function("getKey", &aiMaterialPropertyEmbind::getKey)
        .function("setKey", &aiMaterialPropertyEmbind::setKey)
        .function("getSemantic", &aiMaterialPropertyEmbind::getSemantic)
        .function("setSemantic", &aiMaterialPropertyEmbind::setSemantic)
        .function("getIndex", &aiMaterialPropertyEmbind::getIndex)
        .function("setIndex", &aiMaterialPropertyEmbind::setIndex)
        .function("getDataLength", &aiMaterialPropertyEmbind::getDataLength)
        .function("setDataLength", &aiMaterialPropertyEmbind::setDataLength)
        .function("getType", &aiMaterialPropertyEmbind::getType)
        .function("setType", &aiMaterialPropertyEmbind::setType)
        .function("getData", &aiMaterialPropertyEmbind::getData, allow_raw_pointers())
        .function("setData", &aiMaterialPropertyEmbind::setData, allow_raw_pointers())
        ;
    
    class_<aiMaterial>("aiMaterial")
        .constructor<>()
        //.function("get", select_overload<aiReturn (const char*, unsigned int, unsigned int, int*, unsigned int*) const>(&aiMaterial::Get), allow_raw_pointers())
        //.function("get", select_overload<aiReturn (const char*, unsigned int, unsigned int, float*, unsigned int*) const>(&aiMaterial::Get), allow_raw_pointers())
        //.function("get", select_overload<aiReturn (const char*, unsigned int, unsigned int, int&) const>(&aiMaterial::Get), allow_raw_pointers())
        //.function("get", select_overload<aiReturn (const char*, unsigned int, unsigned int, float&) const>(&aiMaterial::Get), allow_raw_pointers())
        //.function("get", select_overload<aiReturn (const char*, unsigned int, unsigned int, aiString&) const>(&aiMaterial::Get), allow_raw_pointers())
        //.function("get", select_overload<aiReturn (const char*, unsigned int, unsigned int, aiColor3D&) const>(&aiMaterial::Get), allow_raw_pointers())
        //.function("get", select_overload<aiReturn (const char*, unsigned int, unsigned int, aiColor4D&) const>(&aiMaterial::Get), allow_raw_pointers())
        //.function("get", select_overload<aiReturn (const char*, unsigned int, unsigned int, aiUVTransform&) const>(&aiMaterial::Get), allow_raw_pointers())
        .function("getIntBuffer", &aiMaterialEmbind::getIntBuffer, allow_raw_pointers())
        .function("getFloatBuffer", &aiMaterialEmbind::getFloatBuffer, allow_raw_pointers())
        .function("getInt", &aiMaterialEmbind::getInt, allow_raw_pointers())
        .function("getFloat", &aiMaterialEmbind::getFloat, allow_raw_pointers())
        .function("getString", &aiMaterialEmbind::getString, allow_raw_pointers())
        .function("getColor3D", &aiMaterialEmbind::getColor3D, allow_raw_pointers())
        .function("getColor4D", &aiMaterialEmbind::getColor4D, allow_raw_pointers())
        .function("getUVTransform", &aiMaterialEmbind::getUVTransform, allow_raw_pointers())
        .function("getTextureCount", &aiMaterial::GetTextureCount)
        .function("getTexture", &aiMaterial::GetTexture, allow_raw_pointers())
        .function("addBinaryProperty", &aiMaterial::AddBinaryProperty, allow_raw_pointers())  
        //.function("addProperty", select_overload<aiReturn (const aiString*, const char*, unsigned int, unsigned int)>(&aiMaterial::AddProperty), allow_raw_pointers())
        //.function("addProperty", select_overload<aiReturn (const aiVector3D*, unsigned int, const char*, unsigned int, unsigned int)>(&aiMaterial::AddProperty), allow_raw_pointers())
        //.function("addProperty", select_overload<aiReturn (const aiColor3D*, unsigned int, const char*, unsigned int, unsigned int)>(&aiMaterial::AddProperty), allow_raw_pointers())
        //.function("addProperty", select_overload<aiReturn (const aiColor4D*, unsigned int, const char*, unsigned int, unsigned int)>(&aiMaterial::AddProperty), allow_raw_pointers())
        //.function("addProperty", select_overload<aiReturn (const int*, unsigned int, const char*, unsigned int, unsigned int)>(&aiMaterial::AddProperty), allow_raw_pointers())
        //.function("addProperty", select_overload<aiReturn (const float*, unsigned int, const char*, unsigned int, unsigned int)>(&aiMaterial::AddProperty), allow_raw_pointers())
        //.function("addProperty", select_overload<aiReturn (const aiUVTransform*, unsigned int, const char*, unsigned int, unsigned int)>(&aiMaterial::AddProperty), allow_raw_pointers())
        .function("addStringProperty", &aiMaterialEmbind::addStringProperty, allow_raw_pointers())
        .function("addVector3Property", &aiMaterialEmbind::addVector3Property, allow_raw_pointers())
        .function("addColor3DProperty", &aiMaterialEmbind::addColor3DProperty, allow_raw_pointers())
        .function("addColor4DProperty", &aiMaterialEmbind::addColor4DProperty, allow_raw_pointers())
        .function("addIntProperty", &aiMaterialEmbind::addIntProperty, allow_raw_pointers())
        .function("addFloatProperty", &aiMaterialEmbind::addFloatProperty, allow_raw_pointers())
        .function("addUVTransformProperty", &aiMaterialEmbind::addUVTransformProperty, allow_raw_pointers())
        .function("removeProperty", &aiMaterial::RemoveProperty, allow_raw_pointers())
        .function("clear", &aiMaterial::Clear)
        .class_function("copyPropertyList", &aiMaterial::CopyPropertyList, allow_raw_pointers())
        .function("getProperties", &aiMaterialEmbind::getProperties, allow_raw_pointers())
        .function("setProperties", &aiMaterialEmbind::setProperties, allow_raw_pointers())
        .function("getProperty", &aiMaterialEmbind::getProperty, allow_raw_pointers())
        .function("setProperty", &aiMaterialEmbind::setProperty, allow_raw_pointers())
        .function("getNumProperties", &aiMaterialEmbind::getNumProperties)
        .function("setNumProperties", &aiMaterialEmbind::setNumProperties)
        .function("getNumAllocated", &aiMaterialEmbind::getNumAllocated)
        .function("setNumAllocated", &aiMaterialEmbind::setNumAllocated)
        ;
    
    //function("aiGetMaterialProperty", &aiGetMaterialProperty, allow_raw_pointers());
    //function("aiGetMaterialFloatArray", &aiGetMaterialFloatArray, allow_raw_pointers());
    //function("aiGetMaterialFloat", &aiGetMaterialFloat, allow_raw_pointers());
    //function("aiGetMaterialIntegerArray", &aiGetMaterialIntegerArray, allow_raw_pointers());
    //function("aiGetMaterialInteger", &aiGetMaterialInteger, allow_raw_pointers());
    //function("aiGetMaterialColor", &aiGetMaterialColor, allow_raw_pointers());
    //function("aiGetMaterialUVTransform", &aiGetMaterialUVTransform, allow_raw_pointers());
    //function("aiGetMaterialString", &aiGetMaterialString, allow_raw_pointers());
    //function("aiGetMaterialTextureCount", &aiGetMaterialTextureCount, allow_raw_pointers());
    //function("aiGetMaterialTexture", &aiGetMaterialTexture, allow_raw_pointers());

} // end EMSCRIPTEN_BINDINGS

