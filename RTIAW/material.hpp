#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtWeekend.hpp"

struct hitRecord3D;

//template<class M>
//class material
//{
//public:
//	virtual bool scatter(const ray3D &rIn, const hitRecord3D &rec, colorRGB &attenuation, ray3D &scattered) = 0;
//};

template<typename T>
class lambertian;

template<typename T>
class lambertian
{
public:
	lambertian(const color<T> &a)
		:albedo(a)
	{}

	bool scatter(const ray<T> &rIn, const hitRecord<T, lambertian<T>> &rec, color<T> &attenuation, ray<T> &scattered)
	{
		auto scatterDir = rec.normal + randomUnitVector<T>();

		// catch degenerate scatter direction
		if(scatterDir.nearZero())
			scatterDir = rec.normal;

		scattered = ray<T>(rec.p, scatterDir);
		// note: can make attenuation scatter with some probability p
		// so attenuation would be albedo/p
		attenuation = albedo;
		return true;
	}

	color<T> albedo;
};

//template<typename T>
//class metal
//{
//public:
//	metal(const color<T> &a)
//		:albedo(a)
//	{}
//
//	bool scatter(const ray<T> &rIn, const hitRecord<T, metal<T>> &rec, colorRGB &attenuation, ray3D &scattered) const
//	{
//		vec<T> reflected = reflect<T>(unitVector(rIn.direction()), rec.normal);
//		scattered = ray3D(rec.p, reflected);
//		attenuation = albedo;
//		return (dot(scattered.direction(), rec.normal) > 0);
//	}
//
//	colorRGB albedo;
//};

#endif // !MATERIAL_H
