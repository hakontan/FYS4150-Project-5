#include "Nbody.h"

Nbody::Nbody(double years, int NperYr, int writenr, string filename, bool einstein, double beta) {

        N = (int) std::round(years * NperYr);
        cout << N << endl;
        dt = 1.0 / (double) NperYr;
        system = SolarSystem(filename, einstein, beta);
        datapoints = writenr;
        N_bodies = system.bodies.size();


        x_coords = arma::zeros(datapoints, N_bodies);
        y_coords = arma::zeros(datapoints, N_bodies);
        z_coords = arma::zeros(datapoints, N_bodies);

        vx_coords = arma::zeros(datapoints, N_bodies);
        vy_coords = arma::zeros(datapoints, N_bodies);
        vz_coords = arma::zeros(datapoints, N_bodies);

        V_coords = arma::zeros(datapoints, N_bodies + 1);
        K_coords = arma::zeros(datapoints, N_bodies + 1);
        l_coords = arma::zeros(datapoints, N_bodies + 1);
    }

void Nbody::forward_euler() {
    int c = 0;
    cout << datapoints << " " << N << " " << N_bodies << endl;
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

                V_coords(c, j+1) = system.bodies[j].V;
                K_coords(c, j+1) = system.bodies[j].kinetic_energy();
                l_coords(c, j+1) = system.bodies[j].angular_moment();
                V_coords(c, 0) += dt * i;
                K_coords(c, 0) += dt * i;
                l_coords(c, 0) += dt * i;
            }
        }
        if (i == c * (int) std::round(N / (double) datapoints)){
            //cout << i / ((double) N) * 100 << " % "<< endl;
            c++;
        }

    }
}

void Nbody::velocity_verlet() {

    int c = 0;
    //cout << datapoints << " " << N << " " << N_bodies << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N_bodies; j++) {
            ai_prev = system.bodies[j].F / system.bodies[j].mass;
            system.bodies[j].pos += dt * system.bodies[j].vel + 0.5 * dt * dt * ai_prev;
            system.update_force_potential();
            system.bodies[j].vel += 0.5 * dt * (ai_prev + system.bodies[j].F / system.bodies[j].mass);

            if (i == c * (int) std::round(N / (double) datapoints)) {
                //cout << c * (int) std::round(N / (double) datapoints) << endl;
                //cout << "if test" << endl;
                x_coords(c, j) = system.bodies[j].pos[0];
                y_coords(c, j) = system.bodies[j].pos[1];
                z_coords(c, j) = system.bodies[j].pos[2];
                vx_coords(c, j) = system.bodies[j].vel[0];
                vy_coords(c, j) = system.bodies[j].vel[1];
                vz_coords(c, j) = system.bodies[j].vel[2];

                V_coords(c, j+1) = system.bodies[j].V;
                K_coords(c, j+1) = system.bodies[j].kinetic_energy();
                l_coords(c, j+1) = system.bodies[j].angular_moment();
                V_coords(c, 0) += dt * i;
                K_coords(c, 0) += dt * i;
                l_coords(c, 0) += dt * i;
            }
        }
        if (i == c * (int) std::round(N / (double) datapoints)){
            c++;
            //cout << i / ((double) N) * 100 << " % "<< endl;
        }
    }
}

void Nbody::write_pos(string filename, bool binary = false){
    if (binary == true){
        cout << "write_pos if" << endl;
        x_coords.save("x_" + filename + ".bin", arma::arma_binary);
        y_coords.save("y_" + filename + ".bin", arma::arma_binary);
        z_coords.save("z_" + filename + ".bin", arma::arma_binary);
    }
    else {
        cout << "write_pos else" << endl;
        x_coords.save("x_" + filename + ".txt", arma::arma_ascii);
        y_coords.save("y_" + filename + ".txt", arma::arma_ascii);
        z_coords.save("z_" + filename + ".txt", arma::arma_ascii);
        x_coords.print();
    }
}

void Nbody::write_vel(string filename, bool binary = false){
    //cout << "write_vel" << endl;
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
