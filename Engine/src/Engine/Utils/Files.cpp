#include "pch.h"

#include "Files.h"

#include <iostream>
#include <cstdio>

namespace MyEngine
{
    std::string GetFileExtension(const std::string& fileName)
    {
        size_t dotPos = fileName.find_last_of(".");
        if (dotPos != std::string::npos)
        {
            return fileName.substr(dotPos + 1);
        }
        return fileName; // Full string if no extension found
    }

    bool FileExists(const std::string& filePath)
    {
        FILE* file = std::fopen(filePath.c_str(), "r");
        if (file) {
            std::fclose(file);
            return true;
        }
        return false;
    }

    bool EraseFile(const std::string& filePath)
    {
        if (FileExists(filePath)) {
            if (std::remove(filePath.c_str()) == 0) {
                std::string success = "File erased successfully: " + filePath;
                LOG_INFO(success);
                return true;
            } else {
                std::string error = "Error erasing file: " + filePath;
                LOG_ERROR(error);
                return false;
            }
        }
        else {
            std::string warning = "File does not exist: " + filePath;
            LOG_WARNING(warning);
            return false;
        }
    }
}
