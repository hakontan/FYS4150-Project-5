#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <armadillo>

using std::cout;
using std::endl;
using std::string;


#define PI  3.14159265
#define M_sun  1.99e30
#define AU_m   1.49e11
#define AUperYr  0.210945021
#define G (4 * PI * PI)



struct CelestialBody {
    public:
    arma::vec pos;
    arma::vec vel;
    arma::vec F;
    double mass;
    string name;


    CelestialBody(double x,
                  double y,
                  double z,
                  double vx,
                  double vy,
                  double vz,
                  double m,
                  string name_) {
        pos = {x, y, z};

        vel = {vx, vy, vz};

        mass = m;
        name = name_;
    }

    double angular_moment() {
        return std::fabs(arma::norm(arma::cross(pos, vel)));
    }

    void set_force(arma::vec F_) {
        F = F_;
    }

};

class SolarSystem {


    public:
    std::vector<CelestialBody> bodies;
    SolarSystem(std::vector<CelestialBody> bodies_) {
        bodies = bodies_;
    }
    SolarSystem(string filename) {
        double x;
        double y;
        double z;

        double vx;
        double vy;
        double vz;



        double m;
        string name;
        arma::vec R;
        arma::vec F;

        std::ifstream infile(filename);
        while (infile >> name >> x >> y >> z >> vx >> vy >> vz >> m)
        {

            bodies.push_back(CelestialBody(x, y, z, vx, vy, vz, m, name));
        }
        infile.close();
        for(int i=0; i < bodies.size(); i++) {
            F = arma::zeros(3);
            for(int j=0; j < bodies.size(); j++) {
                if(i!=j) {
                  R = bodies[i].pos - bodies[j].pos;
                  F += -(G * R * bodies[i].mass * bodies[j].mass)
                  / std::pow(arma::norm(R), 3);
                }
            }    
            bodies[i].set_force(F);
            cout << i << endl;
            F.print();

        }
    }
};

class Nbody{

};

int main(){
    arma::vec pos = arma::zeros(3);
    arma::vec vel = arma::zeros(3);
    double mass = 0;
    string nam = "jeff";
    CelestialBody jupiter = CelestialBody(0, 0, 0, 0, 0, 0, 0, nam);
    cout << jupiter.mass << endl;
    cout << jupiter.name << endl;
    jupiter.pos.print();

    std::vector<CelestialBody> planets = {jupiter};

    SolarSystem test_system = SolarSystem(planets);
    cout << test_system.bodies[0].name << endl;

    SolarSystem jeff = SolarSystem("datafiles/planets_data.txt");
    cout << "jeff" << jeff.bodies[1].F << endl;
    return 0;
}
