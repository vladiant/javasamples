# Java Bazel Sample

A minimal Java project built with [Bazel](https://bazel.build/) using Bzlmod.

## Prerequisites

- [Bazel](https://bazel.build/install) 6.0 or later
- JDK 11 or later

## Project Structure

```
.
├── MODULE.bazel                          # Bazel module / dependency manifest
├── WORKSPACE                             # Legacy workspace file (empty)
├── BUILD                                 # Root BUILD file
└── src/
    └── main/
        └── java/
            └── com/
                └── example/
                    ├── BUILD             # Build target for the application
                    └── App.java          # Main entry point
```

## Build

```bash
bazel build //src/main/java/com/example:App
```

## Run

```bash
bazel run //src/main/java/com/example:App
```

Expected output:

```
Hello, Bazel!
```

## Clean

```bash
bazel clean
```
