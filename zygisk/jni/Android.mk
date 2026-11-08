LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := lishao_zygisk
LOCAL_SRC_FILES := main.cpp
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_LDLIBS := -llog -lstdc++
LOCAL_CPPFLAGS := -std=c++17 -fvisibility=hidden
include $(BUILD_SHARED_LIBRARY)
