UNAME := $(shell uname)



CPPflags= g++ -std=c++11 -O3 -Wall



LIB = -larmadillo


DATA_C = outputtaskc.out


all:	${DATA_C}

${DATA_C}:        outputtaskc.cpp CelestialBody.cpp Nbody.cpp SolarSystem.cpp
				${CPPflags} outputtaskc.cpp CelestialBody.cpp Nbody.cpp SolarSystem.cpp ${LIB} -o ${DATA_C}


clean:
		rm *.o

rmexecs:
		rm *.out
