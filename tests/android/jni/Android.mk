# Changement du dossier courrant

LOCAL_PATH := $(call my-dir)

# Librairie SDL2

include $(CLEAR_VARS)

DEPENDENCIES_LIB_PATH := ../../../dependencies/android/lib/armeabi-v7a
DEPENDENCIES_INC_PATH := $(LOCAL_PATH)/../../../dependencies/android/include
DEPENDENCIES_INC_PATH += $(LOCAL_PATH)/../../../dependencies/include

PATH_TO_SDL_LIB := ${DEPENDENCIES_LIB_PATH}/libSDL2.so

PATH_TO_HX3D_LIB := ../ext/hx3d/libhx3d.so
PATH_TO_EXAMPLE_LIB := ../ext/hx3d/libtests.so

PATH_TO_INCLUDE_DIR := $(LOCAL_PATH)/include

LOCAL_MODULE := SDL2
LOCAL_SRC_FILES := ${PATH_TO_SDL_LIB}
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := hx3d
LOCAL_SRC_FILES := ${PATH_TO_HX3D_LIB}
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := tests
LOCAL_SRC_FILES := ${PATH_TO_EXAMPLE_LIB}
include $(PREBUILT_SHARED_LIBRARY)

# Fonction recursive permettant de trouver tous les fichiers d'une certaine extension

rwildcard=$(subst jni/, , $(wildcard $1$2)) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# Compilation des fichiers C++

include $(CLEAR_VARS)

LOCAL_MODULE := main
LOCAL_C_INCLUDES := ${PATH_TO_INCLUDE_DIR}
LOCAL_C_INCLUDES += ${DEPENDENCIES_INC_PATH}

LOCAL_SRC_FILES := $(call rwildcard,$(LOCAL_PATH),*.c) $(call rwildcard,$(LOCAL_PATH),*.cpp)

LOCAL_SHARED_LIBRARIES := SDL2 hx3d tests
LOCAL_LDLIBS := -lGLESv3 -llog -landroid
LOCAL_CFLAGS := -g -fexceptions

include $(BUILD_SHARED_LIBRARY)
