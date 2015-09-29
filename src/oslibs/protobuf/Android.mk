LOCAL_PATH := $(call my-dir)

################## Build ProtoBuf ################
include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm
LOCAL_CPPFLAGS += -frtti
LOCAL_MODULE_CLASS := STATIC_LIBRARIES
LOCAL_MODULE := protobuf
LOCAL_MODULE_FILENAME := libprotobuf
LOCAL_MODULE_TAGS := optional
LOCAL_CPP_EXTENSION := .cc

LOCAL_SRC_FILES := \
../../protobuf-2.6.1/src/google/protobuf/io/coded_stream.cc                \
../../protobuf-2.6.1/src/google/protobuf/io/strtod.cc                \
../../protobuf-2.6.1/src/google/protobuf/stubs/common.cc                   \
../../protobuf-2.6.1/src/google/protobuf/descriptor.cc                     \
../../protobuf-2.6.1/src/google/protobuf/descriptor.pb.cc                  \
../../protobuf-2.6.1/src/google/protobuf/descriptor_database.cc            \
../../protobuf-2.6.1/src/google/protobuf/dynamic_message.cc                \
../../protobuf-2.6.1/src/google/protobuf/extension_set.cc                  \
../../protobuf-2.6.1/src/google/protobuf/extension_set_heavy.cc            \
../../protobuf-2.6.1/src/google/protobuf/generated_message_reflection.cc   \
../../protobuf-2.6.1/src/google/protobuf/generated_message_util.cc         \
../../protobuf-2.6.1/src/google/protobuf/io/gzip_stream.cc                 \
../../protobuf-2.6.1/src/google/protobuf/compiler/importer.cc              \
../../protobuf-2.6.1/src/google/protobuf/message.cc                        \
../../protobuf-2.6.1/src/google/protobuf/message_lite.cc                   \
../../protobuf-2.6.1/src/google/protobuf/stubs/once.cc                     \
../../protobuf-2.6.1/src/google/protobuf/compiler/parser.cc                \
../../protobuf-2.6.1/src/google/protobuf/io/printer.cc                     \
../../protobuf-2.6.1/src/google/protobuf/reflection_ops.cc                 \
../../protobuf-2.6.1/src/google/protobuf/repeated_field.cc                 \
../../protobuf-2.6.1/src/google/protobuf/service.cc                        \
../../protobuf-2.6.1/src/google/protobuf/stubs/structurally_valid.cc       \
../../protobuf-2.6.1/src/google/protobuf/stubs/strutil.cc                  \
../../protobuf-2.6.1/src/google/protobuf/stubs/substitute.cc               \
../../protobuf-2.6.1/src/google/protobuf/text_format.cc                    \
../../protobuf-2.6.1/src/google/protobuf/io/tokenizer.cc                   \
../../protobuf-2.6.1/src/google/protobuf/unknown_field_set.cc              \
../../protobuf-2.6.1/src/google/protobuf/wire_format.cc                    \
../../protobuf-2.6.1/src/google/protobuf/wire_format_lite.cc               \
../../protobuf-2.6.1/src/google/protobuf/io/zero_copy_stream.cc            \
../../protobuf-2.6.1/src/google/protobuf/io/zero_copy_stream_impl.cc       \
../../protobuf-2.6.1/src/google/protobuf/io/zero_copy_stream_impl_lite.cc  \
../../protobuf-2.6.1/src/google/protobuf/stubs/stringprintf.cc  \

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../\
$(LOCAL_PATH)/../../protobuf-2.6.1/src\
$(LOCAL_PATH)/../../protobuf-2.6.1\
###########$(LOCAL_PATH)/../../protobuf-2.6.1/vsprojects\

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../protobuf-2.6.1/src

LOCAL_LDLIBS := -llog -lgcc 
########### -pthread

###########LOCAL_WHOLE_STATIC_LIBRARIES := gnustl_static
ifndef NDK_ROOT
include external/stlport/libstlport.mk
endif
include $(BUILD_STATIC_LIBRARY)
########### include $(BUILD_SHARED_LIBRARY)
