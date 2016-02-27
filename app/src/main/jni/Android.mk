
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE:=v8_base
LOCAL_SRC_FILES:=libs/libv8_base.a
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE:=v8_libbase
LOCAL_SRC_FILES:=libs/libv8_libbase.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:=v8_libplatform
LOCAL_SRC_FILES:=libs/libv8_libplatform.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:=v8_nosnapshot
LOCAL_SRC_FILES:=libs/libv8_nosnapshot.a
include $(PREBUILT_STATIC_LIBRARY)

#include $(CLEAR_VARS)
#LOCAL_MODULE:=icuuc
#LOCAL_SRC_FILES:=./libs/libicuuc.a
#include $(PREBUILT_STATIC_LIBRARY)

#include $(CLEAR_VARS)
#LOCAL_MODULE:=icui18n
#LOCAL_SRC_FILES:=./libs/libicui18n.a
#include $(PREBUILT_STATIC_LIBRARY)

#include $(CLEAR_VARS)
#LOCAL_MODULE:=icudata
#LOCAL_SRC_FILES:=./libs/libicudata.a
#include $(PREBUILT_STATIC_LIBRARY)

#include $(CLEAR_VARS)
#LOCAL_MODULE:=v8
#LOCAL_SRC_FILES:=./libs/libv8.so
#include $(PREBUILT_SHARED_LIBRARY)

#include $(CLEAR_VARS)
#LOCAL_MODULE:=icui18n
#LOCAL_SRC_FILES:=./libs/libicui18n.so
#include $(PREBUILT_SHARED_LIBRARY)

#include $(CLEAR_VARS)
#LOCAL_MODULE:=icuuc
#LOCAL_SRC_FILES:=./libs/libicuuc.so
#include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

# This is the target being built.
LOCAL_MODULE:= hellov8

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_CPPFLAGS+=-std=c++11
# All of the source files that we will compile.
LOCAL_SRC_FILES:= \
  hellov8.cpp

LOCAL_STATIC_LIBRARIES := v8_base v8_libbase v8_libplatform v8_nosnapshot
#LOCAL_SHARED_LIBRARIES := libicui18n libicuuc libv8
LOCAL_LDLIBS    := -llog -lz

include $(BUILD_SHARED_LIBRARY)
