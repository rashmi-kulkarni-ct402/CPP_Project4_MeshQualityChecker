#pragma once
#include "Triangulation.h"
#include <string>

namespace Shapes3D
{
    class TxtWriter
    {
    public:
        TxtWriter();
        ~TxtWriter();

        void write(std::string &filePath, Triangulation &triangulation);

        void writeBadTriangles(std::string &outputBadTrianglesFilePath, Triangulation &triangulationBadTriangles);

        void writeGoodTriangles(std::string &outputGoodTrianglesFilePath, Triangulation &triangulationGoodTriangles);
    };
}