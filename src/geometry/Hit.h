#pragma once

#include <memory>
#include <optional>
#include "math/Vector.h"

class Material;

struct Hit {
    double t{0.0};
    Vector point;
    Vector normal;
    std::shared_ptr<Material> material;

    Hit()
        : t(0.0), point(0.0, 0.0, 0.0), normal(0.0, 0.0, 0.0), material(nullptr) {}

    Hit(const Vector& p, const Vector& n, std::shared_ptr<Material> m)
        : t(0.0), point(p), normal(n), material(std::move(m)) {}

    Hit(double tVal, const Vector& p, const Vector& n, std::shared_ptr<Material> m)
        : t(tVal), point(p), normal(n), material(std::move(m)) {}
};

using HitInfo = Hit;
using Hinfo = Hit;

inline bool operator==(const std::optional<Hit>& opt, std::nullptr_t) {
    return !opt.has_value();
}
inline bool operator!=(const std::optional<Hit>& opt, std::nullptr_t) {
    return opt.has_value();
}
inline bool operator==(std::nullptr_t, const std::optional<Hit>& opt) {
    return !opt.has_value();
}
inline bool operator!=(std::nullptr_t, const std::optional<Hit>& opt) {
    return opt.has_value();
}
