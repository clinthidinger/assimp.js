
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/scene.h"
#include "assimp/mesh.h"
#include <new>

using namespace emscripten;
//using namespace Assimp;

/*
const size_t Alignment = 16;

void* aligned_alloc(std::size_t size, std::size_t alignment){
    if(alignment < alignof(void*)) { 
        alignment = alignof(void*); 
    }
    std::size_t space = size + alignment - 1;
    void* allocated_mem = std::malloc(space + sizeof(void*));
    void* aligned_mem = static_cast<void*>(static_cast<char*>(allocated_mem) + sizeof(void*)); 
    ////////////// #1 ///////////////
    std::align(alignment, size, aligned_mem, space);
    ////////////// #2 ///////////////
    *(static_cast<void**>(aligned_mem) - 1) = allocated_mem;
    ////////////// #3 ///////////////
    return aligned_mem;
}

void aligned_free(void* p) noexcept {
    std::free(*(static_cast<void**>(p) - 1));
}

void *operator new(std::size_t n) throw(std::bad_alloc)
{
	//printf("clint allocate");
    //return aligned_alloc(16, n);

 	return aligned_alloc(n, Alignment);
}

void *operator new[](std::size_t n)
{
	//printf("clint allocate[]");
  //return ::operator new[](n);
	//return aligned_alloc(16, n);
	return aligned_alloc(n, Alignment);
}

void operator delete(void * p) throw()
{
  aligned_free(p);
}

void operator delete[](void * p)
{
  aligned_free(p);
}
*/

namespace aiNodeEmbind
{
	DefineGetter(aiNode, aiString &, mName, Name)
	DefineGetterSetter(aiNode, aiMatrix4x4 &, mTransformation, Transformation)
	DefineGetterSetter(aiNode, aiNode *, mParent, Parent)
	DefineGetterSetter(aiNode, unsigned int, mNumChildren, NumChildren)
	DefineArrayIndexGetterSetter(aiNode, aiNode *, mChildren, Child)
	DefineGetterSetter(aiNode, unsigned int, mNumMeshes, NumMeshes)
	DefineArrayGetterSetter(aiNode, unsigned int, mMeshes, Meshes, object.mNumMeshes)
	DefineArrayIndexGetterSetter(aiNode, unsigned int, mMeshes, MeshIndex)
	void setName(aiNode &node, const std::string &name)
	{
		node.mName = aiString(name);
	}
	void allocateChildren(aiNode &node, size_t count = 0)
    {
		allocateArray<aiNode *>(&node.mChildren, count, node.mNumChildren);
    }
    void allocateMeshIndices(aiNode &node, size_t count = 0)
    {
		allocateArray<unsigned int>(&node.mMeshes, count, node.mNumMeshes);
    }
	//unsigned int getMeshIndex(const aiNode &node, int index) { return node.mMeshes[index]; }
	//void setMeshIndex(const aiScene &node, int index, unsigned int i) { node.mMeshes[index] = i; }
}

namespace aiSceneEmbind
{
	DefineArrayGetterSetter(aiMesh, aiVector3D, mVertices, Vertices, object.mNumVertices)

	DefineGetterSetter(aiScene, unsigned int, mFlags, Flags)
	DefineGetterSetter(aiScene, aiNode *, mRootNode, RootNode)
	DefineGetterSetter(aiScene, unsigned int, mNumMeshes, NumMeshes)
	DefineArrayIndexGetterSetter(aiScene, aiMesh *, mMeshes, Mesh)
	DefineGetterSetter(aiScene, unsigned int, mNumMaterials, NumMaterials)
	DefineArrayIndexGetterSetter(aiScene, aiMaterial *, mMaterials, Material)
	DefineGetterSetter(aiScene, unsigned int, mNumAnimations, NumAnimations)
	DefineArrayIndexGetterSetter(aiScene, aiAnimation *, mAnimations, Animation)
	DefineGetterSetter(aiScene, unsigned int, mNumTextures, NumTextures)
	DefineArrayIndexGetterSetter(aiScene, aiTexture *, mTextures, Texture)
	DefineGetterSetter(aiScene, unsigned int, mNumLights, NumLights)
	DefineArrayIndexGetterSetter(aiScene, aiLight *, mLights, Light)
	DefineGetterSetter(aiScene, unsigned int, mNumCameras, NumCameras)
	DefineArrayIndexGetterSetter(aiScene, aiCamera *, mCameras, Camera)

	void allocateMeshes(aiScene &scene, size_t count = 0)
    {
		allocateArray<aiMesh *>(&scene.mMeshes, count, scene.mNumMeshes);
		memset(scene.mMeshes, 0, sizeof(aiMesh *) * count);
    }
    void allocateMaterials(aiScene &scene, size_t count = 0)
    {
		allocateArray<aiMaterial *>(&scene.mMaterials, count, scene.mNumMaterials);
		memset(scene.mMaterials, 0, sizeof(aiMaterial *) * count);
    }
    void allocateAnimations(aiScene &scene, size_t count = 0)
    {
		allocateArray<aiAnimation *>(&scene.mAnimations, count, scene.mNumAnimations);
		memset(scene.mAnimations, 0, sizeof(aiAnimation *) * count);
    }
    void allocateTextures(aiScene &scene, size_t count = 0)
    {
		allocateArray<aiTexture *>(&scene.mTextures, count, scene.mNumTextures);
		memset(scene.mTextures, 0, sizeof(aiTexture *) * count);
    }
    void allocateLights(aiScene &scene, size_t count = 0)
    {
		allocateArray<aiLight *>(&scene.mLights, count, scene.mNumLights);
		memset(scene.mLights, 0, sizeof(aiLight *) * count);
    }
    void allocateCameras(aiScene &scene, size_t count = 0)
    {
		allocateArray<aiCamera *>(&scene.mCameras, count, scene.mNumCameras);
		memset(scene.mCameras, 0, sizeof(aiCamera *) * count);
    }
	//aiMesh *getMesh(const aiScene &scene, int index) { return scene.mMeshes[index]; }
	//void setMesh(const aiScene &scene, int index, aiMesh *mesh) { scene.mMeshes[index] = mesh; }
	//aiMaterial *getMaterial(const aiScene &scene, int index) { return scene.mMaterials[index]; }
	//void setMaterial(const aiScene &scene, int index, aiMaterial *material) { scene.mMaterials[index] = material; }
	//aiAnimation *getAnimation(const aiScene &scene, int index) { return scene.mAnimations[index]; }
	//void setAnimation(const aiScene &scene, int index, aiAnimation *animation) { scene.mAnimations[index] = animation; }
	//aiTexture *getTexture(const aiScene &scene, int index) { return scene.mTextures[index]; }
	//void setTexture(const aiScene &scene, int index, aiTexture *texture) { scene.mTextures[index] = texture; }
	//aiLight *getLight(const aiScene &scene, int index) { return scene.mLights[index]; }
	//void setLight(const aiScene &scene, int index, aiLight *light) { scene.mLights[index] = light; }
	//aiCamera *getCamera(const aiScene &scene, int index) { return scene.mAnimations[index]; }
	//void setCamera(const aiScene &scene, int index, aiCamera *camera) { scene.mCameras[index] = camera; }
}

EMSCRIPTEN_BINDINGS(assimp_scene)
{
	class_<aiNode>("aiNode")
		.constructor<>()
    	.constructor<const std::string&>()
     	.function("findNode", select_overload<const aiNode*(const aiString&) const>(&aiNode::FindNode), allow_raw_pointers())
    	.function("findNode", select_overload<aiNode*(const aiString&)>(&aiNode::FindNode), allow_raw_pointers())
   		//.function("findNode", select_overload<const aiNode*(const char*) const>(&aiNode::FindNode), allow_raw_pointers())
  		//.function("findNode", select_overload<aiNode*(const char*)>(&aiNode::FindNode), allow_raw_pointers())
    	.function("getName", &aiNodeEmbind::getName)
		.function("setName", &aiNodeEmbind::setName)
		.function("getTransformation", &aiNodeEmbind::getTransformation)
		.function("setTransformation", &aiNodeEmbind::setTransformation)
		.function("getParent", &aiNodeEmbind::getParent, allow_raw_pointers())
		.function("setParent", &aiNodeEmbind::setParent, allow_raw_pointers())
		.function("getNumChildren", &aiNodeEmbind::getNumChildren)
		.function("setNumChildren", &aiNodeEmbind::setNumChildren)
		.function("getChild", &aiNodeEmbind::getChild, allow_raw_pointers())
		.function("setChild", &aiNodeEmbind::setChild, allow_raw_pointers())
		.function("getNumMeshes", &aiNodeEmbind::getNumMeshes)
		.function("setNumMeshes", &aiNodeEmbind::setNumMeshes)
		.function("getMeshIndex", &aiNodeEmbind::getMeshIndex, allow_raw_pointers())
		.function("setMeshIndex", &aiNodeEmbind::setMeshIndex, allow_raw_pointers())
		.function("allocateChildren", &aiNodeEmbind::allocateChildren)
		.function("allocateMeshIndices", &aiNodeEmbind::allocateMeshIndices)
		;

    class_<aiScene>("aiScene")
		.constructor<>()
	    .function("hasMeshes", &aiScene::HasMeshes)
	    .function("hasMaterials", &aiScene::HasMaterials)
	    .function("hasLights", &aiScene::HasLights)
	    .function("hasTextures", &aiScene::HasTextures)
	    .function("hasCameras", &aiScene::HasCameras)
	    .function("hasAnimations", &aiScene::HasAnimations)
	    .function("getFlags", &aiSceneEmbind::getFlags)
	    .function("setFlags", &aiSceneEmbind::setFlags)
	    .function("getRootNode", &aiSceneEmbind::getRootNode, allow_raw_pointers())
	    .function("setRootNode", &aiSceneEmbind::setRootNode, allow_raw_pointers())
	    .function("getNumMeshes", &aiSceneEmbind::getNumMeshes)
	    .function("setNumMeshes", &aiSceneEmbind::setNumMeshes)
	    .function("getMesh", &aiSceneEmbind::getMesh, allow_raw_pointers())
	    .function("setMesh", &aiSceneEmbind::setMesh, allow_raw_pointers())
	    .function("getNumMaterials", &aiSceneEmbind::getNumMaterials)
	    .function("setNumMaterials", &aiSceneEmbind::setNumMaterials)
	    .function("getMaterial", &aiSceneEmbind::getMaterial, allow_raw_pointers())
	    .function("setMaterial", &aiSceneEmbind::setMaterial, allow_raw_pointers())
	    .function("getNumAnimations", &aiSceneEmbind::getNumAnimations)
	    .function("setNumAnimations", &aiSceneEmbind::setNumAnimations)
	    .function("getAnimation", &aiSceneEmbind::getAnimation, allow_raw_pointers())
	    .function("setAnimation", &aiSceneEmbind::setAnimation, allow_raw_pointers())
	    .function("getNumTextures", &aiSceneEmbind::getNumTextures)
	    .function("setNumTextures", &aiSceneEmbind::setNumTextures)
	    .function("getTexture", &aiSceneEmbind::getTexture, allow_raw_pointers())
	    .function("setTexture", &aiSceneEmbind::setTexture, allow_raw_pointers())
	    .function("getNumLights", &aiSceneEmbind::getNumLights)
	    .function("setNumLights", &aiSceneEmbind::setNumLights)
	    .function("getLight", &aiSceneEmbind::getLight, allow_raw_pointers())
	    .function("setLight", &aiSceneEmbind::setLight, allow_raw_pointers())
	    .function("getNumCameras", &aiSceneEmbind::getNumCameras)
	    .function("setNumCameras", &aiSceneEmbind::setNumCameras)
	    .function("getCamera", &aiSceneEmbind::getCamera, allow_raw_pointers())
	    .function("setCamera", &aiSceneEmbind::setCamera, allow_raw_pointers())
	    .function("allocateMeshes", &aiSceneEmbind::allocateMeshes)
	    .function("allocateMaterials", &aiSceneEmbind::allocateMaterials)
	    .function("allocateAnimations", &aiSceneEmbind::allocateAnimations)
	    .function("allocateTextures", &aiSceneEmbind::allocateTextures)
	    .function("allocateLights", &aiSceneEmbind::allocateLights)
	    .function("allocateCameras", &aiSceneEmbind::allocateCameras)
	    ;
} // end EMSCRIPTEN_BINDINGS
