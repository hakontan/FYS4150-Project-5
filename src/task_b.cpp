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

    void set_force(arma::vec F_) {
        cout << "new" << endl;
        F_.print();
        cout << "over" << endl;
        F.print();
        F = F_;
        cout << "under" << endl;
        F.print();
    }

};

class SolarSystem {
    private:
    arma::vec R;
    arma::vec F;
    double V;

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
        
        update_force();
        
        
    }
    void update_force() {
            
        for(int i=0; i < bodies.size(); i++) {
            F = arma::zeros(3);
            V = 0;
            for(int j=0; j < bodies.size(); j++) {
                if(i!=j) {
                  R = bodies[i].pos - bodies[j].pos;
                  F += -(G * R * bodies[i].mass * bodies[j].mass)
                        / std::pow(arma::norm(R), 3);
                    
                }
            }
        cout << F(0) << endl;    
        bodies[i].F = F; //set_force(F);

        // F.print();
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
        //bodies = system.bodies;
        //cout << "jeff" << bodies[0].pos(0) << endl;
        //bodies[0].pos(0)++;
        //cout << "jeff" << bodies[0].pos(0) << endl;
        datapoints = (int) std::round(N/writenr);
        N_bodies = system.bodies.size();

        x_coords = arma::zeros(datapoints, N_bodies);
        y_coords = arma::zeros(datapoints, N_bodies);
        z_coords = arma::zeros(datapoints, N_bodies);

        vx_coords = arma::zeros(datapoints, N_bodies);
        vy_coords = arma::zeros(datapoints, N_bodies);
        vz_coords = arma::zeros(datapoints, N_bodies);
    }

    void forward_euler() {
        //double v_prev;

        int c = 0;
        cout << "no" << endl;
        /*bodies[0].pos[0] = 0;
        bodies[0].pos[1] = 0;
        bodies[0].pos[2] = 0;
        bodies[1].pos[0] = 1;
        bodies[1].pos[1] = 0;
        bodies[1].pos[2] = 0;

        bodies[1].vel[1] = 6.28;
        bodies[1].vel[0] = 0;
        bodies[1].vel[2] = 0;*/
        cout << "g" << endl;
        system.bodies[1].pos.print();

        for (int i=0; i < N; i++) {
            //cout << "updating step: " << i << endl;
            for (int j=0; j<N_bodies; j++) {
                //cout << bodies[j].name << endl;
                system.bodies[j].pos += dt * system.bodies[j].vel;
                //cout << bodies[j].pos[0] << endl;
                system.bodies[j].vel += dt * system.bodies[j].F / system.bodies[j].mass;
                //cout << "over" << endl;
                //bodies[j].F.print();
                system.update_force();
                //cout << "under" << endl;
                //bodies[j].F.print();
                //cout << bodies[j].mass << endl;
                

                x_coords(i, j) = system.bodies[j].pos[0];
                y_coords(i, j) = system.bodies[j].pos[1];
                z_coords(i, j) = system.bodies[j].pos[2];

                vx_coords(i, j) = system.bodies[j].vel[0];
                vy_coords(i, j) = system.bodies[j].vel[1];
                vz_coords(i, j) = system.bodies[j].vel[2];

                //vx_coords.save("x_coords.bin", arma_binary);
                //vy_coords.save("x_coords.bin", arma_binary);
                //vz_coords.save("x_coords.bin", arma_binary);

            }

            /*
            if (i == c * datapoints) {
                 write to matrix
                
                c += 1;
            }
            */
        }
        x_coords.save("x_coords.txt", arma::arma_ascii);
        y_coords.save("y_coords.txt", arma::arma_ascii);
        z_coords.save("z_coords.txt", arma::arma_ascii);
    }
};

int main(){
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

    Nbody test = Nbody(10000, 0.001, 1, "datafiles/planets_data.txt");
    test.forward_euler();

    return 0;
}
