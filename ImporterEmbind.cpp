
#include <emscripten/bind.h>
//#include "utilEmbind.h"
#include "assimp/Importer.hpp"

using namespace emscripten;
using namespace Assimp;


EMSCRIPTEN_BINDINGS(ASSIMP)
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
	    .function("readFile", select_overload<const aiScene *(const char*, unsigned int)>(&Importer::ReadFile), allow_raw_pointers())
	    .function("readFile", select_overload<const aiScene *(const std::string&, unsigned int)>(&Importer::ReadFile), allow_raw_pointers())
	    .function("readFileFromMemory", &Importer::ReadFileFromMemory, allow_raw_pointers())
	    .function("applyPostProcessing", &Importer::ApplyPostProcessing, allow_raw_pointers())
	    .function("freeScene", &Importer::FreeScene)
	    .function("getErrorString", &Importer::GetErrorString, allow_raw_pointers())
	    .function("getScene", &Importer::GetScene, allow_raw_pointers())
	    .function("getOrphanedScene", &Importer::GetOrphanedScene, allow_raw_pointers())
	    .function("isExtensionSupported", select_overload<bool (const char*) const>(&Importer::IsExtensionSupported), allow_raw_pointers())
	    .function("isExtensionSupported", select_overload<bool (const std::string&) const>(&Importer::IsExtensionSupported), allow_raw_pointers())
	    .function("getExtensionList", select_overload<void (aiString&) const>(&Importer::GetExtensionList), allow_raw_pointers())
	    .function("getExtensionList", &getExtensionList, allow_raw_pointers())
	    .function("getImporterCount", &Importer::GetImporterCount)
	    .function("getImporterInfo", &Importer::GetImporterInfo, allow_raw_pointers())
	    .function("getImporter", select_overload<BaseImporter *(size_t) const>(&Importer::GetImporter), allow_raw_pointers())
	    .function("getImporter", select_overload<BaseImporter* (const char*) const>(&Importer::GetImporter), allow_raw_pointers())
	    .function("getImporterIndex", &Importer::GetImporterIndex, allow_raw_pointers())
	    .function("getMemoryRequirements", &Importer::GetMemoryRequirements, allow_raw_pointers())
	    .function("setExtraVerbose", &Importer::SetExtraVerbose)
	    ;
} // end EMSCRIPTEN_BINDINGS
