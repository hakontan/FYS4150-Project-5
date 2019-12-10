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

    
    
}