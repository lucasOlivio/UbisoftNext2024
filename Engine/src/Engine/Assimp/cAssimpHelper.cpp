#include "pch.h"
#include "AssimpFileLoaderHelper.h"

// We include the ACTUAL header here, since the compiler needs
//  to know how large the class really is in order to create one. 
#include "cFileLoader_Imp.h"

//#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
//#include <assimp/postprocess.h>     // Post processing flags

namespace MyEngine
{
    cFileLoader::cFileLoader()
    {
        // Create the implementation class...
        this->m_pImp = new cFileLoader_Imp();
    }

    cFileLoader::~cFileLoader()
    {
        // Delete the implementation class
        delete this->m_pImp;

    }

    bool cFileLoader::Load3DModelFile(std::string filename, sMesh* drawInfo)
    {
        sPostProcessFlags postProcessOptionsDefaults;
        return this->m_pImp->Load3DModelFile(filename, postProcessOptionsDefaults, drawInfo);

    }


    bool cFileLoader::Load3DModelFile(std::string filename, sPostProcessFlags postProcessOptions, sMesh* drawInfo)
    {
        return this->m_pImp->Load3DModelFile(filename, postProcessOptions, drawInfo);
    }

    void cFileLoader::SetBasePath(std::string basepath_no_end_slash)
    {
        this->m_pImp->SetBasePath(basepath_no_end_slash);
        return;
    }

    ass_cString cFileLoader::getLastError(bool bAndClearErrors /*=true*/)
    {
        return this->m_pImp->getLastError().c_str();
    }

    ass_cScene::ass_cScene()
    {
    }

    //
    void ass_cScene::ass_sSceneFlags::DecodeSceneFlags(unsigned int flags)
    {
        this->incomplete = (flags & AI_SCENE_FLAGS_INCOMPLETE);                 // 0x1
        this->validated = (flags & AI_SCENE_FLAGS_VALIDATED);                   // 0x2
        this->validation_warning = (flags & AI_SCENE_FLAGS_VALIDATION_WARNING); // 0x4
        this->non_verbose_format = (flags & AI_SCENE_FLAGS_NON_VERBOSE_FORMAT); // 0x8
        this->terrain = (flags & AI_SCENE_FLAGS_TERRAIN);                       // 0x10
        this->allow_shared = (flags & AI_SCENE_FLAGS_ALLOW_SHARED);             // 0x20
        return;
    };





    ass_cString::ass_cString()
    {
        this->m_reset();
    }

    ass_cString::ass_cString(const char* const c_str)
    {
        this->m_reset();

        this->m_numCharacters = (unsigned int)strlen(c_str);
        this->m_data = new char[this->m_numCharacters + 1];

        strncpy_s(this->m_data, this->m_numCharacters + 1, c_str, this->m_numCharacters);
    }

    // Copy constructor
    ass_cString::ass_cString(const ass_cString& copyString)
    {
        this->m_reset();

        this->m_numCharacters = copyString.m_numCharacters;

        this->m_data = new char[this->m_numCharacters + 1];

        strncpy_s(this->m_data, this->m_numCharacters + 1, copyString.m_data, this->m_numCharacters);
    }

    // Copy assignment 
    ass_cString& ass_cString::operator=(const ass_cString& copyString)
    {
        this->m_reset();

        this->m_numCharacters = copyString.m_numCharacters;

        this->m_data = new char[this->m_numCharacters + 1];

        strncpy_s(this->m_data, this->m_numCharacters + 1, copyString.m_data, this->m_numCharacters);

        return *this;
    }

    // concatenation
    ass_cString ass_cString::operator+(const ass_cString& concatString)
    {
        ass_cString newString;

        // TODO

        return newString;
    }

    ass_cString::~ass_cString()
    {
        this->m_reset();
    }

    unsigned int ass_cString::getLength()
    {
        return this->m_numCharacters;
    }

    const char* ass_cString::c_str(void) const
    {
        return this->m_data;
    }

    void ass_cString::m_reset(void)
    {
        if (this->m_data)
        {
            delete[] this->m_data;
            this->m_numCharacters = 0;
        }
        return;
    }
}