#include "../headers/Point3D.h"
#include <cmath>

Shapes3D::Point3D::Point3D() : mX(), mY(), mZ() {}
Shapes3D::Point3D::Point3D(double inX, double inY, double inZ) : mX(inX), mY(inY), mZ(inZ) {}
Shapes3D::Point3D::~Point3D() {}

double Shapes3D::Point3D::x() const
{
    return mX;
}

double Shapes3D::Point3D::y() const
{
    return mY;
}

double Shapes3D::Point3D::z() const
{
    return mZ;
}

bool Shapes3D::Point3D::operator<(const Point3D &other) const
{
    if (mX < other.mX)
        return true;
    if (mX > other.mX)
        return false;

    if (mY < other.mY)
        return true;
    if (mY > other.mY)
        return false;

    return mZ < other.mZ;
}

double Shapes3D::Point3D::distanceBetweenPoints(const Shapes3D::Point3D &point1, const Shapes3D::Point3D &point2)
{
    // Calculate the distance using Euclidean distance formula
    double dx = point1.x() - point2.x();
    double dy = point1.y() - point2.y();
    double dz = point1.z() - point2.z();

    return std::sqrt(dx * dx + dy * dy + dz * dz);
}