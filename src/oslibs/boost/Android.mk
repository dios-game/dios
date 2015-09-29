

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := boost_date_time
LOCAL_SRC_FILES := ../../prebuilt/lib/android/libboost_date_time-gcc-mt-s-1_55.a
LOCAL_EXPORT_CPPFLAGS := -frtti -fexceptions
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../prebuilt/inc/boost-1_55
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := boost_signals
LOCAL_SRC_FILES := ../../prebuilt/lib/android/libboost_signals-gcc-mt-s-1_55.a
LOCAL_EXPORT_CPPFLAGS := -frtti -fexceptions
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../prebuilt/inc/boost-1_55
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := boost_system
LOCAL_SRC_FILES := ../../prebuilt/lib/android/libboost_system-gcc-mt-s-1_55.a
LOCAL_EXPORT_CPPFLAGS := -frtti -fexceptions
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../prebuilt/inc/boost-1_55
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := boost_thread
LOCAL_SRC_FILES := ../../prebuilt/lib/android/libboost_thread_pthread-gcc-mt-s-1_55.a
LOCAL_EXPORT_CPPFLAGS := -frtti -fexceptions
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../prebuilt/inc/boost-1_55
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := boost_atomic
LOCAL_SRC_FILES := ../../prebuilt/lib/android/libboost_atomic-gcc-mt-s-1_55.a
LOCAL_EXPORT_CPPFLAGS := -frtti -fexceptions
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../prebuilt/inc/boost-1_55
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := boost_chrono
LOCAL_SRC_FILES := ../../prebuilt/lib/android/libboost_chrono-gcc-mt-s-1_55.a
LOCAL_EXPORT_CPPFLAGS := -frtti -fexceptions
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../prebuilt/inc/boost-1_55
include $(PREBUILT_STATIC_LIBRARY)