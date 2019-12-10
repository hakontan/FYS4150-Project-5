#include "CelestialBody.h"
#include "SolarSystem.h"
#include "Nbody.h"
#include <array>
#include <string>
#include <ctime>


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
    //cout << "Made filenames" << endl;
    //cout << input_filename << "  " << output_filename << endl;
    arma::vec pos = arma::zeros(3);
    arma::vec vel = arma::zeros(3);


    Nbody euler = Nbody();
    Nbody verlet = Nbody();
    std::array<int, 8> stepsperYr = {100, 500, 1000, 1500, 2000, 3000, 4000};
    string nr;
    //cout << "before loop" << endl;
    //cout << input_filename << endl;
    //cout << "datafiles/" + input_filename << endl;
    string directory = "datafiles/filestaskc/";
    for (int i=0; i<stepsperYr.array::size(); i++)
    {
        nr = std::to_string(i);
        //cout << nr << endl;
        euler = Nbody(2, stepsperYr[i], 100, "datafiles/" + input_filename);
        //cout << "before euler" << endl;
        euler.forward_euler();
        euler.write_pos(output_filename + "euler" + nr, directory);
        //cout << "euler" << endl;
        verlet = Nbody(2, stepsperYr[i], 100, "datafiles/" + input_filename);
        verlet.velocity_verlet();
        verlet.write_pos(output_filename + "verlet" + nr, directory);
    }


    std::clock_t t_start_verlet = std::clock();

    Nbody energy_verlet = Nbody(200, 100000, 2e5, "datafiles/" + input_filename, false, 2);
    energy_verlet.velocity_verlet();
    energy_verlet.write_energis_angmom("energy_verlet", directory);

    std::clock_t t_end_verlet = std::clock();
    double time_verlet = 1000.0 * (t_end_verlet - t_start_verlet) / CLOCKS_PER_SEC;



    std::clock_t t_start_euler = std::clock();


    Nbody energy_euler = Nbody(200, 100000, 2e5, "datafiles/" + input_filename, false, 2);
    energy_euler.forward_euler();
    energy_euler.write_energis_angmom("energy_euler", directory);

    std::clock_t t_end_euler = std::clock();
    double time_euler = 1000.0 * (t_end_euler - t_start_euler) / CLOCKS_PER_SEC;

    cout << "Time taken Verlet: " << time_verlet / 1000.0 << endl;
    cout << "Time taken Euler: " << time_euler / 1000.0 << endl;

    return 0;
}
