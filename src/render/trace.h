#pragma once

#include "geometry/Ray.h"
#include "geometry/Sphere.h"
#include "colour/Colour.h"
#include "light/Light.h"

Colour trace(const Ray& ray, const Sphere& sphere, const Light& light);
Colour trace(const Ray& ray, const Sphere& sphere);
