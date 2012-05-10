SOURCES += \
    tests/test_loop.cpp \
    src/Soca/Com/ClientLoop.cpp \
    src/Soca/Model/Model.cpp \
    tests/MyApp.cpp \
    src/Soca/Sys/BinOut.cpp

HEADERS += \
    src/Soca/Com/ClientLoop.h \
    src/Soca/Model/Model.h \
    tests/MyApp.h \
    src/Soca/Sys/BinOut.h

INCLUDEPATH += \
    src

QT += network
