#include "../headers/MeshQualityChecker.h"
#include "../headers/Triangulation.h"
#include "../headers/Point3D.h"
#include "../headers/Triangle.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>

Shapes3D::MeshQualityChecker::MeshQualityChecker(Triangulation &triangulation) : triangulation(triangulation) {}
Shapes3D::MeshQualityChecker::~MeshQualityChecker() {}

// calculates area of a triangle
double Shapes3D::MeshQualityChecker::calculateTriangleArea(const Shapes3D::Triangle &triangle)
{
    // Get the indices of the vertices of the triangle
    int index1 = triangle.index1();
    int index2 = triangle.index2();
    int index3 = triangle.index3();

    // fetching vertex coordinates from triangulation.uniquePoints()
    Shapes3D::Point3D vertex1 = triangulation.uniquePoints()[index1];
    Shapes3D::Point3D vertex2 = triangulation.uniquePoints()[index2];
    Shapes3D::Point3D vertex3 = triangulation.uniquePoints()[index3];

    // calculating lengths of sides of triangle
    double side1 = Shapes3D::Point3D::distanceBetweenPoints(vertex1, vertex2);
    double side2 = Shapes3D::Point3D::distanceBetweenPoints(vertex2, vertex3);
    double side3 = Shapes3D::Point3D::distanceBetweenPoints(vertex3, vertex1);

    // calculating semi-perimeter of the triangle
    double semiPerimeter = (side1 + side2 + side3) / 2;
    double area = sqrt(semiPerimeter * (semiPerimeter - side1) * (semiPerimeter - side2) * (semiPerimeter - side3));

    return area;
}

// calculating total surface area of all triangles in the mesh
double Shapes3D::MeshQualityChecker::calculateTotalSurfaceArea(const Shapes3D::Triangulation &triangulation)
{
    double totalSurfaceArea = 0.0;
    int triangleNumber = 1;

    // iterating each triangle in the triangulation to calculate its area
    for (const Shapes3D::Triangle &triangle : triangulation.triangles())
    {
        double triangleArea = calculateTriangleArea(triangle);
        totalSurfaceArea += triangleArea;
        std::cout << "Triangle " << triangleNumber << " area = " << triangleArea << std::endl;
        triangleNumber++;
    }
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Total Surface Area = " << totalSurfaceArea << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    return totalSurfaceArea;
}

// calculate mesh density
double Shapes3D::MeshQualityChecker::calculateMeshDensity(const Shapes3D::Triangulation &triangulation)
{
    double meshDensity = 0.0;
    // MeshQualityChecker checker;

    // calculating cube volume
    double surfaceArea = calculateTotalSurfaceArea(triangulation);

    // mesh density = total no. of triangles / total surface area
    if (surfaceArea != 0.0)
    {
        meshDensity = triangulation.triangles().size() / surfaceArea;
    }

    std::cout << "Mesh Density = " << meshDensity << std::endl;
    std::cout << "***************************************************" << std::endl;
    return meshDensity;
}

// calculating aspect ratio of a triangle

// TODO: should be triangle class resp.
double Shapes3D::MeshQualityChecker::calculateTriangleAspectRatio(const Shapes3D::Triangle &triangle)
{
    // Get the indices of the vertices of the triangle
    int index1 = triangle.index1();
    int index2 = triangle.index2();
    int index3 = triangle.index3();

    // fetching vertex coordinates from triangulation.uniquePoints()
    Shapes3D::Point3D vertex1 = triangulation.uniquePoints()[index1];
    Shapes3D::Point3D vertex2 = triangulation.uniquePoints()[index2];
    Shapes3D::Point3D vertex3 = triangulation.uniquePoints()[index3];

    // calculating lengths of the edges
    double side1 = Shapes3D::Point3D::distanceBetweenPoints(vertex1, vertex2);
    double side2 = Shapes3D::Point3D::distanceBetweenPoints(vertex2, vertex3);
    double side3 = Shapes3D::Point3D::distanceBetweenPoints(vertex3, vertex1);

    // finding longest and shortest edges
    double longestEdge = std::max(std::max(side1, side2), side3);
    double shortestEdge = std::min(std::min(side1, side2), side3);

    // aspect ratio = longest side of triangle / shortest side of triangle
    double aspectRatio = longestEdge / shortestEdge;
    return aspectRatio;
}

// calculates aspect ratio
double Shapes3D::MeshQualityChecker::calculateAspectRatio(const Shapes3D::Triangulation &triangulation)
{
    double maxAspectRatio = 0.0;

    for (const Shapes3D::Triangle &triangle : triangulation.triangles())
    {
        double triangleAspectRatio = calculateTriangleAspectRatio(triangle);
        std::cout << "Triangle aspect ratio: " << triangleAspectRatio << std::endl;

        if (triangleAspectRatio > maxAspectRatio)
        {
            maxAspectRatio = triangleAspectRatio;
        }
    }

    std::cout << "Maximum Aspect Ratio = " << maxAspectRatio << std::endl;
    return maxAspectRatio;
}

double Shapes3D::MeshQualityChecker::calculateAspectRatioSkewness(const Shapes3D::Triangulation &triangulation)
{
    // Vector to store aspect ratios of all triangles
    std::vector<double> aspectRatios;

    // Iterate over each triangle in the triangulation to calculate its aspect ratio
    for (const Shapes3D::Triangle &triangle : triangulation.triangles())
    {
        double aspectRatio = calculateTriangleAspectRatio(triangle);
        aspectRatios.push_back(aspectRatio);
    }

    // ideal aspect ratio
    double idealAspectRatio = 1.0;

    // Calculate mean aspect ratio
    double sumAspectRatio = std::accumulate(aspectRatios.begin(), aspectRatios.end(), 0.0);
    double meanAspectRatio = sumAspectRatio / aspectRatios.size();

    // Calculate skewness
    double sumCubedDeviations = 0.0;
    for (double aspectRatio : aspectRatios)
    {
        double deviation = aspectRatio - meanAspectRatio;
        sumCubedDeviations += deviation * deviation * deviation;
    }

    double variance = sqrt(sumCubedDeviations / aspectRatios.size());
    double aspectRatioSkewness = sumCubedDeviations / (aspectRatios.size() * std::pow(variance, 3));
    std::cout << "Aspect Ratio Skewness = " << aspectRatioSkewness << std::endl;
    return aspectRatioSkewness;
}

void Shapes3D::MeshQualityChecker::categorizeTriangles(const Shapes3D::Triangulation &triangulation,
                                                       Shapes3D::Triangulation &triangulationBadTriangles,
                                                       Shapes3D::Triangulation &triangulationGoodTriangles)
{
    for (const Triangle &triangle : triangulation.triangles())
    {
        double aspectRatio = calculateTriangleAspectRatio(triangle);
        if (!isAspectRatioWithinThreshold(aspectRatio))
        {
            // adding points to triangulationBadTriangles
            triangulationBadTriangles.addUniquePointToTriangulation(triangulation.uniquePoints()[triangle.index1()]);
            triangulationBadTriangles.addUniquePointToTriangulation(triangulation.uniquePoints()[triangle.index2()]);
            triangulationBadTriangles.addUniquePointToTriangulation(triangulation.uniquePoints()[triangle.index3()]);

            // adding triangle to triangulationBadTriangles
            triangulationBadTriangles.addTriangleToTriangulation(triangle);
        }
        else
        {
            // adding points to triangulationGoodTriangles
            triangulationGoodTriangles.addUniquePointToTriangulation(triangulation.uniquePoints()[triangle.index1()]);
            triangulationGoodTriangles.addUniquePointToTriangulation(triangulation.uniquePoints()[triangle.index2()]);
            triangulationGoodTriangles.addUniquePointToTriangulation(triangulation.uniquePoints()[triangle.index3()]);

            // adding triangle to triangulationGoodTriangles
            triangulationGoodTriangles.addTriangleToTriangulation(triangle);
        }
    }
}

bool Shapes3D::MeshQualityChecker::isAspectRatioWithinThreshold(double aspectRatio)
{
    // criteria: +/- 5% from sqrt(2)
    double idealAspectRatio = sqrt(2);
    double threshold = 0.05 * idealAspectRatio;
    return (aspectRatio >= (idealAspectRatio - threshold)) && (aspectRatio <= (idealAspectRatio + threshold));
}