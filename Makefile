CC=g++
DEBUG=-g -O0
CPPFLAGS=${DEBUG}
LDFLAGS=${DEBUG}
CXXFLAGS=-fno-implicit-templates
all: grid.o fwd_decl.o grid_test
grid.o: grid.hpp
grid_test: fwd_decl.o grid_test.o
clean:
	@-del *.o *.exe
