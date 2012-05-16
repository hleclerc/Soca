SOURCES += \
    tests/test_loop.cpp \
    src/Soca/Com/ClientLoop.cpp \
    src/Soca/Model/Model.cpp \
    tests/MyApp.cpp \
    src/Soca/Database/Database.cpp \
    src/Soca/Model/Lst.cpp \
    src/Soca/Model/Directory.cpp \
    src/Soca/Model/ModelWithAttr.cpp

HEADERS += \
    src/Soca/Com/ClientLoop.h \
    src/Soca/Model/Model.h \
    tests/MyApp.h \
    src/Soca/Sys/BinOut.h \
    src/Soca/Database/Database.h \
    src/Soca/Model/Lst.h \
    src/Soca/Model/Directory.h \
    src/Soca/Model/ModelWithAttr.h

INCLUDEPATH += \
    src

QT += network

OTHER_FILES += \
    src/Soca/Com/ClientLoop_parser.sipe


sipe.commands = mkdir -p ext; cd ext; test -e Sipe || ( test -e ../../Sipe && ln -s `pwd`/../../Sipe . ) || git clone git@github.com:hleclerc/Sipe.git
sipe.target = sipe
QMAKE_EXTRA_TARGETS += sipe

# update_parser.depends += sipe
update_parser.commands = ext/Sipe/sipe -o ../Soca/src/Soca/Com/ClientLoop_parser.h ../Soca/src/Soca/Com/ClientLoop_parser.sipe
QMAKE_EXTRA_TARGETS += update_parser
