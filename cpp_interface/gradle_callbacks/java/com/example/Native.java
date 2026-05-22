package com.example;

public class Native {
    static {
        System.loadLibrary("Native");
    }

    public static native long initNativeClass();
    public static native void destroyNativeClass(long cppClass);
    public static native void NativeClassScan(long cppClass);
    public static native void NativeClassStop(long cppClass);
    public static native void NativeClassSetListener(long cppClass, NativeListener listener);
}
