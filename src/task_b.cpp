#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <armadillo>

using std::cout;
using std::endl;
using std::string;

#define M_sun = 2e30;
#define AU_m  = 1.49e11;
#define AUperYr = 0.210945021;

struct CelestialBody {
    public:
    arma::vec pos;
    arma::vec vel;
    arma::vec F;
    double mass;
    string name;


    CelestialBody(arma::vec p, arma::vec v, double m, string name_) {
        pos[0] = x;
        pos[1] = y;
        pos[2] = z;
        vel[0] = vx;
        vel[1] = vy;
        vel[2] = vz;

        pos /= AU_m;
        vel /= AUperYr;
        mass = m / M_sun;
        name = name_;
  }
    double angular_moment() {
        return std::fabs(arma::norm(arma::cross(pos, vel)));
    }

};

class SolarSystem {


    public:
    std::vector<CelestialBody> bodies;
    SolarSystem(std::vector<CelestialBody> bodies_) {
        bodies = bodies_;
    }
    SolarSystem(std::vector<string> filename) {
        double x;
        double y;
        double z;

        double vx;
        double vy;
        double vz;

        double m;
        string name;

        std:ifstream infile(filename)
        while (infile >> name >> x >> y >> z >> vx >> vy >> vz >> m)
        {   

            bodies.push_back(CelestialBody(x, y, z, vx, vy, vz, m, name))
        }
        infile.close()
            
        }

    }
};

class Nbody{

}

int main(){
    arma::vec pos = arma::zeros(3);
    arma::vec vel = arma::zeros(3);
    double mass = 0;
    string nam = "jeff";
    CelestialBody jupiter = CelestialBody(pos, vel, mass, nam);
    cout << jupiter.mass << endl;
    cout << jupiter.name << endl;
    jupiter.pos.print();

    std::vector<CelestialBody> planets = {jupiter};

    SolarSystem test_system = SolarSystem(planets);
    cout << test_system.bodies[0].name << endl;
    return 0;
}
