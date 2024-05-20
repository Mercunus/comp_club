CC=g++
CFLAGS=-c -Wall --std=c++20
DEBUG=-g3
LDFLAGS=
SOURCES=main.cpp CompClub.cpp Logger.cpp Table.cpp
HEADERS=CompClub.h Logger.h Table.h
TEST_INPUT=test_file.txt 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=club

all: $(SOURCES) $(HEADERS) $(EXECUTABLE)
	./$(EXECUTABLE) $(TEST_INPUT)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@