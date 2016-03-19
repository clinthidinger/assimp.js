
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/scene.h"
#include "assimp/mesh.h"

using namespace emscripten;
//using namespace Assimp;

namespace aiNodeEmbind
{
	DefineGetterSetter(aiNode, aiString &, mName, Name)
	DefineGetterSetter(aiNode, aiMatrix4x4 &, mTransformation, Transformation)
	DefineGetterSetter(aiNode, aiNode *, mParent, Parent)
	DefineGetterSetter(aiNode, unsigned int, mNumChildren, NumChildren)
	DefineArrayIndexGetterSetter(aiNode, aiNode *, mChildren, Child)
	DefineGetterSetter(aiNode, unsigned int, mNumMeshes, NumMeshes)
	DefineArrayGetterSetter(aiNode, unsigned int, mMeshes, Meshes, object.mNumMeshes)
	DefineArrayIndexGetterSetter(aiNode, unsigned int, mMeshes, MeshIndex)
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
	    ;
} // end EMSCRIPTEN_BINDINGS
