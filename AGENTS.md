# Agent Guidelines

## Commands

- **Build:** `cmake -B build -DCMAKE_BUILD_TYPE=Debug && cmake --build build` (or `make build`)
- **Run:** `./build/bin/raytracer` (or `.\build\bin\raytracer.exe` on Windows, or `make run`)
- **Test:** `ctest --test-dir build --output-on-failure` (or `make test`, or `./build/bin/raytracer_tests -s`)

## Architecture Decision Records (ADRs)

- Architecture decisions are recorded in `docs/adr/`. Read them before modifying the build system, tools, or test setup.
- **Never go against an accepted ADR:** To propose changing a decision, create a new ADR with status `Proposed` and ask the user for review.
- **Never set an ADR to `Accepted`:** Only the user can accept ADRs.

## Contributing & Project Policies

- **Contributing Guide:** See `CONTRIBUTING.md` for workflow rules, dev container setup, and TDD expectations.
- **Code of Conduct:** See `CODE_OF_CONDUCT.md`.
- **License:** See `LICENSE` (MIT).
- **Templates & CI:** Issue and PR templates are located in `.github/`, and CI workflows are in `.github/workflows/`.
