# Java Simple JNI C++ Wrapper Example

Based on: https://habr.com/ru/articles/1017486/

Two projects demonstrating how to create Java wrappers for C++ classes using JNI,
adapted from an Android/NDK tutorial to run on desktop Linux.

## Prerequisites

- JDK 11+ (`javac`, `java`)
- g++ with C++17 support
- `JAVA_HOME` set (auto-detected if `java` is on PATH)

Demonstrates the basic pattern:
- Store a C++ object pointer as `long` in Java
- Export C functions via JNI that cast the `long` back to the C++ object
- Java wrapper class manages the native object lifecycle (create/use/destroy)

```bash
make run
```

**Expected output:**
```
Calling fun() on nc1:
Hello from native
Calling fun() on nc2:
Hello from native
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
