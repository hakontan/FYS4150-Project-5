UNAME := $(shell uname)



CPPflags= g++ -std=c++11 -O3 -Wall



LIB = -larmadillo


DATA_C = outputtaskc.out
DATA_D = outputtaskd.out
DATA_E = outputtaske.out
DATA_F = outputtaskf.out


all:	${DATA_C} ${DATA_D} ${DATA_E} ${DATA_F}

${DATA_C}:        outputtaskc.cpp CelestialBody.cpp Nbody.cpp SolarSystem.cpp
				${CPPflags} outputtaskc.cpp CelestialBody.cpp Nbody.cpp SolarSystem.cpp ${LIB} -o ${DATA_C}

${DATA_D}:        outputtaskd.cpp CelestialBody.cpp Nbody.cpp SolarSystem.cpp
				${CPPflags} outputtaskd.cpp CelestialBody.cpp Nbody.cpp SolarSystem.cpp ${LIB} -o ${DATA_D}

${DATA_E}:        outputtaske.cpp CelestialBody.cpp Nbody.cpp SolarSystem.cpp
					${CPPflags} outputtaske.cpp CelestialBody.cpp Nbody.cpp SolarSystem.cpp ${LIB} -o ${DATA_E}


${DATA_F}:        outputtaskf.cpp CelestialBody.cpp Nbody.cpp SolarSystem.cpp
				${CPPflags} outputtaskf.cpp CelestialBody.cpp Nbody.cpp SolarSystem.cpp ${LIB} -o ${DATA_F}
clean:
		rm *.o

rmexecs:
		rm *.out
