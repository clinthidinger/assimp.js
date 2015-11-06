
#include <emscripten/bind.h>
//#include <string>
#include "assimp/Importer.hpp"	//OO version Header!
#include "assimp/Exporter.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
//#include "assimp/DefaultLogger.hpp"
//#include "assimp/LogStream.hpp"

//#include "assimp/color4.h"
//#include "assimp/camera.h"
//#include "assimp/anim.h"
//#include "assimp/light.h"
//#include "assimp/material.h"
//#include "assimp/matrix3x3.h"
//#include "assimp/matrix4x4.h"
//#include "assimp/mesh.h"
//#include "assimp/quaternion.h"
//#include "assimp/texture.h"
//#include "assimp/types.h"
//#include "assimp/vector2.h"
//#include "assimp/vector3.h"

/*

assimp/include/assimp/ai_assert.h	assimp/include/assimp/defs.h		assimp/include/assimp/postprocess.h
assimp/include/assimp/anim.h		assimp/include/assimp/importerdesc.h	assimp/include/assimp/quaternion.h
assimp/include/assimp/camera.h		assimp/include/assimp/light.h		assimp/include/assimp/scene.h
assimp/include/assimp/cexport.h		assimp/include/assimp/material.h	assimp/include/assimp/texture.h
assimp/include/assimp/cfileio.h		assimp/include/assimp/matrix3x3.h	assimp/include/assimp/types.h
assimp/include/assimp/cimport.h		assimp/include/assimp/matrix4x4.h	assimp/include/assimp/vector2.h
assimp/include/assimp/color4.h		assimp/include/assimp/mesh.h		assimp/include/assimp/vector3.h
assimp/include/assimp/config.h		assimp/include/assimp/metadata.h	assimp/include/assimp/version.h


*/


#define DefineGetter(ClassType, MemberType, MemberName, FuncName) 	MemberType get##FuncName(ClassType &object) { return object.MemberName; }
#define DefineSetter(ClassType, MemberType, MemberName, FuncName)	void set##FuncName(ClassType &object, MemberType value) { object.MemberName = value; }

#define DefineGetterSetter(ClassName, MemberType, MemberName, FuncName) \
	DefineGetter(ClassName, MemberType, MemberName, FuncName) \
	DefineSetter(ClassName, MemberType, MemberName, FuncName)


using namespace emscripten;
using namespace Assimp;

// Importer
void getExtensionList(Importer &importer, aiString &str) 
{
	importer.GetExtensionList(str);
}

// Exporter
namespace aiNode_ext
{
	DefineGetter(aiNode, aiString &, mName, Name)
	void setName(aiNode &node, const std::string &value)
	{
		node.mName = value;
	}
	DefineGetterSetter(aiNode, aiMatrix4x4 &, mTransformation, Transformation)
	DefineGetterSetter(aiNode, aiNode *, mParent, Parent)
	DefineGetterSetter(aiNode, unsigned int, mNumChildren, NumChildren)
	DefineGetterSetter(aiNode, aiNode **, mChildren, Children)
	DefineGetterSetter(aiNode, unsigned int, mNumMeshes, NumMeshes)
	DefineGetterSetter(aiNode, unsigned int *, mMeshes, Meshes)
}


EMSCRIPTEN_BINDINGS(ASSIMP)
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


	//value_object<Exporter::ExportFormatEntry>("Exporter_ExportFormatEntry")
    //	.field("mDescription", &Exporter::ExportFormatEntry::mDescription)
    //    .field("mExportFunction", &Exporter::ExportFormatEntry::mExportFunction)
    //    .field("mEnforcePP", &Exporter::ExportFormatEntry::mEnforcePP)
    //    ;

	

// Will need to wrap all properties!!!



	



   	



    


	


   	

	

	



} // end EMSCRIPTEN_BINDINGS

