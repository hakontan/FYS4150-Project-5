#include "SolarSystem.h"

SolarSystem::SolarSystem() {

}
SolarSystem::SolarSystem(std::vector<CelestialBody> bodies_) {
    bodies = bodies_;
}
SolarSystem::SolarSystem(string filename) {
    double x;
    double y;
    double z;

    double vx;
    double vy;
    double vz;


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
    for(int i=0; i < bodies.size(); i++) {
        F = arma::zeros(3);
        V = 0;
        for(int j=0; j < bodies.size(); j++) {
            if(i!=j) {
                R = bodies[i].pos - bodies[j].pos;
                R_norm = arma::norm(R);
                F += -(G * R * bodies[i].mass * bodies[j].mass)
                        / std::pow(R_norm, 3);
                V += -(G * bodies[j].mass) / R_norm;
            }
        }
    bodies[i].F = F;
    bodies[i].V = V;
    }
}
