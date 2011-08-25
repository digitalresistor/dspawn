CXXFLAGS=-Wall -Wextra -Wno-unused-parameter -Werror -pipe -g

all: dspawn

clean:
	/bin/rm -rf dspawn dspawn.o

dspawn: dspawn.o
	${CXX} dspawn.o -lev -o dspawn

dspawn.o: dspawn.cc


