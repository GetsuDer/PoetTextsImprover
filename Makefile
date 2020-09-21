TESTDIR = Testing/
INCLUDEDIR = Include/
SOURCEDIR = Source/
OBJECTDIR = ObjectFiles/

CC = g++
CFLAGS = -Wall -Wextra -Wfloat-equal -std=c++14 -g  

.PHONY: all clean 


all: improver

improver: $(OBJECTDIR)main.o $(OBJECTDIR)input.o $(OBJECTDIR)sorting.o $(OBJECTDIR)parsing.o
	$(CC) -o improver $^ $(CFLAGS)

$(OBJECTDIR)main.o: $(SOURCEDIR)main.cpp ObjectDir
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJECTDIR)%.o: $(SOURCEDIR)%.cpp $(INCLUDEDIR)%.h ObjectDir
	$(CC) -c -o $@ $< $(CFLAGS)

ObjectDir:
	mkdir -p ObjectFiles

clean:
	rm -rf *.o ObjectFiles
