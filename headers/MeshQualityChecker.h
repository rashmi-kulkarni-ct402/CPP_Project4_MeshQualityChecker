#pragma once
#include "Triangulation.h"
#include "../headers/Point3D.h"
#include "../headers/Triangle.h"

namespace Shapes3D
{
    class MeshQualityChecker
    {
    public:
        MeshQualityChecker(Triangulation &triangulation);
        ~MeshQualityChecker();

        double calculateTotalSurfaceArea(const Triangulation &triangulation);
        double calculateMeshDensity(const Triangulation &triangulation);
        double calculateAspectRatio(const Triangulation &triangulation);
        double calculateAspectRatioSkewness(const Triangulation &triangulation);
        void categorizeTriangles(const Triangulation &triangulation,
                                 Triangulation &triangulationBadTriangles,
                                 Triangulation &triangulationGoodTriangles);

    private:
        double distanceBetweenPoints(const Point3D &point1, const Point3D &point2);
        double calculateTriangleArea(const Triangle &triangle);
        double calculateTriangleAspectRatio(const Triangle &triangle);
        bool isAspectRatioWithinThreshold(double aspectRatio);
        Triangulation &triangulation;
    };
}
