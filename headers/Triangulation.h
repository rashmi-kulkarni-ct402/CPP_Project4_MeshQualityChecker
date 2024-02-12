#pragma once
#include "Point3D.h"
#include "Triangle.h"
#include <vector>

namespace Shapes3D
{
    class Triangulation
    {
    public:
        Triangulation();
        ~Triangulation();

        std::vector<Point3D> uniquePoints() const;
        std::vector<Triangle> triangles() const;
        void addUniquePointToTriangulation(const Point3D inPoint);
        void addTriangleToTriangulation(const Triangle inTriangle);

    private:
        std::vector<Point3D> mUniquePoints;
        std::vector<Triangle> mTriangles;
    };
}