NDK_TOOLCHAIN_VERSION:=4.9

APP_PLATFORM:= android-17
APP_STL:=stlport_static
APP_CFLAGS += -Wno-error=format-security

APP_CPPFLAGS += -fexceptions -fpermissive
