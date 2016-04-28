
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/mesh.h"

using namespace emscripten;


template<class ArrayType>
void allocateArray(ArrayType **array, size_t count, size_t &defaultCount)
{
	if(array == nullptr)
	{
		return;
	}
	if(count == 0)
	{
		count = defaultCount;
	}
	else
	{
		defaultCount = count;
	}
	
	if(*array != nullptr)
	{
		delete[] *array;	
	}	
	*array = new ArrayType[count];
}

namespace aiFaceEmbind
{
	DefineGetterSetter(aiFace, unsigned int, mNumIndices, NumIndices)
	DefineArrayIndexGetterSetter(aiFace, unsigned int, mIndices, Index)
	void allocateIndices(aiFace &face, size_t count = 0)
	{
		allocateArray<unsigned int>(&face.mIndices, count, face.mNumIndices);
	}
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
	DefineArrayIndexRefGetterSetter(aiBone, aiVertexWeight, mWeights, Weight)
	DefineConstGetterSetter(aiBone, aiMatrix4x4, mOffsetMatrix, OffsetMatrix)
	void allocateWeights(aiBone &bone, size_t count = 0)
	{
		allocateArray<aiVertexWeight>(&bone.mWeights, count, bone.mNumWeights);
	}
}

namespace aiMeshEmbind
{
	DefineGetterSetter(aiMesh, unsigned int, mPrimitiveTypes, PrimitiveTypes)
	DefineGetterSetter(aiMesh, unsigned int, mNumVertices, NumVertices)
	DefineGetterSetter(aiMesh, unsigned int, mNumFaces, NumFaces)
	//DefineArrayIndexRefGetterSetter(aiMesh, aiVector3D, mVertices, Vertex)
	//DefineArrayIndexRefGetterSetter(aiMesh, aiVector3D, mNormals, Normal)
	//DefineArrayIndexRefGetterSetter(aiMesh, aiVector3D, mTangents, Tangent)
	//DefineArrayIndexRefGetterSetter(aiMesh, aiVector3D, mBitangents, Bitangent)
	//DefineArrayIndexRefGetterSetter(aiMesh, aiFace, mFaces, Face)
	DefineArrayIndexRefGetter(aiMesh, aiVector3D, mVertices, Vertex)
	void setVertex(aiMesh &mesh, unsigned int index, float x, float y, float z)
	{
		mesh.mVertices[index].Set(x, y, z);
	}
	DefineArrayIndexRefGetter(aiMesh, aiVector3D, mNormals, Normal)
	void setNormal(aiMesh &mesh, unsigned int index, float x, float y, float z)
	{
		mesh.mNormals[index].Set(x, y, z);
	}
	DefineArrayIndexRefGetter(aiMesh, aiVector3D, mTangents, Tangent)
	DefineArrayIndexRefGetter(aiMesh, aiVector3D, mBitangents, Bitangent)
	DefineArrayIndexRefGetter(aiMesh, aiFace, mFaces, Face)
	
	DefineGetterSetter(aiMesh, unsigned int, mNumBones, NumBones)
	DefineArrayIndexGetterSetter(aiMesh, aiBone *, mBones, Bone)
	DefineGetterSetter(aiMesh, unsigned int, mMaterialIndex, MaterialIndex)
	std::string getName(const aiMesh &mesh)
	{
		return std::string(mesh.mName.C_Str());
	}
	void setName(aiMesh &mesh, const std::string &name)
	{
		mesh.mName = aiString(name);
	}
	unsigned int getNumUVComponents(const aiMesh &mesh, unsigned int setIndex)
	{
		return mesh.mNumUVComponents[setIndex];
	}
	void setNumUVComponents(aiMesh &mesh, unsigned int setIndex, unsigned int count)
	{
		mesh.mNumUVComponents[setIndex] = count;
	}
	const aiVector3D &getTextureCoord(const aiMesh &mesh, unsigned int uvSetIdx, unsigned int vertIdx)
	{
		return mesh.mTextureCoords[uvSetIdx][vertIdx];
	}
	void setTextureCoord(aiMesh &mesh, unsigned int uvSetIdx, unsigned int vertIdx, const aiVector3D &value)
	{
		mesh.mTextureCoords[uvSetIdx][vertIdx] = value;
	}
	const aiColor4D &getColor(const aiMesh &mesh, unsigned int colorSetIdx, unsigned int vertIdx)
	{
		return mesh.mColors[colorSetIdx][vertIdx];
	}
	void setColor(aiMesh &mesh, unsigned int colorSetIdx, unsigned int vertIdx, const aiColor4D &value)
	{
		mesh.mColors[colorSetIdx][vertIdx] = value;
	}
    void allocateVertices(aiMesh &mesh, size_t count = 0)
    {
		allocateArray<aiVector3D>(&mesh.mVertices, count, mesh.mNumVertices);
    }
    void allocateNormals(aiMesh &mesh, size_t count = 0)
    {
		allocateArray<aiVector3D>(&mesh.mNormals, count, mesh.mNumVertices);
    }
    void allocateTextureCoords(aiMesh &mesh, unsigned int setIndex, size_t count = 0)
    {
		allocateArray<aiVector3D>(&mesh.mTextureCoords[setIndex], count, mesh.mNumUVComponents[setIndex]);
    }
	void allocateVertexColors(aiMesh &mesh, unsigned int setIndex, size_t count = 0)
    {
		allocateArray<aiColor4D>(&mesh.mColors[setIndex], count, mesh.mNumVertices);
    }
	void allocateTangents(aiMesh &mesh, size_t count = 0)
    {
		allocateArray<aiVector3D>(&mesh.mTangents, count, mesh.mNumVertices);
    }
	void allocateBitangents(aiMesh &mesh, size_t count = 0)
    {
		allocateArray<aiVector3D>(&mesh.mBitangents, count, mesh.mNumVertices);
    }
	void allocateFaces(aiMesh &mesh, size_t count = 0)
    {
		allocateArray<aiFace>(&mesh.mFaces, count, mesh.mNumFaces);
    }
	void allocateTris(aiMesh &mesh, size_t count = 0)
    {
		allocateArray<aiFace>(&mesh.mFaces, count, mesh.mNumFaces);
		//for(unsigned int i; i < mesh.mNumFaces; ++i)
		//{
		//	aiFaceEmbind::allocateIndices(mesh.mFaces[i], 3);
		//}
    }
	void allocateBones(aiMesh &mesh, size_t count = 0)
    {
		allocateArray<aiBone *>(&mesh.mBones, count, mesh.mNumBones);
    }
}

EMSCRIPTEN_BINDINGS(assimp_mesh)
{
	class_<aiFace>("aiFace")
		.constructor<>()
		.constructor<const aiFace&>()
		.function("getNumIndices", &aiFaceEmbind::getNumIndices)
		.function("setNumIndices", &aiFaceEmbind::setNumIndices)
		.function("getIndex", &aiFaceEmbind::getIndex)
		.function("setIndex", &aiFaceEmbind::setIndex)
		.function("op_equals", &aiFace::operator=)
		.function("op_equal_to", &aiFace::operator==)
		.function("op_not_equal_to", &aiFace::operator!=)
		.function("allocateIndices", &aiFaceEmbind::allocateIndices)
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
		.function("allocateWeights", &aiBoneEmbind::allocateWeights)
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
	    .function("getVertex", &aiMeshEmbind::getVertex)
	    .function("setVertex", &aiMeshEmbind::setVertex)
	    .function("getNormal", &aiMeshEmbind::getNormal)
	    .function("setNormal", &aiMeshEmbind::setNormal)
	    .function("getTangent", &aiMeshEmbind::getTangent)
	    //.function("setTangent", &aiMeshEmbind::setTangent)
	    .function("getBitangent", &aiMeshEmbind::getBitangent)
	    //.function("setBitangent", &aiMeshEmbind::setBitangent)
	    .function("getColor", &aiMeshEmbind::getColor)
	    //.function("setColor", &aiMeshEmbind::setColor)
	    .function("getTextureCoord", &aiMeshEmbind::getTextureCoord)
	    //.function("setTextureCoord", &aiMeshEmbind::setTextureCoord)
	    //.function("getNumUVComponents", &aiMeshEmbind::getNumUVComponents)
	    //.function("setNumUVComponents", &aiMeshEmbind::setNumUVComponents)
	    .function("getFace", &aiMeshEmbind::getFace)
	    //.function("setFace", &aiMeshEmbind::setFace)
	    .function("getNumBones", &aiMeshEmbind::getNumBones)
	    .function("setNumBones", &aiMeshEmbind::setNumBones)
	    //!!!.function("getBone", &aiMeshEmbind::getBone)
	    //!!!.function("setBone", &aiMeshEmbind::setBone)
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
		.function("allocateVertices", &aiMeshEmbind::allocateVertices)
    	.function("allocateNormals", &aiMeshEmbind::allocateNormals)
    	.function("allocateTextureCoords", &aiMeshEmbind::allocateTextureCoords)
    	.function("allocateVertexColors", &aiMeshEmbind::allocateVertexColors)
    	.function("allocateTangents", &aiMeshEmbind::allocateTangents)
    	.function("allocateBitangents", &aiMeshEmbind::allocateBitangents)
		.function("allocateFaces", &aiMeshEmbind::allocateFaces)
		.function("allocateTris", &aiMeshEmbind::allocateTris)
	    ; 	
} // end EMSCRIPTEN_BINDINGS
