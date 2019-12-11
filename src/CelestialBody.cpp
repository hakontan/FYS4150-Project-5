#include "CelestialBody.h"

CelestialBody::CelestialBody(double x,
                             double y,
                             double z,
                             double vx,
                             double vy,
                             double vz,
                             double m,
                             string name_) {
        /*
        Initialize a celestial body to construct a planetary system in
        solarsystem.cpp.
        ----------------
        x: double
            x coordinate for position.
        y: double
            y coordinate for position.
        z: double
            z coordinate for position.
        vx: double
            x coordinate for velocity.
        vy: double
            y coordinate for velocity.
        vz: double
            z coordinate for velocity.
        m: double
            mass of the celestial body
        name_: string
            Name of the celestial body
        */
        pos = {x, y, z};
        vel = {vx, vy, vz};

        mass = m;
        name = name_;
    }

double CelestialBody::angular_moment(arma::vec R_cm, arma::vec V_cm) {
    /*
    Calculates the angular momentum relative to the center of mass system.
    ----------------
    R_cm: double
        Distance to the center of mass from the origin.
    V_cm: double
        velocity of the center of mass relative to the origin.
    */
    return std::fabs(arma::norm(arma::cross(pos - R_cm, vel - V_cm)));
}

double CelestialBody::kinetic_energy(arma::vec V_cm){
    /*
    Calculates the kinetic energy relative to the center of mass system.
    ----------------
    V_cm: double
        velocity of the center of mass relative to the origin.
    */
    return 0.5 * mass * std::pow(arma::norm(vel - V_cm), 2);
}
