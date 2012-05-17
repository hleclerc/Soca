SOURCES += \
    tests/test_loop.cpp \
    src/Soca/Com/ClientLoop.cpp \
    src/Soca/Model/Model.cpp \
    tests/MyApp.cpp \
    src/Soca/Database/Database.cpp \
    src/Soca/Model/Lst.cpp \
    src/Soca/Model/Directory.cpp \
    src/Soca/Model/ModelWithAttr.cpp \
    src/Soca/Model/Val.cpp \
    src/Soca/Model/Str.cpp \
    src/Soca/Model/Path.cpp \
    src/Soca/Model/Ptr.cpp \
    src/Soca/Model/ModelWithAttrAndName.cpp

HEADERS += \
    src/Soca/Com/ClientLoop.h \
    src/Soca/Model/Model.h \
    tests/MyApp.h \
    src/Soca/Sys/BinOut.h \
    src/Soca/Database/Database.h \
    src/Soca/Model/Lst.h \
    src/Soca/Model/Directory.h \
    src/Soca/Model/ModelWithAttr.h \
    src/Soca/Model/Val.h \
    src/Soca/Model/Str.h \
    src/Soca/Model/Path.h \
    src/Soca/Model/Ptr.h \
    src/Soca/Model/ModelWithAttrAndName.h

INCLUDEPATH += \
    src

QT += network

OTHER_FILES += \
    src/Soca/Com/ClientLoop_parser.sipe \
    update_parser.sh

