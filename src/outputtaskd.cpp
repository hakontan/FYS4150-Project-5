#include "CelestialBody.h"
#include "SolarSystem.h"
#include "Nbody.h"
#include <array>
#include <string>

int main()
{
    string input_filename = "data_sunearth_escapevel";
    string output_filename = "escapevel";
    std::array<string, 5> filenr = {"025", "05", "1", "15", "2"};
    string directory = "datafiles/filestaskd/";
    string nr;

    Nbody Solver = Nbody();

    for (int i=0; i<filenr.array::size(); i++)
    {

        nr = filenr[i];
        Solver = Nbody(1000, 1000, 10000, "datafiles/" + input_filename + nr + ".txt");
        Solver.velocity_verlet();
        Solver.write_pos(output_filename + nr, directory);

    }

    std::array<double, 6> beta_lin = {2.0, 2.2, 2.4, 2.6, 2.8, 3.0};
    std::array<string, 6> filenr_beta = {"2", "22", "24", "26", "28", "30"};

    for (int i=0; i<beta_lin.array::size(); i++)
    {
        nr = filenr_beta[i];
        Solver = Nbody(1, 10000, 10000, "datafiles/data_sunearth_custom2.txt", false, beta_lin[i]);
        Solver.velocity_verlet();
        Solver.write_pos("beta_var" + nr, directory);

    }

    return 0;
}
