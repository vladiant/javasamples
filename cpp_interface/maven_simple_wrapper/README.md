# Java Simple JNI C++ Wrapper Example

Based on: https://habr.com/ru/articles/1017486/

Demonstrates how to create Java wrappers for C++ classes using JNI,
adapted from an Android/NDK tutorial to run on desktop Linux.

## Prerequisites

- JDK 11+ with JNI headers
- g++ with C++17 support
- Apache Maven 3.6+

## Project Structure

```
pom.xml
src/
  main/
    java/com/example/
      Main.java         # entry point
      Native.java       # JNI static native method declarations
      NativeClass.java  # Java wrapper managing the C++ object lifecycle
    native/
      NativeClass.h     # C++ class definition
      native_jni.cpp    # JNI bridge functions (extern "C")
```

Demonstrates the basic pattern:
- Store a C++ object pointer as `long` in Java
- Export C functions via JNI that cast the `long` back to the C++ object
- Java wrapper class manages the native object lifecycle (create/use/destroy)

## Build and Run

```bash
mvn compile exec:exec
```

**Expected output:**
```
=== Part 1: Simple JNI Wrapper ===
Calling fun() on nc1:
Hello from native
Calling fun() on nc2:
Hello from native
Done.
```

## Clean

```bash
mvn clean
```

## How It Works

The Maven build does two things during the `compile` phase:

1. **Native library** (`target/native/libNative.so`): compiled by `maven-antrun-plugin`
   invoking `g++` with the JDK's JNI headers (`${java.home}/include`).
2. **Java classes** (`target/classes`): compiled by `maven-compiler-plugin`.

Running is done via `exec-maven-plugin` which forks a JVM with
`-Djava.library.path=target/native` so that `System.loadLibrary("Native")` resolves
the shared library.

## Key Concepts (from the article)

1. **Object pointer as long**: C++ object address stored as `jlong`/`long` in Java
2. **C-function bridge**: JNI can only call C functions, so each C++ method gets a
   corresponding `extern "C"` JNI function that casts the `long` back to the object
3. **Weak global references**: For callbacks, use `NewWeakGlobalRef` to avoid preventing GC
4. **Thread attachment**: `AttachCurrentThread`/`DetachCurrentThread` required for calling
   Java from native threads
5. **Prevent GC of listeners**: Keep a strong Java reference to the listener object
