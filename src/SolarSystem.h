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
        double beta;
        bool einstein;

        SolarSystem();
        SolarSystem(std::vector<CelestialBody> bodies_);
        SolarSystem(string filename, bool einstein_, double beta);
        void update_force_potential();
        arma::vec calculate_force_newton(double mass_i, double mass_j, double beta);
        arma::vec calculate_force_newton(double mass_i, double mass_j){return calculate_force_newton(mass_i, mass_j, 2);}

        arma::vec calculate_force_einstein(double mass_i, double mass_j, double l);

};

#endif
