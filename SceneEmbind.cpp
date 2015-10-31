
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/scene.h"

using namespace emscripten;
using namespace Assimp;


EMSCRIPTEN_BINDINGS(ASSIMP)
{
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
} // end EMSCRIPTEN_BINDINGS
