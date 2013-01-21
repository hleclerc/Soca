all: src/Soca/Com/ClientLoop_parser.h

%.h: %.sipe ext/Sipe ext/Sipe/src/Sipe/Predef.sipe
	make -C ext/Sipe
	ext/Sipe/sipe -o $@ $<

ext/Sipe:
	mkdir -p ext; cd ext; test -e Sipe || ( test -e ../../Sipe && ln -s `pwd`/../../Sipe . ) || git clone git@github.com:hleclerc/Sipe.git

test_loop:
	metil_comp -Isrc tests/test_loop.cpp
	