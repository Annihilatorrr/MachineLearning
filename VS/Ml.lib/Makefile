CC = g++
CXXFLAGS = -std=c++17 -fPIC -pedantic -Wall -Wextra
LDFLAGS      = -shared

DEBUGFLAGS   = -O0 -D _DEBUG
RELEASEFLAGS = -O2 -D NDEBUG -combine -fwhole-program

TARGET  = libml.so
PREFIX = /usr/local/bin
SOURCES = linearregression.cpp
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)
debug: CXXFLAGS +=-DDEBUG -g -ggdb3
debug: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(CXXFLAGS) $(DEBUGFLAGS) -o $(TARGET) $(OBJECTS)

install:
	install $(TAEGET) $(PREFIX)
uninstall:
	rm -rf $(PREFIX)/$(TARGET)
