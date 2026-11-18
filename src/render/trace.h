#pragma once

#include "geometry/Ray.h"
#include "geometry/Sphere.h"
#include "colour/Colour.h"

Colour trace(const Ray& ray, const Sphere& sphere);
