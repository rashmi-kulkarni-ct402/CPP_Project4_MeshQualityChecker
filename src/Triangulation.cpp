#include "../headers/Triangulation.h"
#include "../headers/Point3D.h"
#include "../headers/Triangle.h"
#include <vector>

Shapes3D::Triangulation::Triangulation() {}
Shapes3D::Triangulation::~Triangulation() {}

// vector for storing unique points
std::vector<Shapes3D::Point3D> Shapes3D::Triangulation::uniquePoints() const
{
    return mUniquePoints;
}

// vector for storing triangles
std::vector<Shapes3D::Triangle> Shapes3D::Triangulation::triangles() const
{
    return mTriangles;
}

// adds a point to mUniquePoints vector
void Shapes3D::Triangulation::addUniquePointToTriangulation(const Shapes3D::Point3D inPoint)
{
    mUniquePoints.push_back(inPoint);
}

// adds a triangle to mTriangles vector
void Shapes3D::Triangulation::addTriangleToTriangulation(const Shapes3D::Triangle inTriangle)
{
    mTriangles.push_back(inTriangle);
}
