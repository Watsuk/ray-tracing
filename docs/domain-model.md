# Domain Model

```mermaid
classDiagram
    direction TB

    class Scene {
        -Vector _toLight
        -vector~unique_ptr~Shape~~ _shapes
        +toLight() const Vector&
        +add(unique_ptr~Shape~ shape) void
        +nearestHit(Ray ray) const optional~Hit~
    }

    class Shape {
        <<abstract>>
        +~Shape()*
        +hit(Ray ray)* const optional~Hit~
    }

    class Sphere {
        -Vector _center
        -double _radius
        -shared_ptr~Material~ _material
        +hit(Ray ray) const optional~Hit~
    }

    class Plane {
        -Vector _point
        -Vector _normal
        -shared_ptr~Material~ _material
        +hit(Ray ray) const optional~Hit~
    }

    class Material {
        #Colour _colour
        +colour() const Colour&
        +shade(Vector normal, Vector toLight) const Colour
    }

    class Hit {
        +double t
        +Vector point
        +Vector normal
        +MaterialRef material
    }

    class Ray {
        -Vector _origin
        -Vector _direction
        +origin() const Vector&
        +direction() const Vector&
        +at(double t) const Vector
    }

    class Camera {
        -Vector _position
        -double _screenWidth
        +rayThroughPixel(col, row, w, h) const Ray
        +render(Scene scene, w, h) const Image
    }

    Scene "1" *-- "*" Shape : owns
    Sphere ..|> Shape : implements
    Plane ..|> Shape : implements
    Sphere *-- "1" Material : has
    Plane *-- "1" Material : has
    Shape ..> Hit : produces
    Hit o-- "1" Material : references
    Camera ..> Scene : renders
    Camera ..> Ray : casts
```

### Key Relationships
- **Scene**: Owns any number of `Shape`s via `std::unique_ptr<Shape>` and holds the sun's direction (`toLight`).
- **Shape**: Abstract interface with pure virtual `hit(ray) const`.
- **Sphere & Plane**: Concrete shapes implementing `Shape`.
- **Material**: Encapsulates surface appearance and Lambertian shading ($N \cdot L$).
- **Composition**: Shapes *have* a `Material` rather than subclassing it ($\text{Shapes} + \text{Materials}$ instead of $\text{Shapes} \times \text{Materials}$).
