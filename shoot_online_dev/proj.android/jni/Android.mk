LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d-x-3.2)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d-x-3.2/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d-x-3.2/cocos)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
		   ../../Classes/SCGame.cpp

SRC_COMMON_FILES := $(wildcard $(LOCAL_PATH)/../../Classes/Account/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Common/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Effect/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Game/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Game/common/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Game/Components/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Data/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Module/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Network/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Network/netlib/compress/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Network/netlib/crypt/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Network/netlib/libjson/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Network/netlib/http/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Network/netlib/protocol/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Network/netlib/stream/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Player/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Scene/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/UI/*.cpp)
SRC_COMMON_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/Utility/*.cpp)
SRC_COMMON_FILES := $(SRC_COMMON_FILES:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES += $(SRC_COMMON_FILES)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../../cocos2d-x-3.2/external/curl/include/androidß

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)
$(call import-module,editor-support/cocostudio)
$(call import-module,curl/prebuilt/android)


# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,network)
# $(call import-module,extensions)
