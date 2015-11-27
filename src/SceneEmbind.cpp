
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/scene.h"

using namespace emscripten;
//using namespace Assimp;

namespace aiNodeEmbind
{
	DefineGetterSetter(aiNode, aiString &, mName, Name)
	DefineGetterSetter(aiNode, aiMatrix4x4 &, mTransformation, Transformation)
	DefineGetterSetter(aiNode, aiNode *, mParent, Parent)
	DefineGetterSetter(aiNode, unsigned int, mNumChildren, NumChildren)
	DefineGetterSetter(aiNode, aiNode **, mChildren, Children)
	DefineGetterSetter(aiNode, unsigned int, mNumMeshes, NumMeshes)
	DefineGetterSetter(aiNode, unsigned int *, mMeshes, Meshes)
}

namespace aiSceneEmbind
{
	DefineGetterSetter(aiScene, unsigned int, mFlags, Flags)
	DefineGetterSetter(aiScene, aiNode *, mRootNode, RootNode)
	DefineGetterSetter(aiScene, unsigned int, mNumMeshes, NumMeshes)
	DefineGetterSetter(aiScene, aiMesh **, mMeshes, Meshes)
	DefineGetterSetter(aiScene, unsigned int, mNumMaterials, NumMaterials)
	DefineGetterSetter(aiScene, aiMaterial **, mMaterials, Materials)
	DefineGetterSetter(aiScene, unsigned int, mNumAnimations, NumAnimations)
	DefineGetterSetter(aiScene, aiAnimation **, mAnimations, Animations)
	DefineGetterSetter(aiScene, unsigned int, mNumTextures, NumTextures)
	DefineGetterSetter(aiScene, aiTexture **, mTextures, Textures)
	DefineGetterSetter(aiScene, unsigned int, mNumLights, NumLights)
	DefineGetterSetter(aiScene, aiLight **, mLights, Lights)
	DefineGetterSetter(aiScene, unsigned int, mNumCameras, NumCameras)
	DefineGetterSetter(aiScene, aiCamera **, mCameras, Cameras)
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
		.function("getChildren", &aiNodeEmbind::getChildren, allow_raw_pointers())
		.function("setChildren", &aiNodeEmbind::setChildren, allow_raw_pointers())
		.function("getNumMeshes", &aiNodeEmbind::getNumMeshes)
		.function("setNumMeshes", &aiNodeEmbind::setNumMeshes)
		.function("getMeshes", &aiNodeEmbind::getMeshes, allow_raw_pointers())
		.function("setMeshes", &aiNodeEmbind::setMeshes, allow_raw_pointers())
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
	    //.function("getMeshes", &aiSceneEmbind::getMeshes, allow_raw_pointers())
	    //.function("setMeshes", &aiSceneEmbind::setMeshes, allow_raw_pointers())
	    .function("getNumMaterials", &aiSceneEmbind::getNumMaterials)
	    .function("setNumMaterials", &aiSceneEmbind::setNumMaterials)
	    .function("getMaterials", &aiSceneEmbind::getMaterials, allow_raw_pointers())
	    .function("setMaterials", &aiSceneEmbind::setMaterials, allow_raw_pointers())
	    .function("getNumAnimations", &aiSceneEmbind::getNumAnimations)
	    .function("setNumAnimations", &aiSceneEmbind::setNumAnimations)
	    .function("getAnimations", &aiSceneEmbind::getAnimations, allow_raw_pointers())
	    .function("setAnimations", &aiSceneEmbind::setAnimations, allow_raw_pointers())
	    .function("getNumTextures", &aiSceneEmbind::getNumTextures)
	    .function("setNumTextures", &aiSceneEmbind::setNumTextures)
	    .function("getTextures", &aiSceneEmbind::getTextures, allow_raw_pointers())
	    .function("setTextures", &aiSceneEmbind::setTextures, allow_raw_pointers())
	    .function("getNumLights", &aiSceneEmbind::getNumLights)
	    .function("setNumLights", &aiSceneEmbind::setNumLights)
	    .function("getLights", &aiSceneEmbind::getLights, allow_raw_pointers())
	    .function("setLights", &aiSceneEmbind::setLights, allow_raw_pointers())
	    .function("getNumCameras", &aiSceneEmbind::getNumCameras)
	    .function("setNumCameras", &aiSceneEmbind::setNumCameras)
	    .function("getCameras", &aiSceneEmbind::getCameras, allow_raw_pointers())
	    .function("setCameras", &aiSceneEmbind::setCameras, allow_raw_pointers())
	    ;
} // end EMSCRIPTEN_BINDINGS
