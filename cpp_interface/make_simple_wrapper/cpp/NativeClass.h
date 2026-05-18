#ifndef NATIVE_CLASS_H
#define NATIVE_CLASS_H

#include <cstdio>

class NativeClass {
public:
    NativeClass() {}
    ~NativeClass() {}

    void fun() {
        printf("Hello from native\n");
        fflush(stdout);
    }
};

#endif // NATIVE_CLASS_H
