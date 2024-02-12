#pragma once

namespace Shapes3D
{
    class Point3D
    {
    public:
        Point3D();
        Point3D(double inX, double inY, double inZ);
        ~Point3D();

        double x() const;
        double y() const;
        double z() const;
        bool operator<(const Point3D &other) const;
        static double distanceBetweenPoints(const Point3D &p1, const Point3D &p2);

    private:
        double mX;
        double mY;
        double mZ;
    };
}
