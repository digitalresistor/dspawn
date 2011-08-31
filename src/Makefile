CXXFLAGS=-Wall -Wextra -Wno-unused-parameter -Werror -pipe -g

all: dspawn

clean:
	/bin/rm -rf dspawn dspawn.o directory.o directory_entry.o

dspawn: dspawn.o directory.o directory_entry.o
	${CXX} dspawn.o directory.o directory_entry.o -lev -o dspawn

dspawn.o: dspawn.cc

directory.o: directory.cc directory.h directory_entry.h

directory_entry.o: directory_entry.cc directory_entry.h

