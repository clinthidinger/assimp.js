
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/mesh.h"

using namespace emscripten;


namespace aiFaceEmbind
{
	DefineGetterSetter(aiFace, unsigned int, mNumIndices, NumIndices)
	DefineArrayGetterSetter(aiFace, unsigned int, mIndices, Indices, object.mNumIndices)
}

namespace aiVertexWeightEmbind
{
	DefineGetterSetter(aiVertexWeight, unsigned int, mVertexId, VertexId)
	DefineGetterSetter(aiVertexWeight, float, mWeight, Weight)
}

namespace aiBoneEmbind
{
	std::string getName(const aiBone &bone)
	{
		return std::string(bone.mName.C_Str());
	}
	void setName(aiBone &bone, const std::string &name)
	{
		bone.mName = aiString(name);
	}
	DefineGetterSetter(aiBone, unsigned int, mNumWeights, NumWeights)
	DefineArrayGetterSetter(aiBone, aiVertexWeight, mWeights, Weights, object.mNumWeights)
	DefineConstGetterSetter(aiBone, aiMatrix4x4, mOffsetMatrix, OffsetMatrix)
}

namespace aiMeshEmbind
{
	DefineGetterSetter(aiMesh, unsigned int, mPrimitiveTypes, PrimitiveTypes)
	DefineGetterSetter(aiMesh, unsigned int, mNumVertices, NumVertices)
	DefineGetterSetter(aiMesh, unsigned int, mNumFaces, NumFaces)
	DefineArrayGetterSetter(aiMesh, aiVector3D, mVertices, Vertices, object.mNumVertices)
	DefineArrayGetterSetter(aiMesh, aiVector3D, mNormals, Normals, object.mNumVertices)
	DefineArrayGetterSetter(aiMesh, aiVector3D, mTangents, Tangents, object.mNumVertices)
	DefineArrayGetterSetter(aiMesh, aiVector3D, mBitangents, Bitangents, object.mNumVertices)
	DefineArraySetGetterSetter(aiMesh, aiColor4D, mColors, Colors, object.mNumVertices, AI_MAX_NUMBER_OF_COLOR_SETS)
	unsigned int getNumUVComponents(const aiMesh &mesh, unsigned int setIndex)
	{
		return mesh.mNumUVComponents[setIndex];
	}
	void setNumUVComponents(aiMesh &mesh, unsigned int setIndex, unsigned int count)
	{
		mesh.mNumUVComponents[setIndex] = count;
	}

	DefineArraySetGetterSetter(aiMesh, aiVector3D, mTextureCoords, TextureCoords, object.mNumVertices, AI_MAX_NUMBER_OF_TEXTURECOORDS)

	DefineArrayGetterSetter(aiMesh, aiFace, mFaces, Faces, object.mNumFaces)
	DefineGetterSetter(aiMesh, unsigned int, mNumBones, NumBones)
	DefineArrayGetterSetter(aiMesh, aiBone, mBones, Bones, object.mNumBones)
	DefineGetterSetter(aiMesh, unsigned int, mMaterialIndex, MaterialIndex)
	DefineGetterSetter(aiMesh, unsigned int, mName, Name)
	std::string getName(const aiMesh &mesh)
	{
		return std::string(mesh.mName.C_Str());
	}
	void setName(aiMesh &mesh, const std::string &name)
	{
		mesh.mName = aiString(name);
	}
}

EMSCRIPTEN_BINDINGS(assimp_mesh)
{
	class_<aiFace>("aiFace")
		.constructor<>()
		.constructor<const aiFace&>()
		.function("getNumIndices", &aiFaceEmbind::getNumIndices)
		.function("setNumIndices", &aiFaceEmbind::setNumIndices)
		.function("getIndices", &aiFaceEmbind::getIndices)
		.function("setIndices", &aiFaceEmbind::setIndices)
		;

	class_<aiVertexWeight>("aiVertexWeight")
		.constructor<>()
		.constructor<unsigned int, float>()
		.function("getVertexId", &aiVertexWeightEmbind::getVertexId)
		.function("setVertexId", &aiVertexWeightEmbind::setVertexId)
		.function("getWeight", &aiVertexWeightEmbind::getWeight)
		.function("setWeight", &aiVertexWeightEmbind::setWeight)
		;

	class_<aiBone>("aiBone")
		.constructor<>()
		.constructor<const aiBone&>()
		.function("getName", &aiBoneEmbind::getName)
		.function("setName", &aiBoneEmbind::setName)
		.function("getNumWeights", &aiBoneEmbind::getNumWeights)
		.function("setNumWeights", &aiBoneEmbind::setNumWeights)
		;

	enum_<aiPrimitiveType>("aiPrimitiveType")
		.value("POINT", aiPrimitiveType_POINT)
		.value("LINE", aiPrimitiveType_LINE)
		.value("TRIANGLE", aiPrimitiveType_TRIANGLE)
		.value("POLYGON", aiPrimitiveType_POLYGON)
		;

	class_<aiMesh>("aiMesh")
		.constructor<>()
	    .function("getPrimitiveTypes", &aiMeshEmbind::getPrimitiveTypes)
	    .function("setPrimitiveTypes", &aiMeshEmbind::setPrimitiveTypes)
	    .function("getNumVertices", &aiMeshEmbind::getNumVertices)
	    .function("setNumVertices", &aiMeshEmbind::setNumVertices)
	    .function("getNumFaces", &aiMeshEmbind::getNumFaces)
	    .function("setNumFaces", &aiMeshEmbind::setNumFaces)
	    .function("getVertices", &aiMeshEmbind::getVertices)
	    .function("setVertices", &aiMeshEmbind::setVertices)
	    .function("getNormals", &aiMeshEmbind::getNormals)
	    .function("setNormals", &aiMeshEmbind::setNormals)
	    .function("getTangents", &aiMeshEmbind::getTangents)
	    .function("setTangents", &aiMeshEmbind::setTangents)
	    .function("getBitangents", &aiMeshEmbind::getBitangents)
	    .function("setBitangents", &aiMeshEmbind::setBitangents)
	    .function("getColors", &aiMeshEmbind::getColors)
	    .function("getTextureCoords", &aiMeshEmbind::getTextureCoords)
	    .function("getNumUVComponents", &aiMeshEmbind::getNumUVComponents)
	    .function("setNumUVComponents", &aiMeshEmbind::setNumUVComponents)
	    .function("getFaces", &aiMeshEmbind::getFaces)
	    .function("setFaces", &aiMeshEmbind::setFaces)
	    .function("getNumBones", &aiMeshEmbind::getNumBones)
	    .function("setNumBones", &aiMeshEmbind::setNumBones)
	    .function("getBones", &aiMeshEmbind::getBones)
	    .function("setBones", &aiMeshEmbind::setBones)
	    .function("getMaterialIndex", &aiMeshEmbind::getMaterialIndex)
	    .function("setMaterialIndex", &aiMeshEmbind::setMaterialIndex)
	    .function("getName", &aiMeshEmbind::getName)
	    .function("setName", &aiMeshEmbind::setName)
	    //.function("getNumAnimMeshes", &aiMeshEmbind::getNumAnimMeshes)
	    //.function("setNumAnimMeshes", &aiMeshEmbind::setNumAnimMeshes)
	    //.function("getAnimMeshes", &aiMeshEmbind::getAnimMeshes)
	    //.function("setAnimMeshes", &aiMeshEmbind::setAnimMeshes)
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
} // end EMSCRIPTEN_BINDINGS
