LIBS = -L../Ml.lib -lml
CPPFLAGS = -I ../Ml.lib 
CXXLAGS = -Wall -W 
OBJFILES = main.o
TARGET   = mltest
all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CXX) $(CXXLAGS) -o $(TARGET) $(OBJFILES) $(LIBS) $(LDFLAGS)
	
clean:
	rm -f $(OBJFILES) $(TARGET) *~
