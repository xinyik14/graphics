CC=g++
CFLAGS=-c -std=c++11
LIBS=-lGL -lGLU -lglut
EXECUTABLE=project1
SOURCES=main.cpp data.cpp graphics.cpp
OBJECTS=$(SOURCES:.cpp=.o)

# The following is completely generic

all: $(SOURCES) $(EXECUTABLE)
	@echo $(EXECUTABLE) has been compiled

compile:
	$(CC) $(CFLAGS) $< -o $@

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LIBS) $(OBJECTS) -o $@ 

clean:
	$(RM) *.o $(EXECUTABLE)
	@echo $(EXECUTABLE) has been cleaned
