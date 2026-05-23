# Java JNI C++ Wrapper Native Callbacks Example

Based on: https://habr.com/ru/articles/1017486/

Demonstrates how to create Java wrappers for C++ classes using JNI,
adapted from an Android/NDK tutorial to run on desktop Linux.

Specifically: calling Java from C++ via callbacks —
- A C++ class with a `Listener` interface and a worker thread
- A JNI `Listener` adapter that calls back into Java via `JNIEnv`
- The Java side provides a `NativeListener` interface implementation
- The worker thread periodically calls the Java listener from native code

## Prerequisites

- JDK 11+
- g++ with C++17 support
- Apache Maven 3.6+

## Project Structure

```
pom.xml
src/main/java/com/example/   # Java sources
src/main/native/             # C++ JNI sources
```

## Build

```bash
mvn package
```

This compiles the Java sources and builds `target/lib/libNative.so`.

## Run

```bash
mvn exec:exec
```

**Expected output** (runs for ~5 seconds):
```
=== Part 2: Callbacks from Native ===
[Java callback] From native
[Java callback] From native
[Java callback] From native
[Java callback] From native
[Java callback] From native
Stopping scan...
Done.
```

## Clean

```bash
mvn clean
```

## Key Concepts (from the article)

1. **Object pointer as long**: C++ object address stored as `jlong`/`long` in Java
2. **C-function bridge**: JNI can only call C functions, so each C++ method gets a
   corresponding `extern "C"` JNI function that casts the `long` back to the object
3. **Weak global references**: For callbacks, use `NewWeakGlobalRef` to avoid preventing GC
4. **Thread attachment**: `AttachCurrentThread`/`DetachCurrentThread` required for calling
   Java from native threads
5. **Prevent GC of listeners**: Keep a strong Java reference to the listener object
