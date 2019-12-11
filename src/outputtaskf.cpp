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
    int NperYr = 1e6;
    int writenr = 1e5;

    Nbody SolarSystem = Nbody(Nyr, NperYr, writenr, "datafiles/" + input_filename, false, 2);

    SolarSystem.velocity_verlet();
    SolarSystem.write_pos("SolarSystem", "datafiles/filestaskf/");

    return 0;
}
