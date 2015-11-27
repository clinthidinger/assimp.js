
#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/postprocess.h"
#include "assimp/Importer.hpp"
#include "assimp/cimport.h"
#include "assimp/scene.h"

using namespace emscripten;
using namespace Assimp;

namespace aiPropertyStoreEmbind
{
	DefineGetterSetter(aiPropertyStore, char, sentinel, Sentinel)
}

namespace ImporterEmbind
{
	aiString getExtensionList(const Importer &importer)
	{
		aiString szOut;
		importer.GetExtensionList(szOut);
		return szOut;
	}

	

	//const aiScene *readFile(Importer &importer, const std::string &pFile, unsigned int pFlags)
	//std::string readFile(Importer &importer, const std::string &pFile, unsigned int pFlags)
	//{
	//	const aiScene *scene = importer.ReadFile(pFile.c_str(), aiProcessPreset_TargetRealtime_Quality);//pFlags);
	//	return std::string(importer.GetErrorString());//(scene != nullptr);//new aiScene();
	//}
	//const aiScene *readFileFromMemory(Importer &importer, const std::string &fileData, unsigned int pFlags)
	aiScene *readFileFromMemory(Importer &importer, const std::string &fileData, unsigned int pFlags)
	{
		 const aiScene *scene = importer.ReadFileFromMemory(fileData.c_str(), fileData.size(), pFlags, "");
		 return const_cast<aiScene *>(scene); // const_cast unfortunately needed here.
		 //return 1;
	}
}

EMSCRIPTEN_BINDINGS(assimp_importer)
{
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
	    //.function("readFile", select_overload<const aiScene *(const char*, unsigned int)>(&Importer::ReadFile), allow_raw_pointers())
	    //.function("readFile", select_overload<const aiScene *(const std::string&, unsigned int)>(&Importer::ReadFile), allow_raw_pointers())
	    //.function("readFile", &ImporterEmbind::readFile, allow_raw_pointers())
	    .function("readFileFromMemory", &ImporterEmbind::readFileFromMemory, allow_raw_pointers())
	    .function("applyPostProcessing", &Importer::ApplyPostProcessing, allow_raw_pointers())
	    .function("freeScene", &Importer::FreeScene)
	    .function("getErrorString", &Importer::GetErrorString, allow_raw_pointers())
	    .function("getScene", &Importer::GetScene, allow_raw_pointers())
	    .function("getOrphanedScene", &Importer::GetOrphanedScene, allow_raw_pointers())
	    //.function("isExtensionSupported", select_overload<bool (const char*) const>(&Importer::IsExtensionSupported), allow_raw_pointers())
	    .function("isExtensionSupported", select_overload<bool (const std::string&) const>(&Importer::IsExtensionSupported), allow_raw_pointers())
	    .function("getExtensionList", select_overload<void (aiString&) const>(&Importer::GetExtensionList), allow_raw_pointers())
	    .function("getExtensionList", &ImporterEmbind::getExtensionList, allow_raw_pointers())
	    .function("getImporterCount", &Importer::GetImporterCount)
	    .function("getImporterInfo", &Importer::GetImporterInfo, allow_raw_pointers())
	    .function("getImporter", select_overload<BaseImporter *(size_t) const>(&Importer::GetImporter), allow_raw_pointers())
	    .function("getImporter", select_overload<BaseImporter* (const char*) const>(&Importer::GetImporter), allow_raw_pointers())
	    .function("getImporterIndex", &Importer::GetImporterIndex, allow_raw_pointers())
	    .function("getMemoryRequirements", &Importer::GetMemoryRequirements, allow_raw_pointers())
	    .function("setExtraVerbose", &Importer::SetExtraVerbose)
	    ;

	class_<aiLogStream>("aiLogStream")
		;

	class_<aiPropertyStore>("aiPropertyStore")
		.function("getSentinel", &aiPropertyStoreEmbind::getSentinel)
		.function("setSentinel", &aiPropertyStoreEmbind::setSentinel)
		;

	function("aiImportFile", &aiImportFile, allow_raw_pointers());
	function("aiImportFileEx", &aiImportFileEx, allow_raw_pointers());
	function("aiImportFileExWithProperties", &aiImportFileExWithProperties, allow_raw_pointers());
	function("aiImportFileFromMemory", &aiImportFileFromMemory, allow_raw_pointers());
	function("aiImportFileFromMemoryWithProperties", &aiImportFileFromMemoryWithProperties, allow_raw_pointers());
	function("aiApplyPostProcessing", &aiApplyPostProcessing, allow_raw_pointers());
	function("aiGetPredefinedLogStream", &aiGetPredefinedLogStream, allow_raw_pointers());
	function("aiAttachLogStream", &aiAttachLogStream, allow_raw_pointers());
	function("aiEnableVerboseLogging", &aiEnableVerboseLogging, allow_raw_pointers());
	function("aiDetachLogStream", &aiDetachLogStream, allow_raw_pointers());
	function("aiImpoaiDetachAllLogStreams", &aiDetachAllLogStreams, allow_raw_pointers());
	function("aiReleaseImport", &aiReleaseImport, allow_raw_pointers());
	function("aiGetErrorString", &aiGetErrorString, allow_raw_pointers());
	function("aiIsExtensionSupported", &aiIsExtensionSupported, allow_raw_pointers());
	function("aiGetMemoryRequirements", &aiGetMemoryRequirements, allow_raw_pointers());
	function("aiCreatePropertyStore", &aiCreatePropertyStore, allow_raw_pointers());
	function("aiReleasePropertyStore", &aiReleasePropertyStore, allow_raw_pointers());
	function("aiSetImportPropertyInteger", &aiSetImportPropertyInteger, allow_raw_pointers());
	function("aiSetImportPropertyFloat", &aiSetImportPropertyFloat, allow_raw_pointers());
	function("aiSetImportPropertyString", &aiSetImportPropertyString, allow_raw_pointers());
	function("aiSetImportPropertyMatrix", &aiSetImportPropertyMatrix, allow_raw_pointers());
	function("aiCreateQuaternionFromMatrix", &aiCreateQuaternionFromMatrix, allow_raw_pointers());
	function("aiDecomposeMatrix", &aiDecomposeMatrix, allow_raw_pointers());
	function("aiTransposeMatrix4", &aiTransposeMatrix4, allow_raw_pointers());
	function("aiTransposeMatrix3", &aiTransposeMatrix3, allow_raw_pointers());
	function("aiTransformVecByMatrix3", &aiTransformVecByMatrix3, allow_raw_pointers());
	function("aiTransformVecByMatrix4", &aiTransformVecByMatrix4, allow_raw_pointers());
	function("aiMultiplyMatrix4", &aiMultiplyMatrix4, allow_raw_pointers());
	function("aiMultiplyMatrix3", &aiMultiplyMatrix3, allow_raw_pointers());
	function("aiIdentityMatrix3", &aiIdentityMatrix3, allow_raw_pointers());
	function("aiIdentityMatrix4", &aiIdentityMatrix4, allow_raw_pointers());
	function("aiGetImportFormatCount", &aiGetImportFormatCount, allow_raw_pointers());
	function("aiGetImportFormatDescription", &aiGetImportFormatDescription, allow_raw_pointers());
} // end EMSCRIPTEN_BINDINGS
