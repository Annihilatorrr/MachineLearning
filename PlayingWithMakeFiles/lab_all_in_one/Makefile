appName = "lab_all_in_one_app"
output: functions.o lab.o
	g++ functions.o lab.o -o $(appName)

functions.o: functions.cpp
	g++ -c functions.cpp

lab.o: lab.cpp
	g++ -c lab.cpp

clean:
	rm *.o $(appName)
