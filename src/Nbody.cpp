

#include "Nbody.h"

Nbody::Nbody(int steps, double timesteps, int writenr, string filename) {

        N = steps;
        dt = timesteps;
        system = SolarSystem(filename);
        datapoints = writenr;
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

void Nbody::forward_euler() {
    int c = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N_bodies; j++) {
            system.bodies[j].pos += dt * system.bodies[j].vel;
            system.bodies[j].vel += dt * system.bodies[j].F / system.bodies[j].mass;
            system.update_force_potential();

            if (i == c * (int) std::round(N / (double) datapoints)) {

                x_coords(c, j) = system.bodies[j].pos[0];
                y_coords(c, j) = system.bodies[j].pos[1];
                z_coords(c, j) = system.bodies[j].pos[2];
                cout << j << " " << N_bodies << endl;
                vx_coords(c, j) = system.bodies[j].vel[0];
                vy_coords(c, j) = system.bodies[j].vel[1];
                vz_coords(c, j) = system.bodies[j].vel[2];

                V_coords(c, j) = system.bodies[j].V;
                K_coords(c, j) = system.bodies[j].kinetic_energy();
                l_coords(c, j) = system.bodies[j].angular_moment();

            }   
        }
        if (i == c * (int) std::round(N / (double) datapoints)){
            c++;
        }

    }
}

void Nbody::velocity_verlet() {

    int c = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N_bodies; j++) {
            ai_prev = system.bodies[j].F / system.bodies[j].mass;
            system.bodies[j].pos += dt * system.bodies[j].vel + 0.5 * dt * dt * ai_prev;
            system.update_force_potential();
            system.bodies[j].vel += 0.5 * dt * (ai_prev + system.bodies[j].F / system.bodies[j].mass);

            
            if (i == c * (int) std::round(N / (double) datapoints)) {
                x_coords(c, j) = system.bodies[j].pos[0];
                y_coords(c, j) = system.bodies[j].pos[1];
                z_coords(c, j) = system.bodies[j].pos[2];
                vx_coords(c, j) = system.bodies[j].vel[0];
                vy_coords(c, j) = system.bodies[j].vel[1];
                vz_coords(c, j) = system.bodies[j].vel[2];

                V_coords(c, j) = system.bodies[j].V;
                K_coords(c, j) = system.bodies[j].kinetic_energy();
                l_coords(c, j) = system.bodies[j].angular_moment();
            }   
        }
        if (i == c * (int) std::round(N / (double) datapoints)){
            c++;
            cout << i / ((double) N) * 100 << " % "<< endl;
        }
    }
}

void Nbody::write_pos(string filename, bool binary = false){
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

void Nbody::write_vel(string filename, bool binary = false){
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

void Nbody::write_energis_angmom(string filename, bool binary = false){
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

