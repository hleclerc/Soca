#!/bin/sh

mkdir -p ext
cd ext
test -e Sipe || ( test -e ../../Sipe && ln -s `pwd`/../../Sipe . ) || git clone git@github.com:hleclerc/Sipe.git
cd ..

make -C ext/Sipe

ext/Sipe/sipe -o src/Soca/Com/ClientLoop_parser.h src/Soca/Com/ClientLoop_parser.sipe
