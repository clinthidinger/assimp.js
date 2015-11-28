
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/mesh.h"

using namespace emscripten;


namespace aiFaceEmbind
{
	DefineGetterSetter(aiFace, unsigned int, mNumIndices, NumIndices)
	DefineArrayGetterSetter(aiFace, unsigned int, mIndices, Indices, aiFace.mNumIndices)
}

namespace aiVertexWeightEmbind
{
	DefineGetterSetter(aiVertexWeight, unsigned int, VertexId, mVertexId)
	DefineGetterSetter(aiVertexWeight, float, mWeight, Weight)
}

namespace aiBoneEmbind
{
	DefineGetterSetter(aiBone, aiString, mName, Name)
	DefineGetterSetter(aiBone, unsigned int, mNumWeights, NumWeights)
	DefineArrayGetterSetter(aiBone, aiVertexWeight, mWeights, Weights, aiBone.mNumWeights)
	DefineConstGetterSetter(aiBone, aiMatrix4x4, mOffsetMatrix, OffsetMatrix)
}

namespace aiMeshEmbind
{
	DefineGetterSetter(aiMesh, unsigned int, mPrimitiveTypes, PrimitiveTypes)
	DefineGetterSetter(aiMesh, unsigned int, mNumVertices, NumVertices)
	DefineGetterSetter(aiMesh, aiVector3D *, mVertices, Vertices)
	DefineGetterSetter(aiMesh, unsigned int, mNumNormals, NumNormals)
	DefineGetterSetter(aiMesh, aiVector3D *, mNormals, Normals)
	DefineGetterSetter(aiMesh, unsigned int, mNumTangents, NumTangents)
	DefineGetterSetter(aiMesh, aiVector3D *, mTangents, Tangents)
	DefineGetterSetter(aiMesh, unsigned int, mNumBitangents, NumBitangents)
	DefineGetterSetter(aiMesh, aiVector3D *, mBitangents, Bitangents)
	DefineGetterSetter(aiMesh, unsigned int, mNumColors, NumColors)
	DefineGetterSetter(aiMesh, aiVector4D *, mColors, Colors)
	DefineGetterSetter(aiMesh, unsigned int, mTextureCoords, NumTextureCoords)
	DefineGetterSetter(aiMesh, aiVector3D *, mTextureCoords, TextureCoords)
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
		.function("getVertexId", &aiFaceEmbind::getVertexId)
		.function("setVertexId", &aiFaceEmbind::setVertexId)
		.function("getWeight", &aiFaceEmbind::getWeight)
		.function("setWeight", &aiFaceEmbind::setWeight)
		;

	class_<aiBone>("aiBone")
		.constructor<>()
		.constructor<const aiBone&>()
		.function("getName", &aiFaceEmbind::getName)
		.function("setName", &aiFaceEmbind::setName)
		.function("getNumWeights", &aiFaceEmbind::getNumWeights)
		.function("setNumWeights", &aiFaceEmbind::setNumWeights)
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
	    .function("getColors[AI_MAX_NUMBER_OF_COLOR_SETS]", &aiMeshEmbind::getColors)
	    .function("getTextureCoords[AI_MAX_NUMBER_OF_TEXTURECOORDS]", &aiMeshEmbind::getTextureCoords)
	    .function("getNumUVComponents[AI_MAX_NUMBER_OF_TEXTURECOORDS]", &aiMeshEmbind::getNumUVComponents)
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
