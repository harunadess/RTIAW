#include <iostream>
#include<chrono>

#include "camera.hpp"
#include "rtWeekend.hpp"

// note: why is this not in ray.hpp?
// linearly blends white and blue depending on the height of the y coordinate *after*
// scaling the ray direction to unit length (so -1 < y < 1)
// also called: linear interpolation
// blendedValue = (1 - t)startValue + t(endValue)
// with t going from 0 to 1
template <class C>
colorRGB rayColor(const ray3D &r, const C& world, int depth)
{
	// if ray bound limit is hit, stop gathering light
	if(depth <= 0)
		return colorRGB(0, 0, 0);

	hitRecord3D rec;
	// ignore any rays that hit very close to 0 (aka: shadow acne)
	if(world.hit(r, 0.01, INF, rec))
	{
		// "incorrect" diffusion method based on the normal
		// has darker shadows, more contrast (at least with standard diffuse textures)
		//point3D target = rec.p + rec.normal + randomUnitVector<prec>();
		// hemispherical scattering
		point3D target = rec.p + randomInHemisphere(rec.normal);
		return 0.5*(rayColor(ray3D(rec.p, target - rec.p), world, depth - 1));
	}
	vec3D unitDirection = unitVector(r.direction());
	auto t = 0.5*(unitDirection.y() + 1.0);
	return (1.0 - t)*colorRGB(1.0, 1.0, 1.0) + t*colorRGB(0.5, 0.7, 1.0);
}

// image constants
constexpr int imageWidth = 400;
constexpr int imageHeight = (int)(imageWidth/aspectRatio);
constexpr int samplesPerPixel = 100;
constexpr int maxDepth = 50;

// convenience type
typedef hittableList<sphere3D, prec> renderList;


/*
* 
*	As it turns out, template *everything* will (likely) not work
*	You would still need some kind of "generic" type. Perhaps you can use a
*	generic type without using shared_ptr. or maybe just use those anyways.
*/

int main()
{
	// world
	renderList world;
	world.add(sphere3D(point3D(0, 0, -1), 0.5));
	world.add(sphere3D(point3D(0, -100.5, -1), 100));

	// camera
	camera camera;

	auto origin = point3D(0, 0, 0);
	auto horizontal = vec3D(viewportWidth, 0, 0);
	auto vertical = vec3D(0, viewportHeight, 0);
	auto lowerLeftCorner = origin - horizontal/2.0 - vertical/2.0 - vec3D(0, 0, focalLength);

	auto start = std::chrono::steady_clock::now();

	// todo: make multi-threaded (cpu, gpu is probably not realistic...)
	// render
	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
	for(int j = ((imageHeight - 1)); j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for(int i = 0; i < imageWidth; ++i)
		{
			colorRGB pixelColor(0, 0, 0);
			for(int s = 0; s < samplesPerPixel; ++s)
			{
				auto u = (i + randomNumber())/(imageWidth - 1);
				auto v = (j + randomNumber())/(imageHeight - 1);
				ray3D r = camera.getRay(u, v);
				pixelColor += rayColor(r, world, maxDepth);
			}
			writeColor(std::cout, pixelColor, samplesPerPixel);
		}
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cerr << "\nDone in " << elapsed.count() << "s\n";

	return 0;
}