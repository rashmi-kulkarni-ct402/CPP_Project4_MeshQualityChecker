#include "../headers/FileTypeChecker.h"
#include <string>
#include <algorithm>

Shapes3D::FileTypeChecker::FileTypeChecker() {}
Shapes3D::FileTypeChecker::~FileTypeChecker() {}

bool Shapes3D::FileTypeChecker::isStlFile(const std::string &filename)
{
    size_t dotPosition = filename.find_last_of('.');
    if (dotPosition == std::string::npos)
    {
        return false;
    }

    std::string extension = filename.substr(dotPosition + 1);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    return (extension == "stl");
}
