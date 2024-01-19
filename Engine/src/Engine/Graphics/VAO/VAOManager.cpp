#include "pch.h"

#include "Engine/Core/types.h"
#include "Engine/Graphics/VAO/VAOManager.h"
#include "Engine/Assimp/cAssimpHelper.h"
#include "Engine/Graphics/Shaders/ShaderManager.h"
#include "Engine/Graphics/opengl.h"

namespace MyEngine
{
    VAOManager::VAOManager() {}

    VAOManager::~VAOManager()
    {
    }

    void VAOManager::DestroyVBO(std::string modelName)
    {
        sMesh* pMesh = FindMeshByModelName(modelName);
        if (!pMesh)
        {
            //Model not loaded
            return;
        }
        glDeleteBuffers(1, &(pMesh->vertexBufferID));
        delete pMesh;
        m_mapModelNameToMesh.erase(modelName);

        return;
    }

    void VAOManager::SetBasePath(std::string basePath)
    {
        m_basePath = basePath;
        return;
    }

    sMesh* VAOManager::LoadModelIntoVAO(std::string& fileName, bool bIsDynamicBuffer,
                                        bool hasNormals, bool hasTexture)
    {
        // Load the model from file
        // Checking if the info already exist in our map
        sMesh* pMesh = FindMeshByModelName(fileName);
        if (pMesh)
        {
            // Info is already loaded
            return pMesh;
        }
        pMesh = new sMesh();
        pMesh->name = fileName;

        if (!m_LoadMeshData(fileName, pMesh))
        {
            return nullptr;
        }

        // Create a VAO (Vertex Array Object), which will 
        //	keep track of all the 'state' needed to draw 
        //	from this buffer...

        // Ask OpenGL for a new buffer ID...
        glGenVertexArrays(1, &(pMesh->VAO_ID));
        // "Bind" this buffer:
        // - aka "make this the 'current' VAO buffer
        glBindVertexArray(pMesh->VAO_ID);

        // Now ANY state that is related to vertex or index buffer
        //	and vertex attribute layout, is stored in the 'state' 
        //	of the VAO... 
        glGenBuffers(1, &(pMesh->vertexBufferID));

        glBindBuffer(GL_ARRAY_BUFFER, pMesh->vertexBufferID);

        glBufferData(GL_ARRAY_BUFFER,
            sizeof(sVertex) * pMesh->numberOfVertices,
            (GLvoid*)pMesh->pVertices,
            (bIsDynamicBuffer ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));

        // Copy the index buffer into the video card, 
        // too create an index buffer.
        glGenBuffers(1, &(pMesh->indexBufferID));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pMesh->indexBufferID);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            sizeof(uint) * pMesh->numberOfIndices,
            (GLvoid*)pMesh->pIndices,
            GL_STATIC_DRAW);

        iShaderProgram* pShader = ShaderManager::GetActiveShader();

        // Set the vertex attributes.
        GLint vpos_location = pShader->GetAL("vPos");
        GLint vcol_location = pShader->GetAL("vCol");
        GLint vNormal_location = pShader->GetAL("vNormal");
        GLint vTextureCoords_location = pShader->GetAL("vTextureCoords");

        // Set the vertex attributes for this shader
        // vPos
        glEnableVertexAttribArray(vpos_location);
        glVertexAttribPointer(vpos_location, 4,
            GL_FLOAT, GL_FALSE,
            sizeof(sVertex),
            (void*)offsetof(sVertex, x));
        // vCol 
        glEnableVertexAttribArray(vcol_location);
        glVertexAttribPointer(vcol_location, 4,
            GL_FLOAT, GL_FALSE,
            sizeof(sVertex),
            (void*)offsetof(sVertex, r));

        if (hasNormals)
        {
            glEnableVertexAttribArray(vNormal_location);
            glVertexAttribPointer(vNormal_location, 4,
                GL_FLOAT, GL_FALSE,
                sizeof(sVertex),
                (void*)offsetof(sVertex, nx));
        }

        if (hasTexture)
        {
            glEnableVertexAttribArray(vTextureCoords_location);
            glVertexAttribPointer(vTextureCoords_location, 2,
                GL_FLOAT, GL_FALSE,
                sizeof(sVertex),
                (void*)offsetof(sVertex, u));
        }

        // Now that all the parts are set up, set the VAO to zero
        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisableVertexAttribArray(vpos_location);
        glDisableVertexAttribArray(vcol_location);

        if (hasNormals)
        {
            glDisableVertexAttribArray(vNormal_location);
        }

        if (hasNormals)
        {
            glDisableVertexAttribArray(vTextureCoords_location);
        }

        // Store the draw information into the map
        m_mapModelNameToMesh[pMesh->name] = pMesh;

        return pMesh;
    }

    sMesh* VAOManager::LoadModelIntoVAO(std::string& fileName,
                                        bool bIsDynamicBuffer /*=false*/)

    {
        return LoadModelIntoVAO(fileName, bIsDynamicBuffer, true, true);
    }

    // We don't want to return an int, likely
    sMesh* VAOManager::FindMeshByModelName(std::string& filename)
    {
        std::map< std::string /*model name*/,
            sMesh* /* info needed to draw*/ >::iterator
            itDrawInfo = m_mapModelNameToMesh.find(filename);

        // Find it? 
        if (itDrawInfo == m_mapModelNameToMesh.end())
        {
            // Nope
            return nullptr;
        }

        return itDrawInfo->second;
    }

    bool VAOManager::m_LoadMeshData(std::string theFileName, sMesh* pMesh)
    {
        cFileLoader helper = cFileLoader();
        cFileLoader::sPostProcessFlags loadFlags;

        std::string fileFullPath = m_basePath + theFileName;
        bool isMeshLoaded = helper.Load3DModelFile(fileFullPath, loadFlags, pMesh);
        if (!isMeshLoaded)
        {
            std::string errorMsg = "Error: " + std::string(helper.getLastError().c_str());
            LOG_ERROR(errorMsg);
            return false;
        }

        return true;
    }

    bool VAOManager::UpdateVAOBuffers(std::string& fileName,
        std::string& shaderProgram,
        sMesh* pUpdatedMesh)
    {
        // This exists? 
        if (!FindMeshByModelName(fileName))
        {
            // Mesh not loaded
            return false;
        }

        // Set VBO
        glBindBuffer(GL_ARRAY_BUFFER, pUpdatedMesh->vertexBufferID);
        // Update data in buffer
        glBufferSubData(GL_ARRAY_BUFFER,
            0,  // Offset
            sizeof(sVertex) * pUpdatedMesh->numberOfVertices,
            (GLvoid*)pUpdatedMesh->pVertices);
        // Unbind VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Set index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pUpdatedMesh->indexBufferID);
        // Update data in buffer
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
            0,  // Offset
            sizeof(uint) * pUpdatedMesh->numberOfIndices,
            (GLvoid*)pUpdatedMesh->pIndices);
        // Unbind index buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return true;
    }
}
