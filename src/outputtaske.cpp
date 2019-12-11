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
    cout << input_filename << "  " << output_filename << endl;
    arma::vec pos = arma::zeros(3);
    arma::vec vel = arma::zeros(3);
    string nam = "jeff";

    int Nyr = 15;
    int NperYr = 50000;
    int writenr = 1e4;

    Nbody Jupiter1 = Nbody(Nyr, NperYr, writenr, "datafiles/data_Sun_Earth_Jupiter.txt", false, 2);

    Jupiter1.velocity_verlet();
    Jupiter1.write_pos("SunEarthJupiter", "datafiles/filestaske");

    Nbody Jupiter10 = Nbody(Nyr, NperYr, writenr, "datafiles/data_Sun_Earth_Jupiter10.txt", false, 2);

    Jupiter10.velocity_verlet();
    Jupiter10.write_pos("SunEarthJupiter10", "datafiles/filestaske/");

    Nbody Jupiter1000 = Nbody(Nyr, NperYr, writenr, "datafiles/data_Sun_Earth_Jupiter1000.txt", false, 2);

    Jupiter1000.velocity_verlet();
    Jupiter1000.write_pos("SunEarthJupiter1000", "datafiles/filestaske/");


    return 0;
}
