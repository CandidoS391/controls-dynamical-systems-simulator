# Agent Instructions

## Project Overview

This repository is a computational mathematics toolkit
focused on control systems, numerical methods, and
electromagnetic applications.

The primary implementation language is C++.
Python is used for visualization and data analysis.

## Development Responsibilities

The project owner is responsible for mathematical
design, algorithm specifications, and final approval.

The coding agent is responsible for implementing
approved specifications, integrating changes,
and executing relevant tests.

Do not independently introduce new mathematical
algorithms or major architectural changes without
explicit authorization.

## Implementation Guidelines

- Follow the Google C++ Style Guide.
- Use .h files for headers and .cc files for implementations.
- Preserve existing class interfaces unless changes are requested.
- Prefer existing mathematical utilities over duplicate implementations.
- Keep numerical computations in C++.
- Use Python primarily for visualization.
- Do not introduce unnecessary dependencies.

### Naming Conventions

Follow the Google C++ Style Guide for naming conventions.

C++:
- Classes and structs: PascalCase (e.g., TransferFunction,
  NyquistAnalysis).
- Functions and methods: PascalCase (e.g., Evaluate(),
  CalculateGainMargin()).
- Local variables and function parameters: snake_case
  (e.g., max_frequency, num_samples).
- Private class member variables: snake_case with a trailing
  underscore (e.g., numerator_, denominator_).
- Compile-time constants: kPascalCase (e.g., kTolerance).
- Namespaces: snake_case.
- Header files: .h extension.
- Implementation files: .cc extension.

Python:
- Functions and variables: snake_case.
- Classes: PascalCase.
- Constants: UPPER_SNAKE_CASE.
- Follow PEP 8 conventions.

General:
- Use descriptive names that reflect mathematical meaning.
- Maintain naming consistency with existing project classes.
- Avoid unnecessary abbreviations.
- Do not rename existing public interfaces unless explicitly
  requested.

### Mathematical Naming

- Prefer variable names that reflect their mathematical
  or physical interpretation.
- Use descriptive names for numerical parameters,
  including frequencies, gains, tolerances, and coefficients.
- Preserve established mathematical terminology when
  translating pseudocode into C++.
- Avoid introducing alternative names for concepts
  already represented in the codebase.

## Numerical Correctness

- Implement algorithms according to the provided
  mathematical specifications.
- Account for numerical tolerances and edge cases.
- Verify results against known analytical examples
  whenever possible.
- Do not assume successful compilation implies
  mathematical correctness.

## Testing

- Run relevant tests after modifying functionality.
- Report which tests were executed.
- Report any failures or unverified behavior.
- Do not modify expected test results merely
  to make failing tests pass.

## Scope Control

- Modify only files necessary for the requested task.
- Avoid unrelated refactoring.
- Do not remove existing functionality without permission.
- Ask for clarification when mathematical requirements
  are ambiguous.

## Completion Reports

After completing a task, summarize:

1. Files changed.
2. Functionality implemented.
3. Tests executed and their results.
4. Remaining issues or limitations.