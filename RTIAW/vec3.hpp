#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "utils.hpp"

template<typename T>
class vec3
{
public:
	vec3() : e{ 0,0,0 } {}
	vec3(T e0, T e1, T e2) : e{ e0, e1, e2 } {}

	inline T x() const { return e[0]; }
	inline T y() const { return e[1]; }
	inline T z() const { return e[2]; }

	inline vec3<T> operator-() const { return vec3<T>(-e[0], -e[1], -e[2]); }
	inline T operator[](int i) const { return e[i]; }
	inline T &operator[](int i) { return e[i]; }

	inline vec3<T> &operator+=(const vec3<T> &v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	inline vec3<T> &operator*=(const T t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	inline vec3<T> &operator/=(const T t) { return *this *= (1/t); }

	inline T length() const { return std::sqrt(lengthSquared()); }

	inline T lengthSquared() const
	{
		return (e[0]*e[0]) + (e[1]*e[1]) + (e[2]*e[2]);
	}

	inline static vec3<T> random()
	{
		return vec3<T>(randomNumber(), randomNumber(), randomNumber());
	}

	inline static vec3<T> random(T min, T max)
	{
		return vec3<T>(randomNumber(min, max), randomNumber(min, max), randomNumber(min, max));
	}

	inline bool nearZero() const
	{
		// return true if the vector is close to zero in all dimensions
		const auto s = 1e-8;
		return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
	}

	T e[3];
};

// related types
template<class T>
using point3 = vec3<T>; // 3D point
template<class T>
using color = vec3<T>;	// RGB color

// utility functions
template<typename T>
inline std::ostream &operator<<(std::ostream &out, const vec3<T> &v)
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

template<typename T>
inline vec3<T> operator+(const vec3<T> &u, const vec3<T> &v)
{
	return vec3<T>((u.e[0] + v.e[0]), (u.e[1] + v.e[1]), (u.e[2] + v.e[2]));

}
template<typename T>
inline vec3<T> operator-(const vec3<T> &u, const vec3<T> &v)
{
	return vec3<T>((u.e[0] - v.e[0]), (u.e[1] - v.e[1]), (u.e[2] - v.e[2]));
}

template<typename T>
inline vec3<T> operator*(const vec3<T> &u, const vec3<T> &v)
{
	return vec3<T>((u.e[0]*v.e[0]), (u.e[1]*v.e[1]), (u.e[2]*v.e[2]));
}

template<typename T>
inline vec3<T> operator*(const vec3<T> &u, const T t)
{
	return vec3<T>((u.e[0]*t), (u.e[1]*t), (u.e[2]*t));
}

template<typename T>
inline vec3<T> operator*(const T t, const vec3<T> &v)
{
	return v*t;
}

template<typename T>
inline vec3<T> operator/(vec3<T> &v, T t)
{
	return (1/t)*v;
}

template<typename T>
inline T dot(const vec3<T> &u, const vec3<T> &v)
{
	return u.e[0]*v.e[0]
		 + u.e[1]*v.e[1]
		 + u.e[2]*v.e[2];
}

template<typename T>
inline vec3<T> cross(const vec3<T> &u, const vec3<T> &v)
{
	return vec3<T>(u.e[1]*v.e[2] - u.e[2]*v.e[1],
				   u.e[2]*v.e[0] - u.e[0]*v.e[2],
		           u.e[0]*v.e[1] - u.e[1]*v.e[0]);
}

template<typename T>
inline vec3<T> unitVector(vec3<T> v)
{
	return v / v.length();
}

template<typename T>
vec3<T> randomInUnitSphere()
{
	while(true)
	{
		vec3<T> p = vec3<T>::random(-1, 1);
		if(p.lengthSquared() >= 1) continue;
		return p;
	}
}

template<typename T>
vec3<T> randomUnitVector()
{
	return unitVector<T>(randomInUnitSphere<T>());
}

template<typename T>
vec3<T> randomInHemisphere(const vec3<T> &normal)
{
	vec3<T> inUnitSphere = randomInUnitSphere<T>();
	// in the same hemisphere as the normal
	if(dot(inUnitSphere, normal) > 0.0)
		return inUnitSphere;
	return -inUnitSphere;
}

template<typename T>
inline vec3<T> reflect(const vec3<T> &v, const vec3<T> &n)
{
	return v - 2*dot(v,n)*n;
}

#endif // !VEC3_H