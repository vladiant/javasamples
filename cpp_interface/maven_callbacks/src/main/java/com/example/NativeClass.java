package com.example;

public class NativeClass {
    long cppClass;
    // Keep a strong reference to the listener to prevent GC
    private NativeListener listenerRef;

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

    public void scan() {
        Native.NativeClassScan(cppClass);
    }

    public void stop() {
        Native.NativeClassStop(cppClass);
    }

    public void setListener(NativeListener listener) {
        this.listenerRef = listener;
        Native.NativeClassSetListener(cppClass, listener);
    }
}
