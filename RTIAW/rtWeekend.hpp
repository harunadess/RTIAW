#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>

// utility
#include "precision.hpp"
#include "utils.hpp"

// common headers
#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "sphere.hpp"
#include "material.hpp"
#include "hittableList.hpp"


// configured types
typedef point3<prec> point3D;
typedef vec3<prec> vec3D;
typedef color<prec> colorRGB;
typedef ray<prec> ray3D;

#endif // !RTWEEKEND_H
