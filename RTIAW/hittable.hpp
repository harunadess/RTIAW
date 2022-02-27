#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"
#include "rtWeekend.hpp"

template <typename T, class M>
struct hitRecord
{
	point3<T> p;
	vec3<T> normal;
	M mat;
	T t;
	bool frontFace;

	inline void setFaceNormal(const ray<T> &r, const vec3<T> &outwardNormal)
	{
		frontFace = dot(r.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

//template <typename T>
//class hittable
//{
//public:
//	virtual bool hit(const ray<T> &r, T tMin, T tMax, hitRecord &rec) const = 0;
//};

#endif //!HITTABLE_H