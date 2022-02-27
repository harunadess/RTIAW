#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

template<typename T>
class ray
{
public:
	ray<T>() {}
	ray<T>(const point3<T> &origin, const vec3<T> &direction)
		: orig(origin), dir(direction)
	{}

	point3<T> origin() const { return orig; }
	vec3<T> direction() const { return dir; }

	// computes P(t) = A + tb;
	point3<T> at(T t) const
	{
		return orig + t*dir;
	}

	point3<T> orig;
	vec3<T> dir;
};

#endif // !RAY_H
