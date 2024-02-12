#pragma once
#include "Triangulation.h"
#include <string>

namespace Shapes3D
{
    class StlReader
    {
    public:
        StlReader();
        ~StlReader();

        void read(const std::string &filePath, Triangulation &triangulation);
    };
}