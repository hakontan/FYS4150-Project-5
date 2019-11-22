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

    Nbody test = Nbody(1e5, 0.0001, 1000, "datafiles/" + input_filename);
    test.velocity_verlet();
    test.write_pos(output_filename);
            // Nbody(int steps, double timesteps, int writenr, string filename);


    return 0;
}