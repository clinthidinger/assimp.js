
#include <emscripten/bind.h>
//#include <string>
#include "assimp/Importer.hpp"	//OO version Header!
#include "assimp/Exporter.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
//#include "assimp/DefaultLogger.hpp"
//#include "assimp/LogStream.hpp"

//#include "assimp/color4.h"
//#include "assimp/camera.h"
//#include "assimp/anim.h"
//#include "assimp/light.h"
//#include "assimp/material.h"
//#include "assimp/matrix3x3.h"
//#include "assimp/matrix4x4.h"
//#include "assimp/mesh.h"
//#include "assimp/quaternion.h"
//#include "assimp/texture.h"
//#include "assimp/types.h"
//#include "assimp/vector2.h"
//#include "assimp/vector3.h"

/*

assimp/include/assimp/ai_assert.h	assimp/include/assimp/defs.h		assimp/include/assimp/postprocess.h
assimp/include/assimp/anim.h		assimp/include/assimp/importerdesc.h	assimp/include/assimp/quaternion.h
assimp/include/assimp/camera.h		assimp/include/assimp/light.h		assimp/include/assimp/scene.h
assimp/include/assimp/cexport.h		assimp/include/assimp/material.h	assimp/include/assimp/texture.h
assimp/include/assimp/cfileio.h		assimp/include/assimp/matrix3x3.h	assimp/include/assimp/types.h
assimp/include/assimp/cimport.h		assimp/include/assimp/matrix4x4.h	assimp/include/assimp/vector2.h
assimp/include/assimp/color4.h		assimp/include/assimp/mesh.h		assimp/include/assimp/vector3.h
assimp/include/assimp/config.h		assimp/include/assimp/metadata.h	assimp/include/assimp/version.h


*/


#define DefineGetter(ClassType, MemberType, MemberName, FuncName) 	MemberType get##FuncName(ClassType &object) { return object.MemberName; }
#define DefineSetter(ClassType, MemberType, MemberName, FuncName)	void set##FuncName(ClassType &object, MemberType value) { object.MemberName = value; }

#define DefineGetterSetter(ClassName, MemberType, MemberName, FuncName) \
	DefineGetter(ClassName, MemberType, MemberName, FuncName) \
	DefineSetter(ClassName, MemberType, MemberName, FuncName)


using namespace emscripten;
using namespace Assimp;

// Importer
void getExtensionList(Importer &importer, aiString &str) 
{
	importer.GetExtensionList(str);
}

// Exporter
namespace aiNode_ext
{
	DefineGetter(aiNode, aiString &, mName, Name)
	void setName(aiNode &node, const std::string &value)
	{
		node.mName = value;
	}
	DefineGetterSetter(aiNode, aiMatrix4x4 &, mTransformation, Transformation)
	DefineGetterSetter(aiNode, aiNode *, mParent, Parent)
	DefineGetterSetter(aiNode, unsigned int, mNumChildren, NumChildren)
	DefineGetterSetter(aiNode, aiNode **, mChildren, Children)
	DefineGetterSetter(aiNode, unsigned int, mNumMeshes, NumMeshes)
	DefineGetterSetter(aiNode, unsigned int *, mMeshes, Meshes)
}


EMSCRIPTEN_BINDINGS(ASSIMP)
{

	// aiReturn
	// BaseImporter
	// aiMatrix4x4
	// IOSystem
	// ProgessHandler
	// aiScene
	// aiImportDesc
	// aiString
	// aiMemoryInfo
	// IOSystem
	// aiExportDataBlob
	// aiReturn
	// aiExportFormatDesc
	// ExportFormatEntry
	// aiMesh
	// aiMaterial
	// aiAnimation
	// aiTexture
	// aiLight
	// aiCamera
	// aiVector3D
	// aiColor4D
	// aiFace
	// aiBone
	// aiAnimMesh
	class_<Importer>("Importer")
		.constructor<>()
		.constructor<const Importer &>()
    	.function("registerLoader", &Importer::RegisterLoader, allow_raw_pointers())
		.function("unregisterLoader", &Importer::UnregisterLoader, allow_raw_pointers())
		.function("registerPPStep", &Importer::RegisterPPStep, allow_raw_pointers())
		.function("unregisterPPStep", &Importer::UnregisterPPStep, allow_raw_pointers())
		.function("setPropertyInteger", &Importer::SetPropertyInteger, allow_raw_pointers())
		.function("setPropertyBool", &Importer::SetPropertyBool, allow_raw_pointers())
	    .function("setPropertyFloat", &Importer::SetPropertyFloat, allow_raw_pointers())
		.function("setPropertyString", &Importer::SetPropertyString, allow_raw_pointers())
		.function("setPropertyMatrix", &Importer::SetPropertyMatrix, allow_raw_pointers())
		.function("getPropertyInteger", &Importer::GetPropertyInteger, allow_raw_pointers())
	    .function("getPropertyBool", &Importer::GetPropertyBool, allow_raw_pointers())
	    .function("getPropertyFloat", &Importer::GetPropertyFloat, allow_raw_pointers())
	    .function("getPropertyString", &Importer::GetPropertyString, allow_raw_pointers())
	    .function("getPropertyMatrix", &Importer::GetPropertyMatrix, allow_raw_pointers())
	    .function("setIOHandler", &Importer::SetIOHandler, allow_raw_pointers())
	    .function("getIOHandler", &Importer::GetIOHandler, allow_raw_pointers())
	    .function("isDefaultIOHandler", &Importer::IsDefaultIOHandler)
	    .function("setProgressHandler", &Importer::SetProgressHandler, allow_raw_pointers())
	    .function("getProgressHandler", &Importer::GetProgressHandler, allow_raw_pointers())
	    .function("isDefaultProgressHandler", &Importer::IsDefaultProgressHandler)
	    .function("validateFlags", &Importer::ValidateFlags)
	    .function("readFile", select_overload<const aiScene *(const char*, unsigned int)>(&Importer::ReadFile), allow_raw_pointers())
	    .function("readFile", select_overload<const aiScene *(const std::string&, unsigned int)>(&Importer::ReadFile), allow_raw_pointers())
	    .function("readFileFromMemory", &Importer::ReadFileFromMemory, allow_raw_pointers())
	    .function("applyPostProcessing", &Importer::ApplyPostProcessing, allow_raw_pointers())
	    .function("freeScene", &Importer::FreeScene)
	    .function("getErrorString", &Importer::GetErrorString, allow_raw_pointers())
	    .function("getScene", &Importer::GetScene, allow_raw_pointers())
	    .function("getOrphanedScene", &Importer::GetOrphanedScene, allow_raw_pointers())
	    .function("isExtensionSupported", select_overload<bool (const char*) const>(&Importer::IsExtensionSupported), allow_raw_pointers())
	    .function("isExtensionSupported", select_overload<bool (const std::string&) const>(&Importer::IsExtensionSupported), allow_raw_pointers())
	    .function("getExtensionList", select_overload<void (aiString&) const>(&Importer::GetExtensionList), allow_raw_pointers())
	    .function("getExtensionList", &getExtensionList, allow_raw_pointers())
	    .function("getImporterCount", &Importer::GetImporterCount)
	    .function("getImporterInfo", &Importer::GetImporterInfo, allow_raw_pointers())
	    .function("getImporter", select_overload<BaseImporter *(size_t) const>(&Importer::GetImporter), allow_raw_pointers())
	    .function("getImporter", select_overload<BaseImporter* (const char*) const>(&Importer::GetImporter), allow_raw_pointers())
	    .function("getImporterIndex", &Importer::GetImporterIndex, allow_raw_pointers())
	    .function("getMemoryRequirements", &Importer::GetMemoryRequirements, allow_raw_pointers())
	    .function("setExtraVerbose", &Importer::SetExtraVerbose)
	    ;

	//value_object<Exporter::ExportFormatEntry>("Exporter_ExportFormatEntry")
    //	.field("mDescription", &Exporter::ExportFormatEntry::mDescription)
    //    .field("mExportFunction", &Exporter::ExportFormatEntry::mExportFunction)
    //    .field("mEnforcePP", &Exporter::ExportFormatEntry::mEnforcePP)
    //    ;

	class_<ExportProperties>("ExportProperties")
		.constructor<>()
		;    

	class_<Exporter>("Exporter")
		.constructor<>()
		.function("setIOHandler", &Exporter::SetIOHandler, allow_raw_pointers())
	    .function("getIOHandler", &Exporter::GetIOHandler, allow_raw_pointers())
		.function("isDefaultIOHandler", &Exporter::IsDefaultIOHandler)
    	//!!!.function("ExportToBlob", select_overload<aiExportDataBlob *(const aiScene*, const char*, unsigned int, const ExportProperties*)>(&Exporter::ExportToBlob), allow_raw_pointers())
    	//!!!.function("ExportToBlob", select_overload<aiExportDataBlob *(const aiScene*, const std::string&, unsigned int, const ExportProperties*)>(&Exporter::ExportToBlob), allow_raw_pointers())
		.function("export", select_overload<aiReturn(const aiScene*, const char*, const char*, unsigned int, const ExportProperties*)>(&Exporter::Export), allow_raw_pointers())
    	.function("export", select_overload<aiReturn(const aiScene*, const std::string&, const std::string&,  unsigned int, const ExportProperties*)>(&Exporter::Export), allow_raw_pointers())
		.function("getErrorString", &Exporter::GetErrorString, allow_raw_pointers())
	    .function("getBlob", &Exporter::GetBlob, allow_raw_pointers())
		.function("getOrphanedBlob", &Exporter::GetOrphanedBlob, allow_raw_pointers())
		.function("freeBlob", &Exporter::FreeBlob)
		.function("getExportFormatCount", &Exporter::GetExportFormatCount, allow_raw_pointers())
		.function("getExportFormatDescription", &Exporter::GetExportFormatDescription, allow_raw_pointers())
		.function("registerExporter", &Exporter::RegisterExporter)
		.function("unregisterExporter", &Exporter::UnregisterExporter, allow_raw_pointers())
		;

// Will need to wrap all properties!!!

	class_<aiNode>("aiNode")
    	//.property("mName", &aiNode::mName)
		.function("getName", &aiNode_ext::getName)
		.function("setName", &aiNode_ext::setName)
		.function("getTransformation", &aiNode_ext::getTransformation)
		.function("setTransformation", &aiNode_ext::setTransformation)
		.function("getParent", &aiNode_ext::getParent, allow_raw_pointers())
		.function("setParent", &aiNode_ext::setParent, allow_raw_pointers())
		.function("getNumChildren", &aiNode_ext::getNumChildren)
		.function("setNumChildren", &aiNode_ext::setNumChildren)
		//.function("getChildren", &aiNode_ext::getChildren, allow_raw_pointers())
		//.function("setChildren", &aiNode_ext::setChildren, allow_raw_pointers())
		.function("getNumMeshes", &aiNode_ext::getNumMeshes)
		.function("setNumMeshes", &aiNode_ext::setNumMeshes)
		.function("getMeshes", &aiNode_ext::getMeshes, allow_raw_pointers())
		.function("setMeshes", &aiNode_ext::setMeshes, allow_raw_pointers())

    	//.property("mTransformation", &aiNode::mTransformation)
    	//!!!.property("mParent", &aiNode::mParent)
    	//.property("mNumChildren", &aiNode::mNumChildren)
    	//.property("mChildren", &aiNode::mChildren)
    	//.property("mNumMeshes", &aiNode::mNumMeshes)
    	//.property("mMeshes", &aiNode::mMeshes, allow_raw_pointers())
    	.constructor<>()
    	.constructor<const std::string&>()
     	.function("findNode", select_overload<const aiNode*(const aiString&) const>(&aiNode::FindNode), allow_raw_pointers())
    	.function("findNode", select_overload<aiNode*(const aiString&)>(&aiNode::FindNode), allow_raw_pointers())
   		.function("findNode", select_overload<const aiNode*(const char*) const>(&aiNode::FindNode), allow_raw_pointers())
  		.function("findNode", select_overload<aiNode*(const char*)>(&aiNode::FindNode), allow_raw_pointers())
    	;

    class_<aiScene>("aiScene")
	    .property("mFlags", &aiScene::mFlags)
		//.property("mRootNode", &aiScene::mRootNode)
	    .property("mNumMeshes", &aiScene::mNumMeshes)
		//.property("mMeshes", &aiScene::mMeshes)
	    .property("mNumMaterials", &aiScene::mNumMaterials)
	    //.property("mMaterials", &aiScene::mMaterials)
		.property("mNumAnimations", &aiScene::mNumAnimations)
	    //.property("mAnimations", &aiScene::mAnimations)
		.property("mNumTextures", &aiScene::mNumTextures)
	    //.property("mTextures", &aiScene::mTextures)
		.property("mNumLights", &aiScene::mNumLights)
	    //.property("mLights", &aiScene::mLights)
		.property("mNumCameras", &aiScene::mNumCameras)
	    //.property("mCameras", &aiScene::mCameras)
		.constructor<>()
	    .function("hasMeshes", &aiScene::HasMeshes)
	    .function("hasMaterials", &aiScene::HasMaterials)
	    .function("hasLights", &aiScene::HasLights)
	    .function("hasTextures", &aiScene::HasTextures)
	    .function("hasCameras", &aiScene::HasCameras)
	    .function("hasAnimations", &aiScene::HasAnimations)
	    ;

	class_<aiMesh>("aiMesh")
	    .property("mPrimitiveTypes", &aiMesh::mPrimitiveTypes)
	    .property("mNumVertices", &aiMesh::mNumVertices)
	    .property("mNumFaces", &aiMesh::mNumFaces)
	    //.property("mVertices", &aiMesh::mVertices)
	    //.property("mNormals", &aiMesh::mNormals)
	    //.property("mTangents", &aiMesh::mTangents)
	    //.property("mBitangents", &aiMesh::mBitangents)
	    //.property("mColors[AI_MAX_NUMBER_OF_COLOR_SETS]", &aiMesh::mColors)
	    //.property("mTextureCoords[AI_MAX_NUMBER_OF_TEXTURECOORDS]", &aiMesh::mTextureCoords)
	    //.property("mNumUVComponents[AI_MAX_NUMBER_OF_TEXTURECOORDS]", &aiMesh::mNumUVComponents)
	    //.property("mFaces", &aiMesh::mFaces)
	    .property("mNumBones", &aiMesh::mNumBones)
	    //.property("mBones", &aiMesh::mBones)
	    .property("mMaterialIndex", &aiMesh::mMaterialIndex)
	    .property("mName", &aiMesh::mName)
	    .property("mNumAnimMeshes", &aiMesh::mNumAnimMeshes)
	    //.property("mAnimMeshes", &aiMesh::mAnimMeshes)
	    .constructor<>()
	    .function("hasPositions", &aiMesh::HasPositions)
	    .function("hasFaces", &aiMesh::HasFaces)
	    .function("hasNormals", &aiMesh::HasNormals)
	    .function("hasTangentsAndBitangents", &aiMesh::HasTangentsAndBitangents)
	    .function("hasVertexColors", &aiMesh::HasVertexColors)
	    .function("hasTextureCoords", &aiMesh::HasTextureCoords)
	    .function("getNumUVChannels", &aiMesh::GetNumUVChannels)
	    .function("getNumColorChannels", &aiMesh::GetNumColorChannels)
	    .function("hasBones", &aiMesh::HasBones)
	    ; 


	class_<aiColor4D>("aiColor2D")
		.constructor<aiColor4D>()
		.constructor<aiColor4D>(TReal, TReal, TReal, TReal)
    	.constructor<aiColor4D>(TReal)
    	.constructor<aiColor4D>(const aiColor4t&)
    	.function("op_plus_equals", &aiColor4D::operator+=)
    	.function("op_minus_equals", &aiColor4D::operator-=)
    	.function("op_mult_equals", &aiColor4D::operator*=)
    	.function("op_div_equals", &aiColor4D::operator/=)
    	.function("op_equal_to", &aiColor4D::operator==)
    	.function("op_not_equal_to", &aiColor4D::operator!=)
    	.function("op_less_than", &aiColor4D::operator<)
    	.function("at", select_overload<TReal(unsigned int)>(&aiColor4D::operator[]))
    	.function("at", select_overload<TReal &(unsigned int)>(&aiColor4D::operator[]))
    	.function("isBlack", &aiColor4D::IsBlack)
    	.function("getR", &getR)
    	.function("setR", &setR)
    	.function("getG", &getG)
    	.function("setG", &setG)
    	.function("getB", &getB)
    	.function("setB", &setB)
    	.function("set", &set)
    	;

    class_<aiVector2D>("aiVector2D")
		.constructor<aiVector2D>()
		.constructor<aiVector2D>(TReal, TReal)
    	.constructor<aiVector2D>(TReal)
    	.constructor<aiVector2D>(const aiVector2D&)
    	.function("op_plus_equals", &aiVector2D::operator+=)
    	.function("op_minus_equals", &aiVector2D::operator-=)
    	.function("op_mult_equals", &aiVector2D::operator*=)
    	.function("op_div_equals", &aiVector2D::operator/=)
    	.function("op_equal_to", &aiVector2D::operator==)
    	.function("op_not_equal_to", &aiVector2D::operator!=)
    	.function("at", select_overload<TReal(unsigned int)>(&aiVector2D::operator[]))
    	.function("at", select_overload<TReal &(unsigned int)>(&aiVector2D::operator[]))
    	.function("squareLength", &aiVector2D::SquareLength)
    	.function("length", &aiVector2D::Length)
    	.function("normalize", &aiVector2D::Normalize)
    	.function("equal", &aiVector2D::Equal)
    	.function("op_equals", &aiVector2D::operator=)
    	.function("symMul", &aiVector2D::SymMul)
    	.function("getX", &getX)
    	.function("setX", &setX)
    	.function("getY", &getY)
    	.function("setY", &setY)
    	.function("set", &set)
    	;

    class_<aiVector3D>("aiVector3D")
		.constructor<aiVector3D>()
		.constructor<aiVector3D>(TReal, TReal, TReal)
    	.constructor<aiVector3D>(TReal)
    	.constructor<aiVector3D>(const aiVector3D&)
    	.function("op_plus_equals", &aiVector3D::operator+=)
    	.function("op_minus_equals", &aiVector3D::operator-=)
    	.function("op_mult_equals", select_overload<aiVector3t &(TReal)>(&aiVector3D::operator*=))
    	.function("op_mult_equals", select_overload<aiVector3t &(const aiMatrix3x3t<TReal>&)>(&aiVector3D::operator*=))
    	.function("op_mult_equals", select_overload<aiVector3t &(const aiMatrix4x4t<TReal>&)>(&aiVector3D::operator*=))
    	.function("op_div_equals", &aiVector3D::operator/=)
    	.function("op_equal_to", &aiVector3D::operator==)
    	.function("op_not_equal_to", &aiVector3D::operator!=)
    	.function("op_less_than", &aiVector3D::operator<)
    	.function("at", select_overload<TReal(unsigned int)>(&aiVector3D::operator[]))
    	.function("at", select_overload<TReal &(unsigned int)>(&aiVector3D::operator[]))
    	.function("squareLength", &aiVector3D::SquareLength)
    	.function("length", &aiVector3D::Length)
    	.function("normalize", &aiVector3D::Normalize)
    	.function("equal", &aiVector3D::Equal)
    	.function("op_equals", &aiVector3D::operator=)
    	.function("symMul", &aiVector3D::SymMul)
    	.function("getX", &getX)
    	.function("setX", &setX)
    	.function("getY", &getY)
    	.function("setY", &setY)
    	.function("getY", &getZ)
    	.function("setY", &setZ)
    	.function("set", &set)
    	;	

    class_<aiMatrix3x3>("aiMatrix3x3")
		.constructor<aiMatrix3x3>()
		.constructor<aiMatrix3x3>(TReal, TReal, TReal, TReal, TReal, TReal, TReal, TReal, TReal)
    	.constructor<aiMatrix3x3>(TReal)
    	.constructor<aiMatrix3x3>(const aiMatrix3x3 &)
    	.constructor<aiMatrix3x3>(const aiMatrix4x4t &)
    	.function("op_mult_equals", &aiMatrix3x3::operator*=)
    	.function("op_mult", &aiMatrix3x3::operator*)
    	.function("op_mult_equals", select_overload<aiMatrix3x3 &(const aiMatrix3x3t<TReal>&)>(&aiMatrix3x3::operator*=))
    	.function("op_mult_equals", select_overload<aiMatrix3x3 &(const aiMatrix4x4t<TReal>&)>(&aiMatrix3x3::operator*=))
    	.function("op_equal_to", &aiMatrix3x3::operator==)
    	.function("op_not_equal_to", &aiMatrix3x3::operator!=)
    	.function("at", select_overload<TReal *(unsigned int)>(&aiMatrix3x3::operator[]), allow_raw_pointers())
    	.function("at", select_overload<const TReal *(unsigned int) const>(&aiMatrix3x3::operator[]), allow_raw_pointers())
    	.function("squareLength", &aiMatrix3x3::SquareLength)
    	.function("length", &aiMatrix3x3::Length)
    	.function("normalize", &aiMatrix3x3::Normalize)
    	.function("equal", &aiMatrix3x3::Equal)
    	.function("op_equals", &aiMatrix3x3::operator=)
    	.function("transpose", &aiMatrix3x3::Transpose)
    	.function("inverse", &aiMatrix3x3::Inverse)
    	.function("determinant", &aiMatrix3x3::Determinant)
    	.function("rotationZ", &aiMatrix3x3::RotationZ)
    	.function("rotation", &aiMatrix3x3::Rotation)
    	.function("translation", &aiMatrix3x3::Translation)
    	.function("fromToMatrix", &aiMatrix3x3::FromToMatrix)
    	.function("getA1", &getA1)
    	.function("setA1", &setA1)
    	.function("getA2", &getA2)
    	.function("setA2", &setA2)
    	.function("getA3", &getA3)
    	.function("setA3", &setA3)
    	.function("getB1", &getB1)
    	.function("setB1", &setB1)
    	.function("getB2", &getB2)
    	.function("setB2", &setB2)
    	.function("getB3", &getB3)
    	.function("setB3", &setB3)
    	.function("getC1", &getC1)
    	.function("setC1", &setC1)
    	.function("getC2", &getC2)
    	.function("setC2", &setC2)
    	.function("getC3", &getC3)
    	.function("setC3", &setC3)
    	;	

    class_<aiMatrix4x4>("aiMatrix4x4")
		.constructor<aiMatrix4x4>()
		.constructor<aiMatrix4x4>(TReal, TReal, TReal, TReal,  TReal, TReal, TReal, TReal,  TReal, TReal, TReal, TReal,  TReal, TReal, TReal, TReal)
    	.constructor<aiMatrix4x4>(TReal)
    	.constructor<aiMatrix4x4>(const aiMatrix3x3 &)
    	.constructor<aiMatrix4x4>(const aiMatrix4x4 &)
    	.constructor<aiMatrix4x4>(const aiVector3D& scaling, const aiQuaternionD& rotation, const aiVector3D& position)
    	.function("op_mult_equals", &aiMatrix4x4::operator*=)
    	.function("op_mult", &aiMatrix4x4::operator*)
    	.function("op_mult_equals", select_overload<aiMatrix4x4 &(const aiMatrix3x3t<TReal>&)>(&aiMatrix4x4::operator*=))
    	.function("op_mult_equals", select_overload<aiMatrix4x4 &(const aiMatrix4x4t<TReal>&)>(&aiMatrix4x4::operator*=))
    	.function("op_equal_to", &aiMatrix4x4::operator==)
    	.function("op_not_equal_to", &aiMatrix4x4::operator!=)
    	.function("at", select_overload<TReal *(unsigned int)>(&aiMatrix4x4::operator[]), allow_raw_pointers())
    	.function("at", select_overload<const TReal *(unsigned int) const>(&aiMatrix4x4::operator[]), allow_raw_pointers())
    	.function("squareLength", &aiMatrix4x4::SquareLength)
    	.function("length", &aiMatrix4x4::Length)
    	.function("normalize", &aiMatrix4x4::Normalize)
    	.function("equal", &aiMatrix4x4::Equal)
    	.function("op_equals", &aiMatrix4x4::operator=)
    	.function("Transpose", &aiMatrix4x4::Transpose)
    	.function("Inverse", &aiMatrix4x4::Inverse)
    	.function("Determinant", &aiMatrix4x4::Determinant)
    	.function("IsIdentity", &aiMatrix4x4::IsIdentity)
    	.function("Decompose", &aiMatrix4x4::Decompose)
    	.function("DecomposeNoScaling", &aiMatrix4x4::DecomposeNoScaling)
    	.function("FromEulerAnglesXYZ", select_overload<aiMatrix4x4t& (TReal, TReal, TReal)>(&aiMatrix4x4::FromEulerAnglesXYZ))
    	.function("FromEulerAnglesXYZ", select_overload<aiMatrix4x4t& (const aiVector3t<TReal> &)>(&aiMatrix4x4::FromEulerAnglesXYZ))
    	.function("RotationX", &aiMatrix4x4::RotationX)
    	.function("RotationY", &aiMatrix4x4::RotationY)
    	.function("RotationZ", &aiMatrix4x4::RotationZ)
    	.function("Rotation", &aiMatrix4x4::Rotation)
    	.function("Translation", &aiMatrix4x4::Translation)
    	.function("Scaling", &aiMatrix4x4::Scaling)
    	.function("FromToMatrix", &aiMatrix4x4::FromToMatrix)
    	.function("getA1", &getA1)
    	.function("setA1", &setA1)
    	.function("getA2", &getA2)
    	.function("setA2", &setA2)
    	.function("getA3", &getA3)
    	.function("setA3", &setA3)
    	.function("getB1", &getB1)
    	.function("setB1", &setB1)
    	.function("getB2", &getB2)
    	.function("setB2", &setB2)
    	.function("getB3", &getB3)
    	.function("setB3", &setB3)
    	.function("getC1", &getC1)
    	.function("setC1", &setC1)
    	.function("getC2", &getC2)
    	.function("setC2", &setC2)
    	.function("getC3", &getC3)
    	.function("setC3", &setC3)
    	;

     class_<aiQuaternion>("aiQuaternion")
		.constructor<aiQuaternion>()
		.constructor<aiQuaternion>(TReal, TReal, TReal, TReal)
    	.constructor<aiQuaternion>(const aiMatrix3x3t<TReal>&)
    	.constructor<aiQuaternion>(TReal, TReal, TReal)
    	.constructor<aiQuaternion>(aiVector3D, TReal)
    	.constructor<aiQuaternion>(aiVector3D)
    	.constructor<aiQuaternion>(const aiQuaternion&)
    	.function("op_mult", &aiQuaternion::operator*)
    	.function("op_equal_to", &aiQuaternion::operator==)
    	.function("op_not_equal_to", &aiQuaternion::operator!=)
    	//.function("at", select_overload<TReal(unsigned int)>(&aiQuaternion::operator[]))
    	//.function("at", select_overload<TReal &(unsigned int)>(&aiQuaternion::operator[]))
    	.function("rotate", &aiQuaternion::Rotate)
    	.function("conjugate", &aiQuaternion::Conjugate)
    	.function("normalize", &aiQuaternion::Normalize)
    	.function("equal", &aiQuaternion::Equal)
    	.function("op_equals", &aiQuaternion::operator=)
    	.class_function("interpolate", &aiQuaternion::Interpolate)
    	.function("getMatrix", &aiQuaternion::GetMatrix)
    	.function("getX", &getX)
    	.function("setX", &setX)
    	.function("getY", &getY)
    	.function("setY", &setY)
    	.function("getZ", &getZ)
    	.function("setZ", &setZ)
    	.function("getW", &getW)
    	.function("setW", &setW)
    	.function("set", &set)
    	;


    class_<aiTexture>("aiTexture")
    	.constructor<aiTexture>()
    	.function("getWidth", &getWidth)
    	.function("setWidth", &setWidth)
    	.function("getHeight", &getHeight)
    	.function("setHeight", &setHeight)
    	.function("getAchFormatHint", &getAchFormatHint)
    	.function("setAchFormatHint", &setAchFormatHint)
    	.function("at", &at, allow_raw_pointers())
    	.function("getData", &getData, allow_raw_pointers())
    	.function("setData", &setData, allow_raw_pointers())
    	.function("checkFormat", &aiTexture::CheckFormat)
    	;

   	class_<aiTexel>("aiTexel")
   		.function("op_equal_to", &aiTexel::operator==)
    	.function("op_not_equal_to", &aiTexel::operator!=)
    	.function("color_cast", &aiTexel::operator  aiColor4D)
    	.function("getB", &getB)
    	.function("setB", &setB)
    	.function("getG", &getG)
    	.function("setG", &setG)
    	.function("getR", &getR)
    	.function("setR", &setR)
    	.function("getA", &getA)
    	.function("setA", &setA)
    	.function("set", &set)
    	.function("at", &at)
   		;
	


   	enum_<aiLightSourceType>("aiLightSourceType")
        .value("UNDEFINED", aiLightSource_UNDEFINED)
        .value("DIRECTIONAL", aiLightSource_DIRECTIONAL)
        .value("POINT", aiLightSource_POINT)
        .value("SPOT", aiLightSource_SPOT)
        .value("AMBIENT", aiLightSource_AMBIENT)
        ;	

	class_<aiLight>("aiLight")
		.constructor<aiLight>()
		.function("getName", &getName)
		.function("setName", &setName)
		.function("getType", &getType)
		.function("setType", &setType)
		.function("getPosition", &getPosition)
		.function("setPosition", &setPosition)
		.function("getDirection", &getDirection)
		.function("setDirection", &setDirection)
		.function("getAttenuationConstant", &getAttenuationConstant)
		.function("setAttenuationConstant", &setAttenuationConstant)
		.function("getAttenuationQuadratic", &getAttenuationQuadratic)
		.function("setAttenuationQuadratic", &setAttenuationQuadratic)
		.function("getColorDiffuse", &getColorDiffuse)
		.function("setColorDiffuse", &setColorDiffuse)
		.function("getColorSpecular", &getColorSpecular)
		.function("setColorSpecular", &setColorSpecular)
		.function("getColorAmbient", &getColorAmbient)
		.function("setColorAmbient", &setColorAmbient)
		.function("getAngleInnerCone", &getAngleInnerCone)
		.function("setAngleInnerCone", &setAngleInnerCone)
		.function("getAngleOuterCone", &getAngleOuterCone)
		.function("setAngleOuterCone", &setAngleOuterCone)
		;

	class_<aiCamera>("aiCamera")
		.constructor<aiCamera>()
		.function("getCameraMatrix", &aiCamera::GetCameraMatrix)
		.function("getName", &getName)
		.function("setName", &setName)
		.function("getPosition", &getPosition)
		.function("setPosition", &setPosition)
		.function("getUp", &getUp)
		.function("setUp", &setUp)
		.function("getLookAt", &getLookAt)
		.function("setLookAt", &setLookAt)
		.function("getHorizontalFOV", &getHorizontalFOV)
		.function("setHorizontalFOV", &setHorizontalFOV)
		.function("getClipPlaneNear", &getClipPlaneNear)
		.function("setClipPlaneNear", &setClipPlaneNear)
		.function("getClipPlaneFar", &getClipPlaneFar)
		.function("setClipPlaneFar", &setClipPlaneFar)
		.function("getAspect", &getAspect)
		.function("setAspect", &setAspect)
		;

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



} // end EMSCRIPTEN_BINDINGS

