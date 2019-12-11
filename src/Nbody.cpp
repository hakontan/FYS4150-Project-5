#include "Nbody.h"

Nbody::Nbody() {
    /*
    Empty constructor to initialize Nbody objects.
    */
}

Nbody::Nbody(double years, int NperYr, int writenr, string filename, bool einstein, double beta) {
    /*
    Initialize armadillo matrices for storing the x, y and z coordinates
    for position and velocity as well as kinetic and potential energy and 
    angular momentum for all celestial bodies.
    ------------
    years: double
        The amount of years to solve the motion of the celestial bodies for.
    NperYr: int
        Number of datapoints per year.
    writenr: int
        How many datapoints to store from the simulation.
    filename: string
        Name of the file to store the data.
    einstein: bool
        condition to solve equations using relativistic correction to the force.
        Default is false.
    beta: double
        Exponent of the radial coordinate in the gravatiational force.
        Default is set to 2.0.
    */
    N = (int) std::round(years * NperYr); // number of timesteps
    dt = 1.0 / (double) NperYr; // timestep
    

    system = SolarSystem(filename, einstein, beta);
    N_bodies = system.bodies.size();

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

Nbody::Nbody(double years, int NperYr, string filename, bool einstein) {
    /*
    Modified Nbody storing only positional coordinates and time as arma matrices.
    Used for the calculation of precession of mercury.
    ------------
    years: double
        The amount of years to solve the motion of the celestial bodies for.
    NperYr: int
        Number of datapoints per year.
    filename: string
        Name of the file to store the data.
    einstein: bool
        condition to solve equations using relativistic correction to the force.
        Default is false.
    */
    N = (int) std::round(years * NperYr);
    dt = 1.0 / (double) NperYr;
    
    system = SolarSystem(filename, einstein, 2.0);
    N_bodies = system.bodies.size();     
    x_coords = arma::zeros(1 * NperYr, N_bodies);
    y_coords = arma::zeros(1 * NperYr, N_bodies);
    z_coords = arma::zeros(1 * NperYr, N_bodies);
    center_of_mass = arma::zeros(1 * NperYr, 3);
    t = arma::zeros(2 * NperYr);
    NperYr_ = NperYr;
    years_ = years;
}


void Nbody::forward_euler() {
    /*
    Solves the motion of the celestial bodies using the forward euler method.
    */   
    int c = 0;
    int c2 = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N_bodies; j++) {

            system.bodies[j].pos += dt * system.bodies[j].vel;
            system.bodies[j].vel += dt * system.bodies[j].F / system.bodies[j].mass;
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
        }

        if (i == c2 * (int) std::round(N / (double) datapoints)){
            c2 += datapoints * 0.01;
            cout << i / ((double) N) * 100 << " % "<< endl;
        }
    }
}

void Nbody::velocity_verlet() {
    /*
    Solves the motion of the celestial bodies using the velocity-verlet method.
    */  
    int c = 0;
    int c2 = 0;
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
        }
        if (i == c2 * (int) std::round(N / (double) datapoints)){
            c2 += datapoints * 0.01;
            cout << i / ((double) N) * 100 << " % "<< endl;
        }
    }
}

void Nbody::velocity_verlet_mercury() {
    /*
    Solves the motion of the celestial bodies using the velocity-verlet method.
    This method is specialized to store the data for the first and last year
    of the calculation used in calculating the precession of mercury@s orbit
    */ 
    int c2 = 0;
    int c = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N_bodies; j++) {
            ai_prev = system.bodies[j].F / system.bodies[j].mass;
            system.bodies[j].pos += dt * system.bodies[j].vel + 0.5 * dt * dt * ai_prev;
            system.update_force_potential();

            system.bodies[j].vel += 0.5 * dt * (ai_prev + system.bodies[j].F / system.bodies[j].mass);
            system.update_cm();

            if (i < 0.5 * NperYr_) {
                x_coords(i, j) = system.bodies[j].pos[0];
                y_coords(i, j) = system.bodies[j].pos[1];
                z_coords(i, j) = system.bodies[j].pos[2];
                center_of_mass(i, 0) = system.R_cm(0);
                center_of_mass(i, 1) = system.R_cm(1);
                center_of_mass(i, 2) = system.R_cm(2);
                t(i) = i * dt;
                c = i + 1;

            }

            if (i > (years_ - 0.5) * NperYr_) {
                x_coords(c, j) = system.bodies[j].pos[0];
                y_coords(c, j) = system.bodies[j].pos[1];
                z_coords(c, j) = system.bodies[j].pos[2];
                center_of_mass(c, 0) = system.R_cm(0);
                center_of_mass(c, 1) = system.R_cm(1);
                center_of_mass(c, 2) = system.R_cm(2);
                t(c) = i * dt;
                if (j == N_bodies){
                    c++;
                }

            }
            
        }
    }
}


void Nbody::write_pos(string filename, string directory, bool binary, bool time){
    /*
    Function that writes the calculated x, y and z coordinates of the position
    to file
    ------------
    filename: string
        name of the file 
    NperYr: int
        Number of datapoints per year.
    binary: bool
        Condition to store the files as .bin or .txt.
        Defualt value is false
    time: bool
        Condition to store all timesteps used in the precession of mercury.
        default is false.
    */
    if (binary == true){
        x_coords.save(directory + "x_" + filename + ".bin", arma::arma_binary);
        y_coords.save(directory + "y_" + filename + ".bin", arma::arma_binary);
        z_coords.save(directory + "z_" + filename + ".bin", arma::arma_binary);
        center_of_mass.save(directory + "R_cm_" + filename + ".bin", arma::arma_binary);
    }
    else {
        x_coords.save(directory + "x_" + filename + ".txt", arma::arma_ascii);
        y_coords.save(directory + "y_" + filename + ".txt", arma::arma_ascii);
        z_coords.save(directory + "z_" + filename + ".txt", arma::arma_ascii);
        center_of_mass.save(directory + "R_cm_" + filename + ".txt", arma::arma_ascii);
    }

    if (time == true) {
        t.save(directory + "t_" + filename + ".txt", arma::arma_ascii);
    }
}

void Nbody::write_vel(string filename, string directory, bool binary){
    /*
    Function that writes the calculated x, y and z coordinates of the velocity
    to file
    ------------
    filename: string
        name of the file 
    NperYr: int
        Number of datapoints per year.
    filename: string
        Name of the file to store the data.
    binary: bool
        Condition to store the files as .bin or .txt.
        Defualt value is false
    */
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
    /*
    Function that writes the calculated valeus for the kinetic and potential
    energy as well as the angular momentum.
    ------------
    filename: string
        name of the file 
    NperYr: int
        Number of datapoints per year.
    binary: bool
        Condition to store the files as .bin or .txt.
        Defualt value is false
    */
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
