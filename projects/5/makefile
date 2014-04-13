CC=g++
CFLAGS=-Wall -Wextra
MAINFILE=main.cxx
OBJECTFILE=item.cxx stack.cxx eqMan.cxx
EXECNAME=calculator

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
