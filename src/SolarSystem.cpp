#include "SolarSystem.h"

SolarSystem::SolarSystem() {
    /*
    Empty constructor to initialize SolarSystem objects.
    */
}
SolarSystem::SolarSystem(std::vector<CelestialBody> bodies_) {
    /*
    Initialize a set of custom defined CelestialBodies. 
    ------------
    bodies: std::vector<CelestialBody>
        Vector containing celestialbody objects.
    */
    bodies = bodies_;
}
SolarSystem::SolarSystem(string filename, bool einstein_, double beta_) {
    /*
    Initialize a set of CelestialBodies with parameters read from file. 
    ------------
    filename: string
        Vector containing celestialbody objects.
    einstein_: bool
        Condition to solve equations using relativistic correction to the
        force.
    beta: double
        Exponent of the radial coordinate in the gravatiational force.
    */
    double x;
    double y;
    double z;

    einstein = einstein_;
    beta = beta_;

    double vx;
    double vy;
    double vz;


    R_cm = arma::zeros(3);
    V_cm = arma::zeros(3);

    double m;

    string name;

    std::ifstream infile(filename);
    while (infile >> name >> x >> y >> z >> vx >> vy >> vz >> m)
    {
        bodies.push_back(CelestialBody(x, y, z, vx, vy, vz, m, name));
    }
    infile.close();
    update_force_potential();

}

void SolarSystem::update_force_potential() {
    /*
    Updates the force acting on all the Celestial bodies. 
    */
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
    /*
    Updates the center of mass for the whole system. 
    */
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
    /*
    calculate the newtonian force acting on mass_i from mass_j. 
    ------------
    mass_i: double
        mass of object with index i.
    mass_j: double
        mass of object with index j.
    beta: double
        exponent of the radial term in the gravitational force.
    */
    return -(G * R * mass_i * mass_j) / std::pow(R_norm, beta + 1);
}

arma::vec SolarSystem::calculate_force_einstein(double mass_i,
                                                double mass_j,
                                                double l
                                                ) {
    /*
    calculate the newtonian force with a general relativistic correction term
    acting on mass_i from mass_j. 
    ------------
    mass_i: double
        mass of object with index i.
    mass_j: double
        mass of object with index j.
    l: double
        angular momentum of mass_i with respect to center of mass.
    */
    return -(G * R * mass_i * mass_j) / std::pow(R_norm, 3)
            * (1 + (3 * l * l / (R_norm * R_norm * C * C) ) );
}
