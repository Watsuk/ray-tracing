# 6. PNG Image Output Library

## Context

The ray tracer must save rendered images to disk as PNG files for visual validation and deliverable milestones (`image.png`). The solution must work identically across developer workstations (Linux, Windows, macOS), within the Docker Dev Container, and in GitHub Actions CI without requiring complex manual package installation.

We evaluated three potential approaches:

1. **libpng + zlib**: The industry-standard reference implementation. While mature and highly optimized, it requires linking against C system libraries (`libpng-dev`, `zlib1g-dev`) or managing binary dependencies via package managers (`vcpkg`, `conan`), increasing environment setup friction.
2. **stb_image_write**: A popular single-header C library. It is easy to include, but provides only image writing without built-in PNG decoding, which prevents self-contained round-trip unit testing.
3. **LodePNG**: A self-contained, header-and-source PNG encoder and decoder in C++ with zero external dependencies (no separate `zlib` or `libpng` required).

## Decision

We use **LodePNG** integrated via CMake `FetchContent` pinned to commit `7b2893e35891c0c85bee5595caafaf3c2044b409`:

- LodePNG is compiled as a static library target (`lodepng`) directly within CMake.
- Image output logic is encapsulated behind an abstract `ImageSaver` interface and a concrete `PngSaver` class.
- `PngSaver` converts the internal floating-point `Colour` buffer (`[0.0, 1.0]`) to 8-bit RGBA pixels and invokes `lodepng::encode`.
- LodePNG's `decode` API is used in unit tests (`test_image_saver.cpp`) to verify saved image dimensions and pixel values without external test tooling.

## Status

Proposed

## Consequences

### Positive
- **Zero external dependencies**: Builds cleanly out of the box on any system with CMake and a C++17 compiler.
- **Reproducible build**: Pinned Git commit hash in `FetchContent` ensures deterministic builds across CI and developer environments.
- **Testability**: Enables round-trip test verification (render -> save -> decode -> assert pixel colours) entirely within Catch2.
- **Clean separation**: The `ImageSaver` abstraction decouples core rendering logic from file format encoding details.

### Negative
- Compression performance is slightly slower than `libpng` with hardware-accelerated SIMD `zlib`, but this overhead is negligible for our image resolutions.
- CMake configure step requires internet access on first run to fetch the repository (cached in subsequent builds).
