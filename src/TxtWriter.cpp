#include "../headers/TxtWriter.h"
#include <iostream>
#include <fstream>

Shapes3D::TxtWriter::TxtWriter() {}
Shapes3D::TxtWriter::~TxtWriter() {}

void Shapes3D::TxtWriter::write(std::string &filePath, Triangulation &triangulation)
{
    std::ofstream outFile(filePath);
    // checks for file opening error
    if (!outFile.is_open())
    {
        std::cout << "Error while opening .txt file." << std::endl;
        return;
    }

    // getting values of uniquePoints, triangles and assigning to new vectors -> points, triangles.
    std::vector<Point3D> points = triangulation.uniquePoints();
    std::vector<Triangle> triangles = triangulation.triangles();

    // iterating each triangle from traingles vector to write points
    for (const Triangle &triangle : triangles)
    {
        outFile << points[triangle.index1()].x() << " " << points[triangle.index1()].y() << " " << points[triangle.index1()].z() << std::endl;
        outFile << points[triangle.index2()].x() << " " << points[triangle.index2()].y() << " " << points[triangle.index2()].z() << std::endl;
        outFile << points[triangle.index3()].x() << " " << points[triangle.index3()].y() << " " << points[triangle.index3()].z() << std::endl;
    }
    // std::cout << "Data writting from .stl to .txt file successful!" << std::endl
    //           << std::endl;
    // closing the file
    outFile.close();
}

void Shapes3D::TxtWriter::writeBadTriangles(std::string &outputBadTrianglesFilePath, Shapes3D::Triangulation &triangulationBadTriangles)
{
    std::ofstream outFile(outputBadTrianglesFilePath);
    // checks for file opening error
    if (!outFile.is_open())
    {
        std::cout << "Error while opening .txt file." << std::endl;
        return;
    }

    // getting values of uniquePoints, triangles and assigning to new vectors -> points, triangles.
    std::vector<Point3D> points = triangulationBadTriangles.uniquePoints();
    std::vector<Triangle> triangles = triangulationBadTriangles.triangles();

    // iterating each triangle from traingles vector to write points
    for (const Triangle &triangle : triangles)
    {
        // Check if indices are within bounds
        if (triangle.index1() >= points.size() || triangle.index2() >= points.size() || triangle.index3() >= points.size())
        {
            std::cout << "Error: Triangle indices out of bounds." << std::endl;
            outFile.close();
            return;
        }

        // Write points of the triangle to the file
        outFile << points[triangle.index1()].x() << " " << points[triangle.index1()].y() << " " << points[triangle.index1()].z() << std::endl;
        outFile << points[triangle.index2()].x() << " " << points[triangle.index2()].y() << " " << points[triangle.index2()].z() << std::endl;
        outFile << points[triangle.index3()].x() << " " << points[triangle.index3()].y() << " " << points[triangle.index3()].z() << std::endl;
    }

    // std::cout << "Data writing from .stl to .txt file successful for bad triangles!" << std::endl
    //           << std::endl;

    // Closing the file
    outFile.close();
}

void Shapes3D::TxtWriter::writeGoodTriangles(std::string &outputGoodTrianglesFilePath, Shapes3D::Triangulation &triangulationGoodTriangles)
{
    std::ofstream outFile(outputGoodTrianglesFilePath);
    // checks for file opening error
    if (!outFile.is_open())
    {
        std::cout << "Error while opening .txt file." << std::endl;
        return;
    }

    // getting values of uniquePoints, triangles and assigning to new vectors -> points, triangles.
    std::vector<Point3D> points = triangulationGoodTriangles.uniquePoints();
    std::vector<Triangle> triangles = triangulationGoodTriangles.triangles();

    // iterating each triangle from traingles vector to write points
    for (const Triangle &triangle : triangles)
    {
        // Check if indices are within bounds
        if (triangle.index1() >= points.size() || triangle.index2() >= points.size() || triangle.index3() >= points.size())
        {
            std::cout << "Error: Triangle indices out of bounds." << std::endl;
            outFile.close();
            return;
        }

        // Write points of the triangle to the file
        outFile << points[triangle.index1()].x() << " " << points[triangle.index1()].y() << " " << points[triangle.index1()].z() << std::endl;
        outFile << points[triangle.index2()].x() << " " << points[triangle.index2()].y() << " " << points[triangle.index2()].z() << std::endl;
        outFile << points[triangle.index3()].x() << " " << points[triangle.index3()].y() << " " << points[triangle.index3()].z() << std::endl;
    }

    // std::cout << "Data writing from .stl to .txt file successful for good triangles!" << std::endl
    //           << std::endl;

    // Closing the file
    outFile.close();
}
