JAVA_HOME ?= $(shell java -XshowSettings:properties -version 2>&1 | grep 'java.home' | awk '{print $$NF}')
JNI_INCLUDE = $(JAVA_HOME)/include
JNI_INCLUDE_LINUX = $(JAVA_HOME)/include/linux

CXX = g++
CXXFLAGS = -std=c++17 -fPIC -shared -I$(JNI_INCLUDE) -I$(JNI_INCLUDE_LINUX) -Icpp

BUILD_DIR = build
LIB_DIR = $(BUILD_DIR)/lib
CLASS_DIR = $(BUILD_DIR)/classes

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    LIB_NAME = libNative.dylib
    JNI_INCLUDE_PLATFORM = $(JAVA_HOME)/include/darwin
else
    LIB_NAME = libNative.so
    JNI_INCLUDE_PLATFORM = $(JAVA_HOME)/include/linux
endif

.PHONY: all clean run

all: $(LIB_DIR)/$(LIB_NAME) $(CLASS_DIR)/com/example/Main.class

$(LIB_DIR)/$(LIB_NAME): cpp/native_jni.cpp cpp/NativeClass.h
	@mkdir -p $(LIB_DIR)
	$(CXX) $(CXXFLAGS) -I$(JNI_INCLUDE_PLATFORM) -o $@ cpp/native_jni.cpp

$(CLASS_DIR)/com/example/Main.class: java/com/example/*.java
	@mkdir -p $(CLASS_DIR)
	javac -d $(CLASS_DIR) java/com/example/*.java

run: all
	java -Djava.library.path=$(LIB_DIR) -cp $(CLASS_DIR) com.example.Main

clean:
	rm -rf $(BUILD_DIR)
