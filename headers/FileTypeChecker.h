#pragma once
#include <string>

namespace Shapes3D
{
    class FileTypeChecker
    {
    public:
        FileTypeChecker();
        ~FileTypeChecker();

        bool isStlFile(const std::string &filename);
    };
}
