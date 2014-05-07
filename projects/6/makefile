CC=g++
CFLAGS= -Wall -Wextra -Wuninitialized -fpermissive -O0 -g
MAINFILE=main.cxx
OBJECTFILE=singleLink.cxx node.cxx dnode.cxx doubleLink.cxx
EXECNAME=invdb

all: objects main

main: objects
	$(CC) $(CFLAGS) $(MAINFILE) -o $(EXECNAME) $(OBJECTFILE:.cxx=.o)

objects:
	$(CC) -c $(CFLAGS) $(OBJECTFILE)

clean:
	rm -rf $(EXECNAME)
	rm -rf *.o *.cxx~ *.hxx~
test:
	./$(EXECNAME)
valgrind:
	valgrind ./$(EXECNAME)
