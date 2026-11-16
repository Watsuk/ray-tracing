# 4. Continuous Integration with GitHub Actions and Dev Container

## Context

To support outside contributions and prevent regressions, pull requests must be validated automatically. The build and test steps need to run in an environment identical to local development to eliminate "works on my machine" issues. Alternative CI platforms include GitLab CI, CircleCI, or custom Docker runners.

## Decision

We will use GitHub Actions (`.github/workflows/ci.yml`) leveraging the Dev Container setup via `devcontainers/ci` to build the CMake targets and execute Catch2 tests with CTest on every pull request and push to `main`.

## Status

Proposed

## Consequences

### Positive
- Build and test commands execute in the exact same environment used locally by developers.
- Native integration with GitHub pull requests, reporting build or test failures directly on commits.

### Negative
- Running tests inside a Dev Container in GitHub Actions adds initial container startup overhead to the CI run time.
- Requires maintaining Docker / Dev Container compatibility when CI image configurations change.
