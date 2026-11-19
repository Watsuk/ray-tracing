# 5. A Shape Has a Material (Composition Over Inheritance)

## Context

In ray tracing, geometric objects (such as Spheres and Planes) must define how they interact with light (their colour and shading technique). When designing the relationship between shapes and surface appearance, two primary object-oriented strategies exist:

1. **Inheritance**: Creating specialized subclasses combining geometry and material (e.g. `RedSphere`, `GreenLambertPlane`, `MirrorSphere`).
2. **Composition**: Creating separate abstractions for geometry (`Shape`) and appearance (`Material`), where a shape holds an instance of or reference to a material.

Without clear separation, using inheritance would result in a combinatorial explosion of classes ($\text{Shapes} \times \text{Materials}$) and tight coupling between geometry mathematics and optical models.

## Decision

We will use **composition over inheritance**:
- Every concrete `Shape` (such as `Sphere` and `Plane`) owns or references a `Material` instance (`_material`).
- When a ray intersects a shape (`hit(ray)`), the resulting `Hit` record carries the hit point, surface normal, and the shape's `Material`.
- Shading is delegated to `Material::shade()`, allowing materials to vary independently from shapes ($\text{Shapes} + \text{Materials}$).

## Status

Proposed

## Consequences

### Positive
- **Extensibility (Open/Closed Principle)**: Adding a new shape requires only implementing geometric intersection math. Adding a new material or shader does not touch any shape classes.
- **Flexibility**: Any material can be applied to any shape at runtime without creating new classes.
- **Maintainability**: Clear separation of concerns between spatial geometry (where and which way) and optics (how light reflects).

### Negative
- **Indirection**: Shading requires routing light parameters through the `Hit` record to the associated material.
- **Memory Management**: Shapes must manage the lifetime or ownership of their associated materials.
