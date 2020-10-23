CC    = g++
FLAGS        = # -std=c++17 -Iinclude
CFLAGS       = -fPIC -g #-pedantic -Wall -Wextra -ggdb3
LDFLAGS      = -shared

DEBUGFLAGS   = -O0 -D _DEBUG
RELEASEFLAGS = -O2 -D NDEBUG -combine -fwhole-program

TARGET  = libml.so
SOURCES = linearregression.cpp#$(wildcard *.cpp)
#HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(FLAGS) $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET) $(OBJECTS)
