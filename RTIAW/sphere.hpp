#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"

template <typename T>
class sphere //: public hittable
{
public:
	sphere() {}
	sphere(point3<T> cen, T r)
		:center(cen), radius(r)
	{}

	bool hit(const ray<T> &r, T tMin, T tMax, hitRecord<T> &rec) const;

	point3<T> center;
	T radius;
};

// (A + tb - C)(A + tb - C) = r^2
// t^2b(b) + 2tb(A - C)+ (A - C)(A - C) - r^2 = 0
template<typename T>
bool sphere<T>::hit(const ray<T> &r, T tMin, T tMax, hitRecord<T> &rec) const
{
	vec3<T> oc = r.origin() - center;
	auto a = r.direction().lengthSquared();
	auto halfB = dot(oc, r.direction());
	auto c = oc.lengthSquared() - radius*radius;

	auto discriminant = halfB*halfB - a*c;
	if(discriminant < 0)
		return false;

	auto sqrtd = sqrt(discriminant);

	// find the nearest root that lies in the acceptable range
	auto root = (-halfB - sqrtd)/a;
	if(root < tMin || tMax < root)
	{
		root = (-halfB + sqrtd)/a;
		if(root < tMin || tMax < root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3<T> normal = (rec.p - center);
	vec3<T> outwardNormal = normal/radius;
	rec.setFaceNormal(r, outwardNormal);

	return true;
}

#endif //!SPHERE_H