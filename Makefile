EMCC=emcc
IFLAGS=-I. -Iassimp/include -Iassimp/code -Iassimp/code/BoostWorkaround -Iassimp/contrib \
           -Iassimp/contrib/openddlparser/include -Iassimp/contrib/clipper -Iassimp/contrib/ConvertUTF \
           -Iassimp/contrib/irrXML -Iassimp/contrib/poly2tri/poly2tri -Iassimp/contrib/unzip -Iasismp/contrib/zlib \
           -Iinclude
# NOTE: "-s SAFE_HEAP=1" is breaking things.  It would be nice to use it for debug builds.

EFLAGS=--bind --memory-init-file 0 -s EXPORT_NAME="'ASSIMP'" -s TOTAL_MEMORY=64MB -s MODULARIZE=1
debug: EFLAGS += -s WARN_ON_UNDEFINED_SYMBOLS=1 -s VERBOSE=1  -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=1 -g4 --js-opts 0
assimp.js: EFLAGS += -s ASM_JS=1 -s NO_EXIT_RUNTIME=1 -s INLINING_LIMIT=1 -s NO_FILESYSTEM=1 -O2 --closure 0 --llvm-lto 1 --llvm-opts 2 --js-opts 1 --closure 1

CPPFLAGS=$(EFLAGS) -std=c++11 -DAI_FORCE_INLINE=inline
CFLAGS=$(EFLAGS) -DZ_HAVE_UNISTD_H=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_STDDEF_H=1
LDFLAGS=$(EFLAGS)

DISABLEFLAGS= \
-DASSIMP_BUILD_NO_X_IMPORTER=1 \
-DASSIMP_BUILD_NO_3DS_IMPORTER=1 \
-DASSIMP_BUILD_NO_MD3_IMPORTER=1 \
-DASSIMP_BUILD_NO_MDL_IMPORTER=1 \
-DASSIMP_BUILD_NO_MD2_IMPORTER=1 \
-DASSIMP_BUILD_NO_PLY_IMPORTER=1 \
-DASSIMP_BUILD_NO_ASE_IMPORTER=1 \
-DASSIMP_BUILD_NO_HMP_IMPORTER=1 \
-DASSIMP_BUILD_NO_SMD_IMPORTER=1 \
-DASSIMP_BUILD_NO_MDC_IMPORTER=1 \
-DASSIMP_BUILD_NO_MD5_IMPORTER=1 \
-DASSIMP_BUILD_NO_LWO_IMPORTER=1 \
-DASSIMP_BUILD_NO_DXF_IMPORTER=1 \
-DASSIMP_BUILD_NO_NFF_IMPORTER=1 \
-DASSIMP_BUILD_NO_RAW_IMPORTER=1 \
-DASSIMP_BUILD_NO_OFF_IMPORTER=1 \
-DASSIMP_BUILD_NO_AC_IMPORTER=1 \
-DASSIMP_BUILD_NO_BVH_IMPORTER=1 \
-DASSIMP_BUILD_NO_IRRMESH_IMPORTER=1 \
-DASSIMP_BUILD_NO_IRR_IMPORTER=1 \
-DASSIMP_BUILD_NO_Q3D_IMPORTER=1 \
-DASSIMP_BUILD_NO_B3D_IMPORTER=1 \
-DASSIMP_BUILD_NO_TERRAGEN_IMPORTER=1 \
-DASSIMP_BUILD_NO_CSM_IMPORTER=1 \
-DASSIMP_BUILD_NO_3D_IMPORTER=1 \
-DASSIMP_BUILD_NO_LWS_IMPORTER=1 \
-DASSIMP_BUILD_NO_OGRE_IMPORTER=1 \
-DASSIMP_BUILD_NO_MS3D_IMPORTER=1 \
-DASSIMP_BUILD_NO_COB_IMPORTER=1 \
-DASSIMP_BUILD_NO_BLEND_IMPORTER=1 \
-DASSIMP_BUILD_NO_Q3BSP_IMPORTER=1 \
-DASSIMP_BUILD_NO_NDO_IMPORTER=1 \
-DASSIMP_BUILD_NO_IFC_IMPORTER=1 \
-DASSIMP_BUILD_NO_XGL_IMPORTER=1 \
-DASSIMP_BUILD_NO_ASSBIN_IMPORTER=1 \
-DASSIMP_BUILD_NO_C4D_IMPORTER=1 \
-DASSIMP_BUILD_NO_X_EXPORTER=1 \
-DASSIMP_BUILD_NO_3DS_EXPORTER=1 \
-DASSIMP_BUILD_NO_MD3_EXPORTER=1 \
-DASSIMP_BUILD_NO_MDL_EXPORTER=1 \
-DASSIMP_BUILD_NO_MD2_EXPORTER=1 \
-DASSIMP_BUILD_NO_PLY_EXPORTER=1 \
-DASSIMP_BUILD_NO_ASE_EXPORTER=1 \
-DASSIMP_BUILD_NO_HMP_EXPORTER=1 \
-DASSIMP_BUILD_NO_SMD_EXPORTER=1 \
-DASSIMP_BUILD_NO_MDC_EXPORTER=1 \
-DASSIMP_BUILD_NO_MD5_EXPORTER=1 \
-DASSIMP_BUILD_NO_LWO_EXPORTER=1 \
-DASSIMP_BUILD_NO_DXF_EXPORTER=1 \
-DASSIMP_BUILD_NO_NFF_EXPORTER=1 \
-DASSIMP_BUILD_NO_RAW_EXPORTER=1 \
-DASSIMP_BUILD_NO_OFF_EXPORTER=1 \
-DASSIMP_BUILD_NO_AC_EXPORTER=1 \
-DASSIMP_BUILD_NO_BVH_EXPORTER=1 \
-DASSIMP_BUILD_NO_IRRMESH_EXPORTER=1 \
-DASSIMP_BUILD_NO_IRR_EXPORTER=1 \
-DASSIMP_BUILD_NO_Q3D_EXPORTER=1 \
-DASSIMP_BUILD_NO_B3D_EXPORTER=1 \
-DASSIMP_BUILD_NO_TERRAGEN_EXPORTER=1 \
-DASSIMP_BUILD_NO_CSM_EXPORTER=1 \
-DASSIMP_BUILD_NO_3D_EXPORTER=1 \
-DASSIMP_BUILD_NO_LWS_EXPORTER=1 \
-DASSIMP_BUILD_NO_OGRE_EXPORTER=1 \
-DASSIMP_BUILD_NO_MS3D_EXPORTER=1 \
-DASSIMP_BUILD_NO_COB_EXPORTER=1 \
-DASSIMP_BUILD_NO_BLEND_EXPORTER=1 \
-DASSIMP_BUILD_NO_Q3BSP_EXPORTER=1 \
-DASSIMP_BUILD_NO_NDO_EXPORTER=1 \
-DASSIMP_BUILD_NO_IFC_EXPORTER=1 \
-DASSIMP_BUILD_NO_XGL_EXPORTER=1 \
-DASSIMP_BUILD_NO_ASSBIN_EXPORTER=1 \
-DASSIMP_BUILD_NO_C4D_EXPORTER=1 

# These are the files we support:
#-DASSIMP_BUILD_NO_OBJ_IMPORTER=1 \
#-DASSIMP_BUILD_NO_COLLADA_EXPORTER=1 \
#-DASSIMP_BUILD_NO_STL_EXPORTER=1 \
#-DASSIMP_BUILD_NO_OBJ_EXPORTER=1 \
#-DASSIMP_BUILD_NO_FBX_IMPORTER=1 \
#-DASSIMP_BUILD_NO_STL_IMPORTER=1 \
#-DASSIMP_BUILD_NO_FBX_EXPORTER=1 \
#-DASSIMP_BUILD_NO_COLLADA_IMPORTER=1 \
# BUG -DASSIMP_BUILD_NO_OPENGEX_EXPORTER=1 \
# -DASSIMP_BUILD_NO_OPENGEX_IMPORTER=1 \


ASSIMP_CORE_SRC = \
assimp/code/Assimp.cpp \
assimp/code/BaseImporter.cpp \
assimp/code/BaseProcess.cpp \
assimp/code/Bitmap.cpp \
assimp/code/CalcTangentsProcess.cpp \
assimp/code/ComputeUVMappingProcess.cpp \
assimp/code/ConvertToLHProcess.cpp \
assimp/code/DeboneProcess.cpp \
assimp/code/DefaultIOStream.cpp \
assimp/code/DefaultIOSystem.cpp \
assimp/code/DefaultLogger.cpp \
assimp/code/Exporter.cpp \
assimp/code/FindDegenerates.cpp \
assimp/code/FindInstancesProcess.cpp \
assimp/code/FindInvalidDataProcess.cpp \
assimp/code/FixNormalsStep.cpp \
assimp/code/GenFaceNormalsProcess.cpp \
assimp/code/GenVertexNormalsProcess.cpp \
assimp/code/Importer.cpp \
assimp/code/ImporterRegistry.cpp \
assimp/code/ImproveCacheLocality.cpp \
assimp/code/JoinVerticesProcess.cpp \
assimp/code/LimitBoneWeightsProcess.cpp \
assimp/code/MakeVerboseFormat.cpp \
assimp/code/MaterialSystem.cpp \
assimp/code/OptimizeGraph.cpp \
assimp/code/OptimizeMeshes.cpp \
assimp/code/PostStepRegistry.cpp \
assimp/code/PretransformVertices.cpp \
assimp/code/ProcessHelper.cpp \
assimp/code/RawLoader.cpp \
assimp/code/RemoveComments.cpp \
assimp/code/RemoveRedundantMaterials.cpp \
assimp/code/RemoveVCProcess.cpp \
assimp/code/SGSpatialSort.cpp \
assimp/code/SceneCombiner.cpp \
assimp/code/ScenePreprocessor.cpp \
assimp/code/SkeletonMeshBuilder.cpp \
assimp/code/SortByPTypeProcess.cpp \
assimp/code/SpatialSort.cpp \
assimp/code/SplitByBoneCountProcess.cpp \
assimp/code/SplitLargeMeshes.cpp \
assimp/code/StandardShapes.cpp \
assimp/code/Subdivision.cpp \
assimp/code/TargetAnimation.cpp \
assimp/code/TextureTransform.cpp \
assimp/code/TriangulateProcess.cpp \
assimp/code/ValidateDataStructure.cpp \
assimp/code/Version.cpp \
assimp/code/VertexTriangleAdjacency.cpp 


ASSIMP_FILE_FORMAT_SRC = \
assimp/code/ColladaExporter.cpp \
assimp/code/ColladaLoader.cpp \
assimp/code/ColladaParser.cpp \
assimp/code/ObjExporter.cpp \
assimp/code/ObjFileImporter.cpp \
assimp/code/ObjFileMtlImporter.cpp \
assimp/code/ObjFileParser.cpp \
assimp/code/FBXAnimation.cpp \
assimp/code/FBXBinaryTokenizer.cpp \
assimp/code/FBXConverter.cpp \
assimp/code/FBXDeformer.cpp \
assimp/code/FBXDocument.cpp \
assimp/code/FBXDocumentUtil.cpp \
assimp/code/FBXImporter.cpp \
assimp/code/FBXMaterial.cpp \
assimp/code/FBXMeshGeometry.cpp \
assimp/code/FBXModel.cpp \
assimp/code/FBXNodeAttribute.cpp \
assimp/code/FBXParser.cpp \
assimp/code/FBXProperties.cpp \
assimp/code/FBXTokenizer.cpp \
assimp/code/FBXUtil.cpp \
assimp/code/STLExporter.cpp \
assimp/code/STLLoader.cpp \
assimp/code/OpenGEXExporter.cpp \
assimp/code/OpenGEXImporter.cpp

ASSIMP_CONTRIB_SRC = \
assimp/contrib/clipper/clipper.cpp \
assimp/contrib/irrXML/irrXML.cpp \
assimp/contrib/poly2tri/poly2tri/common/shapes.cc \
assimp/contrib/poly2tri/poly2tri/sweep/advancing_front.cc \
assimp/contrib/poly2tri/poly2tri/sweep/cdt.cc \
assimp/contrib/poly2tri/poly2tri/sweep/sweep.cc \
assimp/contrib/poly2tri/poly2tri/sweep/sweep_context.cc \
assimp/contrib/unzip/ioapi.c \
assimp/contrib/unzip/unzip.c \
assimp/contrib/zlib/adler32.c \
assimp/contrib/zlib/compress.c \
assimp/contrib/zlib/crc32.c \
assimp/contrib/zlib/deflate.c \
assimp/contrib/zlib/gzclose.c \
assimp/contrib/zlib/gzlib.c \
assimp/contrib/zlib/gzread.c \
assimp/contrib/zlib/gzwrite.c \
assimp/contrib/zlib/infback.c \
assimp/contrib/zlib/inffast.c \
assimp/contrib/zlib/inflate.c \
assimp/contrib/zlib/inftrees.c \
assimp/contrib/zlib/trees.c \
assimp/contrib/zlib/uncompr.c \
assimp/contrib/zlib/zutil.c

EMBINDSRC = \
src/AnimEmbind.cpp \
src/CameraEmbind.cpp \
src/Color4Embind.cpp \
src/LightEmbind.cpp \
src/MaterialEmbind.cpp \
src/Matrix3x3Embind.cpp \
src/Matrix4x4Embind.cpp \
src/MeshEmbind.cpp \
src/PostProcessEmbind.cpp \
src/QuaternionEmbind.cpp \
src/SceneEmbind.cpp \
src/TextureEmbind.cpp \
src/TypesEmbind.cpp \
src/Vector2Embind.cpp \
src/Vector3Embind.cpp \
src/ImporterEmbind.cpp \
src/ExporterEmbind.cpp 

SRC = $(EMBINDSRC) $(ASSIMP_CORE_SRC) $(ASSIMP_FILE_FORMAT_SRC) $(ASSIMP_CONTRIB_SRC)
OBJ = $(addsuffix .bc, $(basename $(SRC)))
TARGET = assimp.js

assimp.js: $(OBJ)
	$(EMCC) $(LDFLAGS) $(OBJ) -o $(TARGET)

debug: $(OBJ)
		$(EMCC) $(LDFLAGS) $(OBJ) -o $(TARGET)

%.bc: %.cpp
	$(EMCC) $(IFLAGS) $(CPPFLAGS) $(DISABLEFLAGS) -o $@ $^

%.bc: %.cc
	$(EMCC) $(IFLAGS) $(CPPFLAGS) -o $@ $^

%.bc: %.c
	$(EMCC) $(IFLAGS) $(CFLAGS) -o $@ $^		

.PHONY: clean

clean:
	rm -f $(OBJ) $(TARGET)











