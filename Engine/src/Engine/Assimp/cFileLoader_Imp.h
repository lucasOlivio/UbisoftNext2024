#pragma once

// This is the 'implementation' class for the PIMPL
// or "pointer to implementation" pattern. 
// 
// This one is completely hidden by another class. 
// This is because C++ doesn't have the concept of 'partial classes'
// so we put all the 'guts' of the code, including private stuff, here. 
// 
// This way we can't chage this class all we want and not force a re-compile. 

#include <string>
#include "cAssimpHelper.h"
#include "Engine/Graphics/GraphicsProperties.h"

struct aiScene; // For scene return pointer after scene loading

namespace MyEngine
{
	class cFileLoader_Imp
	{
	public:
		cFileLoader_Imp();
		~cFileLoader_Imp();

		bool Load3DModelFile(std::string filename, cFileLoader::sPostProcessFlags postProcessOptions, sMesh* drawInfo);
		void SetBasePath(std::string basepath_no_end_slash);

		std::string getLastError(bool bAndClearErrors = true);


	private:
		std::string m_basePath_no_end_slash;

		bool m_ProcessScene(const aiScene* scene, sMesh* drawInfo);
		void m_AppendErrorString(std::string errorString);
		std::string m_LastError;

		// Converts the boolean helper structure into the assimp flags:
		// https://assimp.sourceforge.net/lib_html/postprocess_8h.html#a64795260b95f5a4b3f3dc1be4f52e410a8857a0e30688127a82c7b8939958c6dc
		unsigned int m_loadAssimpPostProcessingFlags(cFileLoader::sPostProcessFlags postProcessOptions);

		unsigned int numberOfModelLoaded;

	};
}
