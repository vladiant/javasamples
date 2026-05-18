#include <jni.h>
#include "NativeClass.h"

extern "C" {

JNIEXPORT jlong JNICALL Java_com_example_Native_initNativeClass(JNIEnv* env, jclass clazz) {
    return (jlong) new NativeClass();
}

JNIEXPORT void JNICALL Java_com_example_Native_destroyNativeClass(JNIEnv* env, jclass clazz, jlong cppClass) {
    delete (NativeClass*) cppClass;
}

JNIEXPORT void JNICALL Java_com_example_Native_NativeClassFun(JNIEnv* env, jclass clazz, jlong cppClass) {
    ((NativeClass*) cppClass)->fun();
}

} // extern "C"
