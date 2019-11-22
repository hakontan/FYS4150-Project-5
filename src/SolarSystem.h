#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "CelestialBody.h"

class SolarSystem {
    private:
        arma::vec R;
        arma::vec F;
        double V;
        double R_norm;

    public:
        std::vector<CelestialBody> bodies;

        SolarSystem();
        SolarSystem(std::vector<CelestialBody> bodies_);
        SolarSystem(string filename);
        void update_force_potential();
};

#endif