CXXFLAGS=-Wall -Wextra -Wno-unused-parameter -Werror -pipe -g

all: dspawn

clean:
	/bin/rm -rf dspawn dspawn.o directory.o

dspawn: dspawn.o directory.o
	${CXX} dspawn.o directory.o -lev -o dspawn

dspawn.o: dspawn.cc

directory.o: directory.cc directory.h

