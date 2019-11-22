#include "CelestialBody.h"
#include "SolarSystem.h"
#include "Nbody.h"
#include <array>
#include <string>


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
    //cout << input_filename << "  " << output_filename << endl;
    arma::vec pos = arma::zeros(3);
    arma::vec vel = arma::zeros(3);
    double mass = 0;
    string nam = "jeff";
    //CelestialBody jupiter = CelestialBody(0, 0, 0, 0, 0, 0, 0, nam);
    //cout << jupiter.mass << endl;
    //cout << jupiter.name << endl;
    //jupiter.pos.print();

    //std::vector<CelestialBody> planets = {jupiter};
    /*
    SolarSystem test_system = SolarSystem(planets);
    cout << test_system.bodies[0].name << endl;
    cout << "1" << endl;
    SolarSystem jeff = SolarSystem("datafiles/planets_data.txt");
    cout << "2" << endl;
    cout << "jeff" << jeff.bodies[0].F << endl;
    cout << "3" << endl;
    */
    Nbody euler = Nbody();
    Nbody verlet = Nbody();
    std::array<int, 8> stepsperYr = {100, 500, 1000, 1500, 2000, 3000 , 4000};
    string nr;

    for (int i=0; i<stepsperYr.array::size(); i++)
    {   
        nr = std::to_string(i);
        cout << nr << endl;
        euler = Nbody(2, stepsperYr[i], 100, "datafiles/" + input_filename);
        euler.forward_euler();
        euler.write_pos(output_filename + "euler" + nr);

        verlet = Nbody(2, stepsperYr[i], 100, "datafiles/" + input_filename);
        verlet.velocity_verlet();
        verlet.write_pos(output_filename + "verlet" + nr);
    }


    return 0;
}
