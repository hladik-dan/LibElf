TEMPLATE = lib
QMAKE_CXXFLAGS += -std=c++11

Debug:DESTDIR = bin/debug
Debug:OBJECTS_DIR = bin/debug/.obj
Debug:CONFIG += debug

Release:DESTDIR = bin/release
Release:OBJECTS_DIR = bin/release/.obj
Release:CONFIG += release

HEADERS += \
    src/elf_header.h \
    src/elf_identification.h \
    src/helper.h \
    src/lib_data.h \
    src/lib_elf.h \
    src/sections.h \
    src/segments.h

SOURCES += \
    src/elf_header.cpp \
    src/elf_identification.cpp \
    src/helper.cpp \
    src/lib_elf.cpp \
    src/sections.cpp \
    src/segments.cpp
