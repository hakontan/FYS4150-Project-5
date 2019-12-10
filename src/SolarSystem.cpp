#include "SolarSystem.h"

SolarSystem::SolarSystem() {

}
SolarSystem::SolarSystem(std::vector<CelestialBody> bodies_) {
    //cout << "create bodeies" << endl;
    bodies = bodies_;
}
SolarSystem::SolarSystem(string filename, bool einstein_, double beta_) {
    double x;
    double y;
    double z;

    einstein = einstein_;
    beta = beta_;

    double vx;
    double vy;
    double vz;


    arma::vec R_cm = arma::zeros(3);
    arma::vec V_cm = arma::zeros(3);

    double m;
    double total_mass;

    string name;

    std::ifstream infile(filename);
    while (infile >> name >> x >> y >> z >> vx >> vy >> vz >> m)
    {
        //cout << "bodies pushback" << endl;
        bodies.push_back(CelestialBody(x, y, z, vx, vy, vz, m, name));
        //bodies[0].pos.print();
    }
    infile.close();
    update_force_potential();
}

void SolarSystem::update_force_potential() {
    for(int i=0; i < bodies.size(); i++) {
        F = arma::zeros(3);
        V = 0;

        for(int j = 0; j < bodies.size(); j++) {
            if(i!=j) {
                R = bodies[i].pos - bodies[j].pos;

                R_norm = arma::norm(R);
                if (einstein) {
                    F += calculate_force_einstein(bodies[i].mass,
                                                  bodies[j].mass,
                                                  bodies[i].angular_moment(R_cm, V_cm)
                                                  );
                }
                else {
                    F += calculate_force_newton(bodies[i].mass,
                                         bodies[j].mass,
                                         beta
                                         );
                }
                V += -(G * bodies[i].mass * bodies[j].mass) / R_norm;
            }
        }
    bodies[i].F = F;
    bodies[i].V = V;
    }
}

void SolarSystem::update_cm() {
    R_cm = arma::zeros(3);
    V_cm = arma::zeros(3);
    total_mass = 0;
    for(int i = 0; i < bodies.size(); i++) {
        total_mass += bodies[i].mass;
        R_cm += bodies[i].pos * bodies[i].mass;
        V_cm += bodies[i].vel * bodies[i].mass;
        }
    R_cm /= total_mass;
    V_cm /= total_mass;
}

arma::vec SolarSystem::calculate_force_newton(double mass_i,
                                              double mass_j,
                                              double beta) {
    return -(G * R * mass_i * mass_j) / std::pow(R_norm, beta + 1);
}

arma::vec SolarSystem::calculate_force_einstein(double mass_i,
                                                double mass_j,
                                                double l
                                                ) {
    //cout << "jeff" << endl;
    return -(G * R * mass_i * mass_j) / std::pow(R_norm, 3)
            * (1 + (3 * l * l / (R_norm * R_norm * C * C) ) );
}
