# Contributing Guide

Welcome to the Raytracer project! We appreciate contributions that help keep our code modular, reliable, and clean.

## 1. Getting Started with the Dev Container

We use Dev Containers to guarantee a consistent development and build environment:
- **VS Code**: Open this repository and choose "Reopen in Container" when prompted.
- **Zed**: Open the project with your container runtime active. Clangd and tasks in `.zed/` are ready to use.
- **Native**: If developing without containers, ensure CMake 3.22+, a C++20 compiler, and Ninja/Make are installed.

## 2. Handy Commands (Makefile)

Use our make shortcuts for building and testing:

```bash
make build         # Configure and compile all targets
make run           # Run the demo raytracer executable
make test          # Run the unit tests via CTest
make test-verbose  # Run Catch2 directly with full assertion details
make clean         # Delete the build folder
```

## 3. Test-Driven Development (TDD)

All new features and bugfixes must follow the TDD workflow:
1. **Red**: Write a failing test in `tests/test_*.cpp` that specifies the desired behavior.
2. **Green**: Write the minimal code in `src/` to make the test pass.
3. **Refactor**: Clean up and optimize the implementation while keeping all tests passing.

Do not commit code that fails `make test`.

## 4. Architecture Decision Records (ADRs)

Our technical decisions are documented in `docs/adr/`:
- Read existing ADRs before modifying the build system, tools, or test framework.
- **Never contradict an accepted ADR**: If a change in architecture is required, create a new ADR in `docs/adr/` with status `Proposed` and request review.
- Only project maintainers may set an ADR to `Accepted`.

## 5. Submitting Changes

1. Create a feature branch from `main`.
2. Keep commits clear and descriptive (preferring conventional commit format, e.g., `feat: ...`, `fix: ...`, `test: ...`).
3. Ensure formatting matches `.clang-format` (`clang-format -i ...`).
4. Push your branch and open a Pull Request against `main`. Our CI pipeline will automatically test your changes inside the Dev Container.
