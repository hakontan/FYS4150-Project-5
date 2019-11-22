#include "CelestialBody.h"

CelestialBody::CelestialBody(double x,
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

double CelestialBody::angular_moment() {
    return std::fabs(arma::norm(arma::cross(pos, vel)));
}

double CelestialBody::kinetic_energy(){
    return 0.5 * mass * std::pow(arma::norm(vel), 2);
}