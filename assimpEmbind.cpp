
#include <emscripten/bind.h>
//#include <string>
#include "assimp/Importer.hpp"	//OO version Header!
#include "assimp/Exporter.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
//#include "assimp/DefaultLogger.hpp"
//#include "assimp/LogStream.hpp"

using namespace emscripten;
using namespace Assimp;

EMSCRIPTEN_BINDINGS(assimp)
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
    	.function("RegisterLoader", &Importer::RegisterLoader, allow_raw_pointers())
		.function("UnregisterLoader", &Importer::UnregisterLoader, allow_raw_pointers())
		.function("RegisterPPStep", &Importer::RegisterPPStep, allow_raw_pointers())
		.function("UnregisterPPStep", &Importer::UnregisterPPStep, allow_raw_pointers())
		.function("SetPropertyInteger", &Importer::SetPropertyInteger, allow_raw_pointers())
		.function("SetPropertyBool", &Importer::SetPropertyBool, allow_raw_pointers())
	    .function("SetPropertyFloat", &Importer::SetPropertyFloat, allow_raw_pointers())
		.function("SetPropertyString", &Importer::SetPropertyString, allow_raw_pointers())
		.function("SetPropertyMatrix", &Importer::SetPropertyMatrix, allow_raw_pointers())
		.function("GetPropertyInteger", &Importer::GetPropertyInteger, allow_raw_pointers())
	    .function("GetPropertyBool", &Importer::GetPropertyBool, allow_raw_pointers())
	    .function("GetPropertyFloat", &Importer::GetPropertyFloat, allow_raw_pointers())
	    .function("GetPropertyString", &Importer::GetPropertyString, allow_raw_pointers())
	    .function("GetPropertyMatrix", &Importer::GetPropertyMatrix, allow_raw_pointers())
	    .function("SetIOHandler", &Importer::SetIOHandler, allow_raw_pointers())
	    .function("GetIOHandler", &Importer::GetIOHandler, allow_raw_pointers())
	    .function("IsDefaultIOHandler", &Importer::IsDefaultIOHandler)
	    .function("SetProgressHandler", &Importer::SetProgressHandler, allow_raw_pointers())
	    .function("GetProgressHandler", &Importer::GetProgressHandler, allow_raw_pointers())
	    .function("IsDefaultProgressHandler", &Importer::IsDefaultProgressHandler)
	    .function("ValidateFlags", &Importer::ValidateFlags)
	    .function("ReadFile", select_overload<const aiScene *(const char*, unsigned int)>(&Importer::ReadFile), allow_raw_pointers())
	    .function("ReadFile", select_overload<const aiScene *(const std::string&, unsigned int)>(&Importer::ReadFile), allow_raw_pointers())
	    .function("ReadFileFromMemory", &Importer::ReadFileFromMemory, allow_raw_pointers())
	    .function("ApplyPostProcessing", &Importer::ApplyPostProcessing, allow_raw_pointers())
	    .function("FreeScene", &Importer::FreeScene)
	    .function("GetErrorString", &Importer::GetErrorString, allow_raw_pointers())
	    .function("GetScene", &Importer::GetScene, allow_raw_pointers())
	    .function("GetOrphanedScene", &Importer::GetOrphanedScene, allow_raw_pointers())
	    .function("IsExtensionSupported", select_overload<bool (const char*) const>(&Importer::IsExtensionSupported), allow_raw_pointers())
	    .function("IsExtensionSupported", select_overload<bool (const std::string&) const>(&Importer::IsExtensionSupported), allow_raw_pointers())
	    .function("GetExtensionList", select_overload<void (aiString&) const>(&Importer::GetExtensionList), allow_raw_pointers())
	    // PROBABLY WRAP!!! .function("GetExtensionList", select_overload<void (std::string&) const>(&Importer::GetExtensionList), allow_raw_pointers())
	    .function("GetImporterCount", &Importer::GetImporterCount)
	    .function("GetImporterInfo", &Importer::GetImporterInfo, allow_raw_pointers())
	    .function("GetImporter", select_overload<BaseImporter *(size_t) const>(&Importer::GetImporter), allow_raw_pointers())
	    .function("GetImporter", select_overload<BaseImporter* (const char*) const>(&Importer::GetImporter), allow_raw_pointers())
	    .function("GetImporterIndex", &Importer::GetImporterIndex, allow_raw_pointers())
	    .function("GetMemoryRequirements", &Importer::GetMemoryRequirements, allow_raw_pointers())
	    .function("SetExtraVerbose", &Importer::SetExtraVerbose)
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
		.function("SetIOHandler", &Exporter::SetIOHandler, allow_raw_pointers())
	    .function("GetIOHandler", &Exporter::GetIOHandler, allow_raw_pointers())
		.function("IsDefaultIOHandler", &Exporter::IsDefaultIOHandler)
    	//!!!.function("ExportToBlob", select_overload<aiExportDataBlob *(const aiScene*, const char*, unsigned int, const ExportProperties*)>(&Exporter::ExportToBlob), allow_raw_pointers())
    	//!!!.function("ExportToBlob", select_overload<aiExportDataBlob *(const aiScene*, const std::string&, unsigned int, const ExportProperties*)>(&Exporter::ExportToBlob), allow_raw_pointers())
		.function("Export", select_overload<aiReturn(const aiScene*, const char*, const char*, unsigned int, const ExportProperties*)>(&Exporter::Export), allow_raw_pointers())
    	.function("Export", select_overload<aiReturn(const aiScene*, const std::string&, const std::string&,  unsigned int, const ExportProperties*)>(&Exporter::Export), allow_raw_pointers())
		.function("GetErrorString", &Exporter::GetErrorString, allow_raw_pointers())
	    .function("GetBlob", &Exporter::GetBlob, allow_raw_pointers())
		.function("GetOrphanedBlob", &Exporter::GetOrphanedBlob, allow_raw_pointers())
		.function("FreeBlob", &Exporter::FreeBlob)
		.function("GetExportFormatCount", &Exporter::GetExportFormatCount, allow_raw_pointers())
		.function("GetExportFormatDescription", &Exporter::GetExportFormatDescription, allow_raw_pointers())
		.function("RegisterExporter", &Exporter::RegisterExporter)
		.function("UnregisterExporter", &Exporter::UnregisterExporter, allow_raw_pointers())
		;

// Will need to wrap all properties!!!

	class_<aiNode>("aiNode")
    	.property("mName", &aiNode::mName)
    	.property("mTransformation", &aiNode::mTransformation)
    	//!!!.property("mParent", &aiNode::mParent)
    	.property("mNumChildren", &aiNode::mNumChildren)
    	//.property("mChildren", &aiNode::mChildren)
    	.property("mNumMeshes", &aiNode::mNumMeshes)
    	//.property("mMeshes", &aiNode::mMeshes, allow_raw_pointers())
    	.constructor<>()
    	.constructor<const std::string&>()
     	.function("FindNode", select_overload<const aiNode*(const aiString&) const>(&aiNode::FindNode), allow_raw_pointers())
    	.function("FindNode", select_overload<aiNode*(const aiString&)>(&aiNode::FindNode), allow_raw_pointers())
   		.function("FindNode", select_overload<const aiNode*(const char*) const>(&aiNode::FindNode), allow_raw_pointers())
  		.function("FindNode", select_overload<aiNode*(const char*)>(&aiNode::FindNode), allow_raw_pointers())
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
	    .function("HasMeshes", &aiScene::HasMeshes)
	    .function("HasMaterials", &aiScene::HasMaterials)
	    .function("HasLights", &aiScene::HasLights)
	    .function("HasTextures", &aiScene::HasTextures)
	    .function("HasCameras", &aiScene::HasCameras)
	    .function("HasAnimations", &aiScene::HasAnimations)
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
	    .function("HasPositions", &aiMesh::HasPositions)
	    .function("HasFaces", &aiMesh::HasFaces)
	    .function("HasNormals", &aiMesh::HasNormals)
	    .function("HasTangentsAndBitangents", &aiMesh::HasTangentsAndBitangents)
	    .function("HasVertexColors", &aiMesh::HasVertexColors)
	    .function("HasTextureCoords", &aiMesh::HasTextureCoords)
	    .function("GetNumUVChannels", &aiMesh::GetNumUVChannels)
	    .function("GetNumColorChannels", &aiMesh::GetNumColorChannels)
	    .function("HasBones", &aiMesh::HasBones)
	    ; 
} // end EMSCRIPTEN_BINDINGS

