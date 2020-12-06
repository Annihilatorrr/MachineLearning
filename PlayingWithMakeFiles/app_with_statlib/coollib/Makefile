TARGET  = libcool.a

output: $(TARGET)

$(TARGET): functions.o
	ar rcs $(TARGET) functions.o

functions.o: functions.cpp
	g++ -c functions.cpp	
clean:
	-rm -f $(TARGET) functions.o
