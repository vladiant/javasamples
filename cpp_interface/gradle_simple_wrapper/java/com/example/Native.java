package com.example;

public class Native {
    static {
        System.loadLibrary("Native");
    }

    public static native long initNativeClass();
    public static native void destroyNativeClass(long cppClass);
    public static native void NativeClassFun(long cppClass);
}
