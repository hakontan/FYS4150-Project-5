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
                  string name_) {
        pos = {x, y, z};

        vel = {vx, vy, vz};

        mass = m;
        name = name_;
    }

    double angular_moment() {
        return std::fabs(arma::norm(arma::cross(pos, vel)));
    }

    double kinetic_energy(){
        return 0.5 * mass * std::pow(arma::norm(vel), 2);
    }
};

class SolarSystem {
    private:
    arma::vec R;
    arma::vec F;
    double V;
    double R_norm;

    public:
    std::vector<CelestialBody> bodies;

    SolarSystem() {

    }
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

        std::ifstream infile(filename);
        while (infile >> name >> x >> y >> z >> vx >> vy >> vz >> m)
        {

            bodies.push_back(CelestialBody(x, y, z, vx, vy, vz, m, name));
        }
        infile.close();

        update_force_potential();


    }
    void update_force_potential() {
        cout << "haha" << endl;
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
};

class Nbody{
    public:
    arma::mat x_coords;
    arma::mat y_coords;
    arma::mat z_coords;

    arma::mat vx_coords;
    arma::mat vy_coords;
    arma::mat vz_coords;

    arma::mat V_coords;
    arma::mat K_coords;
    arma::mat l_coords;

    arma::vec a_i = arma::zeros(3);
    std::vector<CelestialBody> bodies;
    int N_bodies;
    int N;
    double dt;
    int writenr;
    int datapoints;
    SolarSystem system = SolarSystem();

    Nbody(int steps, double timesteps, int writenr, string filename) {

        N = steps;
        dt = timesteps;
        system = SolarSystem(filename);
        datapoints = (int) std::round(N / (double) writenr);
        N_bodies = system.bodies.size();

        x_coords = arma::zeros(datapoints, N_bodies);
        y_coords = arma::zeros(datapoints, N_bodies);
        z_coords = arma::zeros(datapoints, N_bodies);

        vx_coords = arma::zeros(datapoints, N_bodies);
        vy_coords = arma::zeros(datapoints, N_bodies);
        vz_coords = arma::zeros(datapoints, N_bodies);

        V_coords = arma::zeros(datapoints, N_bodies);
        K_coords = arma::zeros(datapoints, N_bodies);
        l_coords = arma::zeros(datapoints, N_bodies);
    }

    void forward_euler() {

        int c = 0;
        for (int i = 0; i < N; i++) {
        cout << datapoints << " " << N_bodies << endl;
            for (int j = 0; j < N_bodies; j++) {
                system.bodies[j].pos += dt * system.bodies[j].vel;
                system.bodies[j].vel += dt * system.bodies[j].F / system.bodies[j].mass;
                system.update_force_potential();

                if (i == c * datapoints) {
                    x_coords(i, j) = system.bodies[j].pos[0];
                    y_coords(i, j) = system.bodies[j].pos[1];
                    z_coords(i, j) = system.bodies[j].pos[2];

                    vx_coords(i, j) = system.bodies[j].vel[0];
                    vy_coords(i, j) = system.bodies[j].vel[1];
                    vz_coords(i, j) = system.bodies[j].vel[2];

                    V_coords(i, j) = system.bodies[j].V;
                    K_coords(i, j) = system.bodies[j].kinetic_energy();
                    l_coords(i, j) = system.bodies[j].angular_moment();
                    c += 1;
                }   
            }

        }
    }

    void velocity_verlet() {

        double ai_prev;
        int c = 0;
        for (int i = 0; i < N; i++) {
        cout << datapoints << " " << N_bodies << endl;
            for (int j = 0; j < N_bodies; j++) {
                ai_prev = system.bodies[j].F / system.bodies[j].mass;
                system.bodies[j].pos += dt * system.bodies[j].vel + 0.5 * dt * dt * ai_prev;
                system.update_force_potential();
                system.bodies[j].vel += 0.5 * dt * (ai_prev + ystem.bodies[j].F / system.bodies[j].mass);

                if (i == c * datapoints) {
                    x_coords(i, j) = system.bodies[j].pos[0];
                    y_coords(i, j) = system.bodies[j].pos[1];
                    z_coords(i, j) = system.bodies[j].pos[2];

                    vx_coords(i, j) = system.bodies[j].vel[0];
                    vy_coords(i, j) = system.bodies[j].vel[1];
                    vz_coords(i, j) = system.bodies[j].vel[2];

                    V_coords(i, j) = system.bodies[j].V;
                    K_coords(i, j) = system.bodies[j].kinetic_energy();
                    l_coords(i, j) = system.bodies[j].angular_moment();
                    c += 1;
                }   
            }

        }
    }

    void write_pos(string filename, bool binary = false){
        if (binary == true){
            x_coords.save("x_" + filename + ".bin", arma::arma_binary);
            y_coords.save("y_" + filename + ".bin", arma::arma_binary);
            z_coords.save("z_" + filename + ".bin", arma::arma_binary);
        }
        else {
            x_coords.save("x_" + filename + ".txt", arma::arma_ascii);
            y_coords.save("y_" + filename + ".txt", arma::arma_ascii);
            z_coords.save("z_" + filename + ".txt", arma::arma_ascii);
        }
    }

    void write_vel(string filename, bool binary = false){
        if (binary == true){
            vx_coords.save("vx_" + filename + ".bin", arma::arma_binary);
            vy_coords.save("vy_" + filename + ".bin", arma::arma_binary);
            vz_coords.save("vz_" + filename + ".bin", arma::arma_binary);
        }
        else {
            vx_coords.save("vx_" + filename, arma::arma_ascii);
            vy_coords.save("vy_" + filename, arma::arma_ascii);
            vz_coords.save("vz_" + filename, arma::arma_ascii);
        }
    }

    void write_energis_angmom(string filename, bool binary = false){
        if (binary == true){
            V_coords.save("V_" + filename + ".bin", arma::arma_binary);
            K_coords.save("K_" + filename + ".bin", arma::arma_binary);
            l_coords.save("l_" + filename + ".bin", arma::arma_binary);
        }
        else {
            V_coords.save("V_" + filename, arma::arma_ascii);
            K_coords.save("K_" + filename, arma::arma_ascii);
            l_coords.save("l_" + filename, arma::arma_ascii);
        }
    }
};

int main(int argc, char* argv[]){
    string output_filename = "simulation_";
    string input_filename = "data_";
    for (int i = 1; i < argc; i++) {
        output_filename += argv[i];
        input_filename += argv[i];
        if (i < argc - 1) {
            output_filename += "_";
            input_filename += "_";
        }
        else {
            input_filename += ".txt";
        }
    }
    cout << input_filename << "  " << output_filename << endl;
    arma::vec pos = arma::zeros(3);
    arma::vec vel = arma::zeros(3);
    double mass = 0;
    string nam = "jeff";
    CelestialBody jupiter = CelestialBody(0, 0, 0, 0, 0, 0, 0, nam);
    //cout << jupiter.mass << endl;
    //cout << jupiter.name << endl;
    //jupiter.pos.print();

    std::vector<CelestialBody> planets = {jupiter};
    /*
    SolarSystem test_system = SolarSystem(planets);
    cout << test_system.bodies[0].name << endl;
    cout << "1" << endl;
    SolarSystem jeff = SolarSystem("datafiles/planets_data.txt");
    cout << "2" << endl;
    cout << "jeff" << jeff.bodies[0].F << endl;
    cout << "3" << endl;
    */

    Nbody test = Nbody(100000, 0.00001, 2, "datafiles/planets_data.txt");
    test.forward_euler();
    test.write_pos(output_filename);

    return 0;
}
