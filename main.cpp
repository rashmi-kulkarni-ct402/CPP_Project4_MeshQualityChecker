#include <iostream>
#include "./headers/Triangulation.h"
#include "./headers/Triangle.h"
#include "./headers/StlReader.h"
#include "./headers/TxtWriter.h"
#include "./headers/FileTypeChecker.h"
#include "./headers/MeshQualityChecker.h"

int main()
{
    // std::string inputFilePath = "resources/cube.stl";
    // std::string outputFilePath = "output/cube.txt";

    std::string inputFilePath = "resources/cube_withErrors.stl";
    std::string outputFilePath = "output/cube_forTesting.txt";
    std::string outputBadTrianglesFilePath = "output/cube_badTriangles.txt";
    std::string outputGoodTrianglesFilePath = "output/cube_goodTriangles.txt";

    Shapes3D::FileTypeChecker checker;
    if (!checker.isStlFile(inputFilePath))
    {
        std::cout << "Error! Input file is not a .stl file." << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        return 1;
    }

    Shapes3D::Triangulation triangulation;
    Shapes3D::Triangulation triangulationBadTriangles;
    Shapes3D::Triangulation triangulationGoodTriangles;
    Shapes3D::Triangle triangle;
    Shapes3D::StlReader stlReader;
    Shapes3D::TxtWriter txtWriter;
    Shapes3D::MeshQualityChecker meshQualityChecker(triangulation);

    stlReader.read(inputFilePath, triangulation);
    meshQualityChecker.calculateMeshDensity(triangulation);
    meshQualityChecker.calculateAspectRatio(triangulation);
    meshQualityChecker.calculateAspectRatioSkewness(triangulation);
    txtWriter.write(outputFilePath, triangulation);

    meshQualityChecker.categorizeTriangles(triangulation, triangulationBadTriangles, triangulationGoodTriangles);
    txtWriter.writeBadTriangles(outputBadTrianglesFilePath, triangulationBadTriangles);
    txtWriter.writeGoodTriangles(outputGoodTrianglesFilePath, triangulationGoodTriangles);

    // meshQualityChecker.calculateAspectRatioDistribution(triangulation, 250);
    std::cout << "***************************************************" << std::endl;
    return 0;
}

/*
read stl
check
depending on criteria - gve diff trian obj
writer take tri obj from checker
*/