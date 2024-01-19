#pragma once

#include <string>

namespace MyEngine
{
    // Get string after last "." in file name
    std::string GetFileExtension(const std::string& fileName);

    bool FileExists(const std::string& filePath);

    bool EraseFile(const std::string& filePath);
}
