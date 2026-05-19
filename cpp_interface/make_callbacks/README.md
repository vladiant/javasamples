# Java JNI C++ Wrapper Native Callbacks Example

Based on: https://habr.com/ru/articles/1017486/

Two projects demonstrating how to create Java wrappers for C++ classes using JNI,
adapted from an Android/NDK tutorial to run on desktop Linux.

## Prerequisites

- JDK 11+ (`javac`, `java`)
- g++ with C++17 support
- `JAVA_HOME` set (auto-detected if `java` is on PATH)

Demonstrates calling Java from C++:
- A C++ class with a `Listener` interface and a worker thread
- A JNI `Listener` adapter that calls back into Java via `JNIEnv`
- The Java side provides a `NativeListener` interface implementation
- The worker thread periodically calls the Java listener from native code

```bash
make run
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
make clean
```

## Key Concepts (from the article)

1. **Object pointer as long**: C++ object address stored as `jlong`/`long` in Java
2. **C-function bridge**: JNI can only call C functions, so each C++ method gets a
   corresponding `extern "C"` JNI function that casts the `long` back to the object
3. **Weak global references**: For callbacks, use `NewWeakGlobalRef` to avoid preventing GC
4. **Thread attachment**: `AttachCurrentThread`/`DetachCurrentThread` required for calling
   Java from native threads
5. **Prevent GC of listeners**: Keep a strong Java reference to the listener object
