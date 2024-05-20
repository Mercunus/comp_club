CC=g++
CFLAGS=-c -Wall --std=c++17 -g3
LDFLAGS=
SOURCES=main.cpp CompClub.cpp Logger.cpp Table.cpp
HEADERS=CompClub.h Logger.h Table.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=club

all: $(SOURCES) $(HEADERS) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@