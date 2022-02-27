#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "vec3.hpp"

constexpr int BIT_DEPTH = 256;

// write the translated [0,255] value of each color component
template<typename T>
void writeColor(std::ostream &out, color<T> pixel, int samplesPerPixel)
{
	T r = pixel.x();
	T g = pixel.y();
	T b = pixel.z();

	// divide the color by the number of samples
	// and gamma-correct for gamma = 2.0
	auto scale = 1.0/samplesPerPixel;
	r = sqrt(scale*r);
	g = sqrt(scale*g);
	b = sqrt(scale*b);

	out << (int)(BIT_DEPTH*clamp(r, 0.0, 0.999)) << ' '
		<< (int)(BIT_DEPTH*clamp(g, 0.0, 0.999)) << ' '
		<< (int)(BIT_DEPTH*clamp(b, 0.0, 0.999)) << '\n';
}

#endif // !COLOR_H
