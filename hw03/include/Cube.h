#ifndef Cube_h_
#define Cube_h_

#include <cmath>
#include "Object.h"

class Cube : public Object
{
    Vector3 center;
    float size;

public:
    Cube(const Vector3 &center, float size)
        : center(center), size(size) {}

    bool getIntersection(const Ray &ray, IntersectionInfo *I) const
    {
        float halfSize = size * 0.5f;

        Vector3 minV = center - Vector3(halfSize, halfSize, halfSize);
        Vector3 maxV = center + Vector3(halfSize, halfSize, halfSize);

        // x 區間
        float tmin = (minV.x - ray.o.x) / ray.d.x;
        float tmax = (maxV.x - ray.o.x) / ray.d.x;
        if (tmin > tmax)
            std::swap(tmin, tmax);

        // y 區間
        float tymin = (minV.y - ray.o.y) / ray.d.y;
        float tymax = (maxV.y - ray.o.y) / ray.d.y;
        if (tymin > tymax)
            std::swap(tymin, tymax);

        // 兩區間是否重疊
        if ((tmin > tymax) || (tymin > tmax))
            return false;

        tmin = std::max(tmin, tymin);
        tmax = std::min(tmax, tymax);

        // z 區間
        float tzmin = (minV.z - ray.o.z) / ray.d.z;
        float tzmax = (maxV.z - ray.o.z) / ray.d.z;
        if (tzmin > tzmax)
            std::swap(tzmin, tzmax);

        if ((tmin > tzmax) || (tzmin > tmax))
            return false;

        tmin = std::max(tmin, tzmin);
        tmax = std::min(tmax, tzmax);

        if (tmin < 0)
            return false;

        I->t = tmin;
        I->object = this;

        return true;
    }

    Vector3 getNormal(const IntersectionInfo &I) const
    {
        float halfSize = size * 0.5f;

        Vector3 minV = center - Vector3(halfSize, halfSize, halfSize);
        Vector3 maxV = center + Vector3(halfSize, halfSize, halfSize);

        Vector3 p = I.hit;
        const float EPS = 1e-4;

        // 交點在立方體的一個面上
        if (fabs(p.x - minV.x) < EPS)
            return Vector3(-1, 0, 0);
        if (fabs(p.x - maxV.x) < EPS)
            return Vector3(1, 0, 0);

        if (fabs(p.y - minV.y) < EPS)
            return Vector3(0, -1, 0);
        if (fabs(p.y - maxV.y) < EPS)
            return Vector3(0, 1, 0);

        if (fabs(p.z - minV.z) < EPS)
            return Vector3(0, 0, -1);
        if (fabs(p.z - maxV.z) < EPS)
            return Vector3(0, 0, 1);

        return Vector3(0, 1, 0);
    }

    BBox getBBox() const override
    {
        float halfSize = size * 0.5f;
        return BBox(center - Vector3(halfSize, halfSize, halfSize),
                    center + Vector3(halfSize, halfSize, halfSize));
    }

    Vector3 getCentroid() const override
    {
        return center;
    }
};

#endif