package com.example;

public class NativeClass {
    long cppClass;

    NativeClass() {
        this.cppClass = Native.initNativeClass();
    }

    @Override
    protected void finalize() {
        free();
    }

    private void free() {
        if (cppClass != 0) {
            Native.destroyNativeClass(cppClass);
            cppClass = 0;
        }
    }

    public void fun() {
        Native.NativeClassFun(cppClass);
    }
}
