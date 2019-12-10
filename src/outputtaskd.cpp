#include "CelestialBody.h"
#include "SolarSystem.h"
#include "Nbody.h"
#include <array>
#include <string>

int main()
{

    
    string input_filename = "data_sunearth_escapevel";
    string output_filename = "escapevel"
    std::array<string, 8> filenr = {"1", "2", "3", "4", "5", "6", "7", "8"};
    string directory = "datafiles/filestaskc/";
    string nr;

    Nbody Solver = Nbody();
    for (int i=0; i<filenr.array::size(); i++)
    {   

        nr = filenr[i]
        Solver = Nbody(1000, 1000, 100, "datafiles/" + input_filename + nr + ".txt");
        Solver.velocity_verlet();
        solver.write_pos(output_filename + nr, directory)
    }

    
    
}