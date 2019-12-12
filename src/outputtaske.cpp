#include "CelestialBody.h"
#include "SolarSystem.h"
#include "Nbody.h"

int main(){


    int Nyr = 15;
    int NperYr = 1e5;
    int writenr = 1e4;

    Nbody Jupiter1 = Nbody(Nyr, NperYr, writenr, "datafiles/data_Sun_Earth_Jupiter.txt", false, 2);

    Jupiter1.velocity_verlet();
    Jupiter1.write_pos("SunEarthJupiter", "datafiles/filestaske/");

    Nbody Jupiter10 = Nbody(Nyr, NperYr, writenr, "datafiles/data_Sun_Earth_Jupiter10.txt", false, 2);

    Jupiter10.velocity_verlet();
    Jupiter10.write_pos("SunEarthJupiter10", "datafiles/filestaske/");

    Nbody Jupiter1000 = Nbody(Nyr, NperYr, writenr, "datafiles/data_Sun_Earth_Jupiter1000.txt", false, 2);

    Jupiter1000.velocity_verlet();
    Jupiter1000.write_pos("SunEarthJupiter1000", "datafiles/filestaske/");


    return 0;
}
