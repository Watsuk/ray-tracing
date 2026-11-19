# 5. A Shape Has a Material

## Context

A surface in the ray tracer needs both a geometry (how it meets a ray) and an appearance (how it takes the light). As new shapes (`Sphere`, `Plane`) and materials are introduced, the architecture must define how these two responsibilities relate.

We considered two approaches:
1. **Inheritance**: Subclassing shapes to include material behavior (e.g. `RedSphere`, `LambertianPlane`, `MirrorSphere`).
2. **Composition**: Giving each shape a `Material` field, delegating shading to the material while the shape computes only the geometry.

Inheritance creates a Cartesian product of classes: $N$ shapes and $M$ materials produce $N \times M$ subclasses. Adding a material would require updating or duplicating every existing shape.

## Decision

We choose **composition over inheritance**:
- An abstract class `Shape` defines the geometric interface (`hit`).
- Every concrete shape (`Sphere`, `Plane`) holds a `Material` instance (`_material`).
- On intersection, `hit()` returns a `Hit` record carrying the hit point, unit normal, and a reference to the shape's material.
- Shading is delegated to `Material::shade(normal, toLight)`.

Shapes *have* a material; they are not materials themselves.

## Status

Proposed

## Consequences

### Positive
- Adding a new shape or a new material requires adding only a single class ($N + M$ classes instead of $N \times M$).
- A shape's geometry mathematics is decoupled from optical reflection models.
- Shapes and materials can be combined freely at runtime.

### Negative
- Intersections must package and return a `Hit` record containing the material reference alongside geometric data.
- Shapes must store and manage the lifetime of their material.
