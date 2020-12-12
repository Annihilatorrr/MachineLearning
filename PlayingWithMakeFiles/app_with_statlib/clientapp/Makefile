LIBS = -L../coollib -lcool
CPPFLAGS = -I ../coollib
CXXLAGS = -Wall -W
OBJFILES = main.o
TARGET   = apptest
LD_LIBRARY_PATH="$LD_LIBRARY_PATH":../coollib
#export LD_LIBRARY_PATH

all: $(TARGET)
$(TARGET): main.o
	g++ -Wall -W  -o $(TARGET) main.o -L../coollib -lcool -static #-Wl,-rpath=../coollib

clean:
	rm -f $(OBJFILES) $(TARGET) *~
