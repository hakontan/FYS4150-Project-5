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

double CelestialBody::angular_moment(arma::vec R_cm, arma::vec V_cm) {
    return std::fabs(arma::norm(arma::cross(pos - R_cm, vel - V_cm)));
}

double CelestialBody::kinetic_energy(arma::vec V_cm){
    return 0.5 * mass * std::pow(arma::norm(vel - V_cm), 2);
}