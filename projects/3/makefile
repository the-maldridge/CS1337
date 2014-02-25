CC=g++
CFLAGS=-c -Wall -Wextra
LDFLAGS=
SOURCES=main.cxx
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=grader

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

test:
	./$(EXECUTABLE)


clean:
	rm -rf $(EXECUTABLE)
