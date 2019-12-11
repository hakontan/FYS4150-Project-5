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
    int Nyr = 100;
    int NperYr = 1e6;
    int writenr = 2e7;
    
    Nbody MercuryEinstein = Nbody(Nyr, NperYr, writenr, "datafiles/" + input_filename, true, 2);
    
    MercuryEinstein.velocity_verlet();

    //MercuryEinstein.write_pos("MercuryEinsteinLarge");
    MercuryEinstein.write_energis_angmom("MercuryEinsteinLarge");
    /*
    Nbody MercuryNewton = Nbody(Nyr, NperYr, writenr, "datafiles/" + input_filename, false, 2);

    MercuryNewton.velocity_verlet();
    MercuryNewton.write_pos("MercuryNewtonLarge");
    */
    return 0;
}
