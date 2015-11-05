#include <emscripten/bind.h>
#include "UtilEmbind.h"
#include "assimp/postprocess.h"


namespace aiPostProcessEmbind
{
	int GetConvertToLeftHandedFlags()
	{
		return aiProcess_ConvertToLeftHanded;
	}
	int GetTargetRealtimeFastFlags()
	{
		return aiProcessPreset_TargetRealtime_Fast;
	}
	int GetTargetRealtimeQualityFlags()
	{
		return aiProcessPreset_TargetRealtime_Quality;
	}
	int GetTargetRealtimeMaxQualityFlags()
	{
		return aiProcessPreset_TargetRealtime_MaxQuality;
	}
}

EMSCRIPTEN_BINDINGS(assimp_postprocess)
{
	  enum_<aiPostProcessSteps>("aiPostProcessSteps")
        .value("CalcTangentSpace", aiProcess_CalcTangentSpace)
        .value("JoinIdenticalVertices", aiProcess_JoinIdenticalVertices)
        .value("MakeLeftHanded", aiProcess_MakeLeftHanded)
        .value("Triangulate", aiProcess_Triangulate)
        .value("RemoveComponent", aiProcess_RemoveComponent)
        .value("GenNormals", aiProcess_GenNormals)
        .value("GenSmoothNormals", aiProcess_GenSmoothNormals)
        .value("SplitLargeMeshes", aiProcess_SplitLargeMeshes)
        .value("PreTransformVertices", aiProcess_PreTransformVertices)
        .value("ValidateDataStructure", aiProcess_ValidateDataStructure)
        .value("ImproveCacheLocality", aiProcess_ImproveCacheLocality)
        .value("RemoveRedundantMaterials", aiProcess_RemoveRedundantMaterials)
        .value("FixInfacingNormals", aiProcess_FixInfacingNormals)
        .value("SortByPType", aiProcess_SortByPType)
        .value("FindDegenerates", aiProcess_FindDegenerates)
        .value("FindInvalidData", aiProcess_FindInvalidData)
        .value("GenUVCoords", aiProcess_GenUVCoords)
        .value("TransformUVCoords", aiProcess_TransformUVCoords)
        .value("FindInstances", aiProcess_FindInstances)
        .value("OptimizeMeshes", aiProcess_OptimizeMeshes)
        .value("OptimizeGraph", aiProcess_OptimizeGraph)
        .value("FlipUVs", aiProcess_FlipUVs)
        .value("FlipWindingOrder", aiProcess_FlipWindingOrder)
        .value("SplitByBoneCount", aiProcess_SplitByBoneCount)
        .value("Debone", aiProcess_Debone)
        ;

    function("GetConvertToLeftHandedFlags", &aiPostProcessEmbind::GetConvertToLeftHandedFlags)
    function("GetTargetRealtimeFastFlags", &aiPostProcessEmbind::GetTargetRealtimeFastFlags)
    function("GetTargetRealtimeQualityFlags", &aiPostProcessEmbind::GetTargetRealtimeQualityFlags)
    function("GetTargetRealtimeMaxQualityFlags", &aiPostProcessEmbind::GetTargetRealtimeMaxQualityFlags)
}