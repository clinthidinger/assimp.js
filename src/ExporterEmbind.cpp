
#include <emscripten/bind.h>
#include <algorithm>
#include <string>
#include "utilEmbind.h"
#include "assimp/Exporter.hpp"
#include "assimp/scene.h"

using namespace emscripten;
using namespace Assimp;


namespace aiExportFormatDescEmbind
{
	DefineGetterSetter(aiExportFormatDesc, const char*, id, Id)
	DefineGetterSetter(aiExportFormatDesc, const char*, description, Description)
	DefineGetterSetter(aiExportFormatDesc, const char*, fileExtension, FileExtension)
}

namespace aiExportDataBlobEmbind
{
	DefineGetterSetter(aiExportDataBlob, size_t, size, Size)
	DefineGetterSetter(aiExportDataBlob, void*, data, Data)
	DefineGetterSetter(aiExportDataBlob, aiString, name, Name)
	DefineGetterSetter(aiExportDataBlob, aiExportDataBlob *, next, Next)
}

namespace ExporterEmbind
{
	template<typename T>
	bool exportTo(Exporter &exporter, const aiScene *scene, const std::string &formatId, const ExportProperties *properties, T &outBuffer)
	{
		const aiExportDataBlob *blob = exporter.ExportToBlob(scene, formatId.c_str(), 0, properties);
		if(blob == nullptr)
		{
			return false;
		}
		
		const char *data = reinterpret_cast<char *>(blob->data);
		if(data == nullptr)
		{
			return false;
		}

		outBuffer.resize(blob->size);
		std::copy(data, data + blob->size, outBuffer.begin());
		// @note blob->next may point to extra files (i.e. material files).

		return true;
	}

	std::string exportToString(Exporter &exporter, const aiScene *scene, const std::string &formatId, const ExportProperties *properties)
	{
		std::string outStr;
		exportTo<std::string>(exporter, scene, formatId, properties, outStr);
		//exportTo<std::string>(exporter, scene, "dae", nullptr, outStr);
		return outStr;
	}

	bool exportToVector(Exporter &exporter, const aiScene *scene, const std::string &formatId, const ExportProperties *properties, std::vector<unsigned char> &outVec)
	{
		return exportTo<std::vector<unsigned char>>(exporter, scene, formatId, properties, outVec);
	}
}

EMSCRIPTEN_BINDINGS(ASSIMP)
{
	class_<aiExportFormatDesc>("aiExportFormatDesc")
		.function("getId", &aiExportFormatDescEmbind::getId, allow_raw_pointers())
		.function("setId", &aiExportFormatDescEmbind::setId, allow_raw_pointers())
		.function("getDescription", &aiExportFormatDescEmbind::getDescription, allow_raw_pointers())
		.function("setDescription", &aiExportFormatDescEmbind::setDescription, allow_raw_pointers())
		.function("getFileExtension", &aiExportFormatDescEmbind::getFileExtension, allow_raw_pointers())
		.function("setFileExtension", &aiExportFormatDescEmbind::setFileExtension, allow_raw_pointers())
		;

	class_<aiExportDataBlob>("aiExportDataBlob")
		.constructor<>()
		.function("getSize", &aiExportDataBlobEmbind::getSize)
		.function("setSize", &aiExportDataBlobEmbind::setSize)
		.function("getData", &aiExportDataBlobEmbind::getData, allow_raw_pointers())
		.function("setData", &aiExportDataBlobEmbind::setData, allow_raw_pointers())
		.function("getName", &aiExportDataBlobEmbind::getName)
		.function("setName", &aiExportDataBlobEmbind::setName)
		.function("getNext", &aiExportDataBlobEmbind::getNext, allow_raw_pointers())
		.function("setNext", &aiExportDataBlobEmbind::setNext, allow_raw_pointers())
		;

	class_<ExportProperties>("ExportProperties")
		.constructor<>()
		.constructor<const ExportProperties&>()
		.function("setPropertyInteger", &ExportProperties::SetPropertyInteger, allow_raw_pointers())
		.function("setPropertyBool", &ExportProperties::SetPropertyBool, allow_raw_pointers())
		.function("setPropertyFloat", &ExportProperties::SetPropertyFloat, allow_raw_pointers())
		.function("setPropertyString", &ExportProperties::SetPropertyString, allow_raw_pointers())
		.function("setPropertyMatrix", &ExportProperties::SetPropertyMatrix, allow_raw_pointers())
		.function("getPropertyInteger", &ExportProperties::GetPropertyInteger, allow_raw_pointers())
		.function("getPropertyBool", &ExportProperties::GetPropertyBool, allow_raw_pointers())
		.function("getPropertyFloat", &ExportProperties::GetPropertyFloat, allow_raw_pointers())
		.function("getPropertyString", &ExportProperties::GetPropertyString, allow_raw_pointers())
		.function("getPropertyMatrix", &ExportProperties::GetPropertyMatrix, allow_raw_pointers())
		.function("hasPropertyInteger", &ExportProperties::HasPropertyInteger, allow_raw_pointers())
		.function("hasPropertyBool", &ExportProperties::HasPropertyBool, allow_raw_pointers())
		.function("hasPropertyFloat", &ExportProperties::HasPropertyFloat, allow_raw_pointers())
		.function("hasPropertyString", &ExportProperties::HasPropertyString, allow_raw_pointers())
		.function("hasPropertyMatrix", &ExportProperties::HasPropertyMatrix, allow_raw_pointers())
		;    

	class_<Exporter>("Exporter")
		.constructor<>()
		//.function("setIOHandler", &Exporter::SetIOHandler, allow_raw_pointers())
	    //.function("getIOHandler", &Exporter::GetIOHandler, allow_raw_pointers())
		.function("isDefaultIOHandler", &Exporter::IsDefaultIOHandler)
    	//.function("exportToBlob", select_overload<const aiExportDataBlob *(const aiScene*, const char*, unsigned int, const ExportProperties*)>(&Exporter::ExportToBlob), allow_raw_pointers())
    	.function("exportToBlob", select_overload<const aiExportDataBlob *(const aiScene*, const std::string&, unsigned int, const ExportProperties*)>(&Exporter::ExportToBlob), allow_raw_pointers())
		//.function("export", select_overload<aiReturn(const aiScene*, const char*, const char*, unsigned int, const ExportProperties*)>(&Exporter::Export), allow_raw_pointers())
    	//.function("export", select_overload<aiReturn(const aiScene*, const std::string&, const std::string&,  unsigned int, const ExportProperties*)>(&Exporter::Export), allow_raw_pointers())
    	.function("exportToString", &ExporterEmbind::exportToString, allow_raw_pointers())
    	.function("exportToVector", &ExporterEmbind::exportToVector, allow_raw_pointers())
		.function("getErrorString", &Exporter::GetErrorString, allow_raw_pointers())
	    .function("getBlob", &Exporter::GetBlob, allow_raw_pointers())
		.function("getOrphanedBlob", &Exporter::GetOrphanedBlob, allow_raw_pointers())
		.function("freeBlob", &Exporter::FreeBlob)
		.function("getExportFormatCount", &Exporter::GetExportFormatCount, allow_raw_pointers())
		.function("getExportFormatDescription", &Exporter::GetExportFormatDescription, allow_raw_pointers())
		.function("registerExporter", &Exporter::RegisterExporter)
		.function("unregisterExporter", &Exporter::UnregisterExporter, allow_raw_pointers())
		;

	function("aiGetExportFormatCount", &aiGetExportFormatCount, allow_raw_pointers());
	function("aiGetExportFormatDescription", &aiGetExportFormatDescription, allow_raw_pointers());
	function("aiCopyScene", &aiCopyScene, allow_raw_pointers());
	function("aiFreeScene", &aiFreeScene, allow_raw_pointers());
	function("aiExportScene", &aiExportScene, allow_raw_pointers());
	function("aiExportSceneEx", &aiExportSceneEx, allow_raw_pointers());
	function("aiExportSceneToBlob", &aiExportSceneToBlob, allow_raw_pointers());
	function("aiReleaseExportBlob", &aiReleaseExportBlob, allow_raw_pointers());
	
} // end EMSCRIPTEN_BINDINGS
