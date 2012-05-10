SOURCES += \
    tests/test_loop.cpp \
    src/Soca/Com/ClientLoop.cpp \
    src/Soca/Model/Model.cpp \
    src/Soca/Com/LoadCallback.cpp \
    tests/MyApp.cpp

HEADERS += \
    src/Soca/Com/ClientLoop.h \
    src/Soca/Model/Model.h \
    src/Soca/Com/LoadCallback.h \
    tests/MyApp.h

INCLUDEPATH += \
    src

QT += network
