#ifndef CAMERA_H
#define CAMERA_H

#include "rtWeekend.hpp"

constexpr double aspectRatio = 16.0/9.0;
constexpr double viewportHeight = 2.0;
constexpr double viewportWidth = aspectRatio*viewportHeight;
constexpr double focalLength = 1.0;

class camera
{
public:
	camera()
	{
		origin = point3D(0.0, 0.0, 0.0);
		horizontal = vec3D(viewportWidth, 0.0, 0.0);
		vertical = vec3D(0.0, viewportHeight, 0.0);
		lowerLeftCorner = origin - (horizontal/2.0) - (vertical/2.0) - vec3D(0, 0, focalLength);
	}

	inline ray3D getRay(prec u, prec v) const
	{
		return ray3D(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
	}

private:
	point3D origin;
	point3D lowerLeftCorner;
	vec3D horizontal;
	vec3D vertical;
};

#endif // !CAMERA_H
