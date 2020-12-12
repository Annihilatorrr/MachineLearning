TARGET  = libcool.so

output: $(TARGET)

$(TARGET): functions.o
	g++ functions.o -shared -std=c++17 -fPIC -pedantic -Wall -Wextra -o $(TARGET) -fvisibility=hidden 

functions.o: functions.cpp
	g++ -c functions.cpp -fPIC	
clean:
	-rm -f $(TARGET) functions.o
