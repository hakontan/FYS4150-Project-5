#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

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
#define G (4 * PI * PI)
#define C 63239.7263


struct CelestialBody {
    public:
        arma::vec pos;
        arma::vec vel;
        arma::vec F;
        double V;
        double mass;
        string name;

        CelestialBody(double x,
                      double y,
                      double z,
                      double vx,
                      double vy,
                      double vz,
                      double m,
                      string name_);


        double angular_moment();

        double kinetic_energy();
};

#endif
