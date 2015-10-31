
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/mesh.h"

using namespace emscripten;
using namespace Assimp;


EMSCRIPTEN_BINDINGS(ASSIMP)
{
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
} // end EMSCRIPTEN_BINDINGS
