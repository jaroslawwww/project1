CC = g++ -std=c++11

single_cycle: functioncall.o allinstruction.o errordetect.o regfile.o
	g++ -o single_cycle functioncall.o allinstruction.o errordetect.o regfile.o
functioncall.o: functioncall.cpp allinstruction.h regfile.h
	g++ -c -g functioncall.cpp
allinstruction.o: allinstruction.cpp errordetect.h regfile.h
	g++ -c -g allinstruction.cpp
errordetect.o: errordetect.cpp regfile.h
	g++ -c -g errordetect.cpp
regfile.o: regfile.cpp
	g++ -c -g regfile.cpp
clean:
	rm -f functioncall.o allinstruction.o errordetect.o regfile.o
