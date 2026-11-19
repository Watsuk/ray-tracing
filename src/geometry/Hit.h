#pragma once

#include <memory>
#include <optional>
#include "math/Vector.h"
#include "material/Material.h"

class MaterialRef {
private:
    const Material* _ptr{nullptr};
    std::shared_ptr<Material> _shared{nullptr};

public:
    MaterialRef() = default;
    MaterialRef(const Material& m) : _ptr(&m) {}
    MaterialRef(const Material* p) : _ptr(p) {}
    MaterialRef(std::shared_ptr<Material> sp) : _ptr(sp.get()), _shared(std::move(sp)) {}

    const Material* operator->() const { return _ptr; }
    const Material& operator*() const { return *_ptr; }
    operator const Material&() const { return *_ptr; }

    const Colour& colour() const {
        static const Colour black(0.0, 0.0, 0.0);
        return _ptr ? _ptr->colour() : black;
    }

    explicit operator bool() const { return _ptr != nullptr; }
    bool operator==(std::nullptr_t) const { return _ptr == nullptr; }
    bool operator!=(std::nullptr_t) const { return _ptr != nullptr; }
    bool operator==(const Material& other) const { return _ptr == &other; }
};

struct Hit {
    double t{0.0};
    Vector point;
    Vector normal;
    MaterialRef material;

    Hit()
        : t(0.0), point(0.0, 0.0, 0.0), normal(0.0, 0.0, 0.0), material() {}

    Hit(double tVal, const Vector& p, const Vector& n, MaterialRef m)
        : t(tVal), point(p), normal(n), material(std::move(m)) {}

    Hit(const Vector& p, const Vector& n, MaterialRef m)
        : t(0.0), point(p), normal(n), material(std::move(m)) {}
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
