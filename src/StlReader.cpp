#include "../headers/StlReader.h"
#include "../headers/Triangulation.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

Shapes3D::StlReader::StlReader() {}
Shapes3D::StlReader::~StlReader() {}

void Shapes3D::StlReader::read(const std::string &filePath, Triangulation &triangulation)
{
    std::ifstream file(filePath);

    // checks for file opening error
    if (!file.is_open())
    {
        std::cout << "Error while opening the file." << std::endl;
    }

    int count = 0;
    int index1;
    int index2;
    int index3;
    std::string line;
    std::string keyword;
    std::map<Point3D, int> pointIndexMap;

    // reads obj file line by line
    while (getline(file, line))
    {
        std::istringstream iss(line);

        if (line.find("vertex") != std::string::npos)
        {
            double x;
            double y;
            double z;
            std::istringstream vertexStream(line);
            std::string keywordVertex;
            vertexStream >> keywordVertex >> x >> y >> z;

            Point3D point(x, y, z);

            // searchs for point in the map
            auto iterator = pointIndexMap.find(point);
            if (iterator == pointIndexMap.end())
            {
                // if not found in map, adds point to map
                pointIndexMap[point] = triangulation.uniquePoints().size();
                // adds point to triangulation object
                triangulation.addUniquePointToTriangulation(point);
            }

            // get vertex indices
            if (count == 0)
            {
                index1 = pointIndexMap[point];
                count++;
            }
            else if (count == 1)
            {
                index2 = pointIndexMap[point];
                count++;
            }
            else if (count == 2)
            {
                index3 = pointIndexMap[point];
                count++;
            }
            if (count == 3)
            {
                Triangle triangle(index1, index2, index3);
                // add triangle to triangulation object
                triangulation.addTriangleToTriangulation(triangle);
                count = 0;
            }
        }
    };
    std::cout << std::endl
              << "Data reading from .stl file completed successfully" << std::endl;
    // closing the file
    file.close();
}