#include "Nbody.h"

Nbody::Nbody() {

}

Nbody::Nbody(double years, int NperYr, int writenr, string filename, bool einstein, double beta) {

        N = (int) std::round(years * NperYr);
        dt = 1.0 / (double) NperYr;
        //cout << dt << endl;
        system = SolarSystem(filename, einstein, beta);
        //cout << "edgd" << endl;
        //system.bodies[0].pos.print();
        N_bodies = system.bodies.size();
        //cout << "bodies " << N_bodies << endl;

        datapoints = writenr;
        
        x_coords = arma::zeros(datapoints, N_bodies);
        y_coords = arma::zeros(datapoints, N_bodies);
        z_coords = arma::zeros(datapoints, N_bodies);
        center_of_mass = arma::zeros(datapoints, 3);

        vx_coords = arma::zeros(datapoints, N_bodies);
        vy_coords = arma::zeros(datapoints, N_bodies);
        vz_coords = arma::zeros(datapoints, N_bodies);

        V_coords = arma::zeros(datapoints, N_bodies + 1);
        K_coords = arma::zeros(datapoints, N_bodies + 1);
        l_coords = arma::zeros(datapoints, N_bodies + 1);

    }

    Nbody::Nbody(double years, int NperYr, string filename) {

        N = (int) std::round(years * NperYr);
        dt = 1.0 / (double) NperYr;
        //cout << dt << endl;
        system = SolarSystem(filename, true, 2.0);
        //cout << "edgd" << endl;
        //system.bodies[0].pos.print();
        N_bodies = system.bodies.size();
        //cout << "bodies " << N_bodies << endl;

        datapoints = writenr;
        
        x_coords = arma::zeros(2 * NperYr, N_bodies);
        y_coords = arma::zeros(2 * NperYr, N_bodies);
        z_coords = arma::zeros(2 * NperYr, N_bodies);
        t = arma::zeros(2 * NperYr)
    }


void Nbody::forward_euler() {
    int c = 0;
    //cout << "chedlan" << endl;
    //cout << N_bodies << endl;
    //cout << system.bodies.size() << endl;
    //system.bodies[0].vel.print();
    //cout << datapoints << " " << N << " " << N_bodies << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N_bodies; j++) {
            //cout << "plss" << j << endl;
            //system.bodies[j].vel.print();
            //cout << "JEFF XDDD" << endl;
            system.bodies[j].pos += dt * system.bodies[j].vel;
            //cout << "jeff" << endl;
            system.bodies[j].vel += dt * system.bodies[j].F / system.bodies[j].mass;
            //cout << "jedna" << endl;
            system.update_force_potential();
            system.update_cm();

            if (i == c * (int) std::round(N / (double) datapoints)) {

                x_coords(c, j) = system.bodies[j].pos[0];
                y_coords(c, j) = system.bodies[j].pos[1];
                z_coords(c, j) = system.bodies[j].pos[2];
                vx_coords(c, j) = system.bodies[j].vel[0];
                vy_coords(c, j) = system.bodies[j].vel[1];
                vz_coords(c, j) = system.bodies[j].vel[2];

                V_coords(c, j+1) = system.bodies[j].V;
                K_coords(c, j+1) = system.bodies[j].kinetic_energy(system.V_cm);
                l_coords(c, j+1) = system.bodies[j].angular_moment(system.R_cm, system.V_cm);
                V_coords(c, 0) += dt * i;
                K_coords(c, 0) += dt * i;
                l_coords(c, 0) += dt * i;
                center_of_mass(c, 0) = system.R_cm(0);
                center_of_mass(c, 1) = system.R_cm(1);
                center_of_mass(c, 2) = system.R_cm(2);
            }
        }
        if (i == c * (int) std::round(N / (double) datapoints)){
            c++;
            cout << i / ((double) N) * 100 << " % "<< endl;
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
            system.update_cm();

            if (i == c * (int) std::round(N / (double) datapoints)) {
                x_coords(c, j) = system.bodies[j].pos[0];
                y_coords(c, j) = system.bodies[j].pos[1];
                z_coords(c, j) = system.bodies[j].pos[2];
                vx_coords(c, j) = system.bodies[j].vel[0];
                vy_coords(c, j) = system.bodies[j].vel[1];
                vz_coords(c, j) = system.bodies[j].vel[2];

                V_coords(c, j+1) = system.bodies[j].V;
                K_coords(c, j+1) = system.bodies[j].kinetic_energy(system.V_cm);
                l_coords(c, j+1) = system.bodies[j].angular_moment(system.R_cm, system.V_cm);
                V_coords(c, 0) += dt * i;
                K_coords(c, 0) += dt * i;
                l_coords(c, 0) += dt * i;
                center_of_mass(c, 0) = system.R_cm(0);
                center_of_mass(c, 1) = system.R_cm(1);
                center_of_mass(c, 2) = system.R_cm(2);
            }
        }
        if (i == c * (int) std::round(N / (double) datapoints)){
            c++;
            cout << i / ((double) N) * 100 << " % "<< endl;
        }
    }
}

void Nbody::velocity_verlet_mercury() {

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N_bodies; j++) {
            ai_prev = system.bodies[j].F / system.bodies[j].mass;
            system.bodies[j].pos += dt * system.bodies[j].vel + 0.5 * dt * dt * ai_prev;
            system.update_force_potential();

            system.bodies[j].vel += 0.5 * dt * (ai_prev + system.bodies[j].F / system.bodies[j].mass);
            system.update_cm();

            if (i < NperYr)) {
                x_coords(i, j) = system.bodies[j].pos[0];
                y_coords(i, j) = system.bodies[j].pos[1];
                z_coords(i, j) = system.bodies[j].pos[2];
                t(i) = i * dt

            }

            if (i > (years - 1 ) * NperYr) {
                x_coords(i, j) = system.bodies[j].pos[0];
                y_coords(i, j) = system.bodies[j].pos[1];
                z_coords(i, j) = system.bodies[j].pos[2];
                t(i) = i * dt

            }
        }
        if (i == c * (int) std::round(N / (double) datapoints)){
            c++;
            cout << i / ((double) N) * 100 << " % "<< endl;
        }
    }
}


void Nbody::write_pos(string filename, string directory, bool binary, bool time){
    if (binary == true){
        //cout << "write_pos if" << endl;
        x_coords.save(directory + "x_" + filename + ".bin", arma::arma_binary);
        y_coords.save(directory + "y_" + filename + ".bin", arma::arma_binary);
        z_coords.save(directory + "z_" + filename + ".bin", arma::arma_binary);
        center_of_mass.save(directory + "R_cm_" + filename + ".bin", arma::arma_binary);
    }
    else {
        //cout << "write_pos else" << endl;
        x_coords.save(directory + "x_" + filename + ".txt", arma::arma_ascii);
        y_coords.save(directory + "y_" + filename + ".txt", arma::arma_ascii);
        z_coords.save(directory + "z_" + filename + ".txt", arma::arma_ascii);
        //x_coords.print();
        center_of_mass.save(directory + "R_cm_" + filename + ".txt", arma::arma_ascii);
    }

    if (time == true) {
        t.save(directory + "t_" + filename + ".txt", arma::arma_ascii);
    }
}

void Nbody::write_vel(string filename, string directory, bool binary){
    //cout << "write_vel" << endl;
    if (binary == true){
        vx_coords.save(directory + "vx_" + filename + ".bin", arma::arma_binary);
        vy_coords.save(directory + "vy_" + filename + ".bin", arma::arma_binary);
        vz_coords.save(directory + "vz_" + filename + ".bin", arma::arma_binary);
    }
    else {
        vx_coords.save(directory + "vx_" + filename + ".txt", arma::arma_ascii);
        vy_coords.save(directory + "vy_" + filename + ".txt", arma::arma_ascii);
        vz_coords.save(directory + "vz_" + filename + ".txt", arma::arma_ascii);
    }
}

void Nbody::write_energis_angmom(string filename, string directory, bool binary){
    if (binary == true){
        V_coords.save(directory + "V_" + filename + ".bin", arma::arma_binary);
        K_coords.save(directory + "K_" + filename + ".bin", arma::arma_binary);
        l_coords.save(directory + "l_" + filename + ".bin", arma::arma_binary);
    }
    else {
        V_coords.save(directory + "V_" + filename + ".txt", arma::arma_ascii);
        K_coords.save(directory + "K_" + filename + ".txt", arma::arma_ascii);
        l_coords.save(directory + "l_" + filename + ".txt", arma::arma_ascii);
    }
}
