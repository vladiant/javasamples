#include <jni.h>
#include "NativeClass.h"
#include <cstring>

static JavaVM* jvm = nullptr;

// JNI Listener adapter: bridges C++ Listener to Java NativeListener
class JniListener : public NativeClass::Listener {
private:
    JNIEnv* env = nullptr;
    jweak listenerRef;
    jmethodID printMethod;

public:
    JniListener(JavaVM* jvm, JNIEnv* callerEnv, jobject listener) {
        // Create a weak global reference from the calling thread
        listenerRef = callerEnv->NewWeakGlobalRef(listener);

        // Attach the current thread to the JVM for callbacks
        // In a real Android app, this would be done from a ThreadPool thread.
        // For desktop JNI, we attach from the thread that will make callbacks.
        jvm->AttachCurrentThread((void**)&env, NULL);
        if (env != NULL) {
            jobject localRef = env->NewLocalRef(listenerRef);
            if (localRef != NULL) {
                jclass clazz = env->GetObjectClass(localRef);
                printMethod = env->GetMethodID(clazz, "print", "(Ljava/lang/String;)V");
                env->DeleteLocalRef(localRef);
            }
        }
    }

    ~JniListener() {
        if (env != nullptr) {
            env->DeleteWeakGlobalRef(listenerRef);
            jvm->DetachCurrentThread();
        }
    }

    void print(const char* msg) override {
        // Re-attach since this may be called from a worker thread
        JNIEnv* callEnv = nullptr;
        int status = jvm->GetEnv((void**)&callEnv, JNI_VERSION_1_6);
        if (status == JNI_EDETACHED) {
            jvm->AttachCurrentThread((void**)&callEnv, NULL);
        }
        if (callEnv == nullptr) return;

        jobject localRef = callEnv->NewLocalRef(listenerRef);
        if (localRef != NULL) {
            jstring jMsg = callEnv->NewStringUTF(msg);
            callEnv->CallVoidMethod(localRef, printMethod, jMsg);
            callEnv->DeleteLocalRef(jMsg);
            callEnv->DeleteLocalRef(localRef);
        }

        if (status == JNI_EDETACHED) {
            jvm->DetachCurrentThread();
        }
    }
};

extern "C" {

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    jvm = vm;
    return JNI_VERSION_1_6;
}

JNIEXPORT jlong JNICALL Java_com_example_Native_initNativeClass(JNIEnv* env, jclass clazz) {
    return (jlong) new NativeClass();
}

JNIEXPORT void JNICALL Java_com_example_Native_destroyNativeClass(JNIEnv* env, jclass clazz, jlong cppClass) {
    delete (NativeClass*) cppClass;
}

JNIEXPORT void JNICALL Java_com_example_Native_NativeClassScan(JNIEnv* env, jclass clazz, jlong cppClass) {
    ((NativeClass*) cppClass)->scan();
}

JNIEXPORT void JNICALL Java_com_example_Native_NativeClassStop(JNIEnv* env, jclass clazz, jlong cppClass) {
    ((NativeClass*) cppClass)->stop();
}

JNIEXPORT void JNICALL Java_com_example_Native_NativeClassSetListener(JNIEnv* env, jclass clazz, jlong cppClass, jobject listener) {
    ((NativeClass*) cppClass)->setListener(new JniListener(jvm, env, listener));
}

} // extern "C"
