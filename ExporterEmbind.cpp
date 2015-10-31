
#include <emscripten/bind.h>
//#include "utilEmbind.h"
#include "assimp/Exporter.hpp"

using namespace emscripten;
using namespace Assimp;


EMSCRIPTEN_BINDINGS(ASSIMP)
{
	class_<ExportProperties>("ExportProperties")
		.constructor<>()
		;    

	class_<Exporter>("Exporter")
		.constructor<>()
		.function("setIOHandler", &Exporter::SetIOHandler, allow_raw_pointers())
	    .function("getIOHandler", &Exporter::GetIOHandler, allow_raw_pointers())
		.function("isDefaultIOHandler", &Exporter::IsDefaultIOHandler)
    	//!!!.function("ExportToBlob", select_overload<aiExportDataBlob *(const aiScene*, const char*, unsigned int, const ExportProperties*)>(&Exporter::ExportToBlob), allow_raw_pointers())
    	//!!!.function("ExportToBlob", select_overload<aiExportDataBlob *(const aiScene*, const std::string&, unsigned int, const ExportProperties*)>(&Exporter::ExportToBlob), allow_raw_pointers())
		.function("export", select_overload<aiReturn(const aiScene*, const char*, const char*, unsigned int, const ExportProperties*)>(&Exporter::Export), allow_raw_pointers())
    	.function("export", select_overload<aiReturn(const aiScene*, const std::string&, const std::string&,  unsigned int, const ExportProperties*)>(&Exporter::Export), allow_raw_pointers())
		.function("getErrorString", &Exporter::GetErrorString, allow_raw_pointers())
	    .function("getBlob", &Exporter::GetBlob, allow_raw_pointers())
		.function("getOrphanedBlob", &Exporter::GetOrphanedBlob, allow_raw_pointers())
		.function("freeBlob", &Exporter::FreeBlob)
		.function("getExportFormatCount", &Exporter::GetExportFormatCount, allow_raw_pointers())
		.function("getExportFormatDescription", &Exporter::GetExportFormatDescription, allow_raw_pointers())
		.function("registerExporter", &Exporter::RegisterExporter)
		.function("unregisterExporter", &Exporter::UnregisterExporter, allow_raw_pointers())
		;
} // end EMSCRIPTEN_BINDINGS
