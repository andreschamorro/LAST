# options
CXX						= g++
CXXFLAGS			= -O3# -fomit-frame-pointer
CPPFLAGS			= -Wall
LDFLAGS				= 
LDLIBS				= 
INCLUDES 			= -I.
SRC 					= btree.cpp main.cpp
HEADERS 			= btree.hpp
OBJS 					= btree.o

all: ksh
# targets
main.o: $(HEADERS) main.cpp
	g++ -c -g main.cpp
maintest.o: $(HEADERS) $(SRC) 
	g++ -c -g maintest.cpp
btree.o: $(HEADERS) $(SRC)
	g++ -c -g btree.cpp

ksh: main.o $(OBJS) 
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(OBJS) main.o -o $@

test: maintest.o $(OBJS) 
	$(CXX) $(INCLUDES) $(CXXFLAGS) -o $@ maintest.o $(OBJS)

distclean: clean
clean:
	$(RM) ksh btree.o main.o
