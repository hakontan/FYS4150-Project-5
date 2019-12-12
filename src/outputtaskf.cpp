#include "CelestialBody.h"
#include "SolarSystem.h"
#include "Nbody.h"

int main(int argc, char* argv[]){
    string output_filename = "simulation_";
    string input_filename = "data_";
    for (int i = 1; i < argc; i++) {
        output_filename += argv[i];
        input_filename += argv[i];
        if (i < argc - 1) {
            output_filename += "_";
            input_filename += "_";
        }
        else {
            input_filename += ".txt";
        }
    }

    int Nyr = 250;
    int NperYr = 1e5;
    int writenr = 1e5;

    Nbody OuterSolarSystem = Nbody(Nyr, NperYr, writenr, "datafiles/" + input_filename, false, 2);

    OuterSolarSystem.velocity_verlet();
    OuterSolarSystem.write_pos("OuterSolarSystem", "datafiles/filestaskf/");

    Nbody InnerSolarSystem = Nbody(5, NperYr, writenr, "datafiles/" + input_filename, false, 2);

    InnerSolarSystem.velocity_verlet();
    InnerSolarSystem.write_pos("InnerSolarSystem", "datafiles/filestaskf/");
    

    return 0;
}
