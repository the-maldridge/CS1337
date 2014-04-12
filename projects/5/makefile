CC=g++
CFLAGS=-c -Wall -Wextra
LDFLAGS=
SOURCES=main.cxx item.cxx stack.cxx
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=calculator

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(EXECUTABLE)
