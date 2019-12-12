import matplotlib.pyplot as plt
import numpy as np

fonts = {
    "font.family": "serif",
    "axes.labelsize": 10,
    "font.size": 10,
    "legend.fontsize": 10,
    "xtick.labelsize": 10,
    "ytick.labelsize": 10,
}

plt.rcParams.update(fonts)

filename_verlet = "simulation_Sun_Earthverlet"
filename_euler = "simulation_Sun_Eartheuler"

years = 2
stepsperYr = np.array([100, 500, 1000, 1500, 2000, 3000, 4000])
NperYr = years * stepsperYr

dt = 1 / np.array(NperYr)
sun_init_x = -0.00000302599
sun_init_y = 0.0

earth_init_x = 0.99999697
earth_init_y = 0.0



verlet_r = []
euler_r = []
for i in range(7):
    # print(i)
    x_coords_verlet = np.loadtxt(
        f"datafiles/filestaskc/x_{filename_verlet}{i}.txt", skiprows=2
    )
    y_coords_verlet = np.loadtxt(
        f"datafiles/filestaskc/y_{filename_verlet}{i}.txt", skiprows=2
    )
    z_coords_verlet = np.loadtxt(
        f"datafiles/filestaskc/z_{filename_verlet}{i}.txt", skiprows=2
    )

    x_coords_euler = np.loadtxt(
        f"datafiles/filestaskc/x_{filename_euler}{i}.txt", skiprows=2
    )
    y_coords_euler = np.loadtxt(
        f"datafiles/filestaskc/y_{filename_euler}{i}.txt", skiprows=2
    )
    z_coords_euler = np.loadtxt(
        f"datafiles/filestaskc/z_{filename_euler}{i}.txt", skiprows=2
    )

    a_verlet = x_coords_verlet[
        np.where(np.logical_and(x_coords_verlet[:, 1] > 0, y_coords_verlet[:, 1] < 0)),
        1,
    ]
    a_verlet = a_verlet[0]

    a_euler = x_coords_euler[
        np.where(np.logical_and(x_coords_euler[:, 1] > 0, y_coords_euler[:, 1] < 0)), 1
    ]
    a_euler = a_euler[0]

    verlet_r.append(np.abs(np.max(a_verlet) - earth_init_x))
    euler_r.append(np.abs(np.max(a_euler) - earth_init_x))
    #ax.plot(x_coords_verlet[:, 1], y_coords_verlet[:, 1])

fig, ax = plt.subplots(1, 2, figsize=[7.1014, 7.1014/1.618])
ax = ax.ravel()
ax[0].plot(dt, verlet_r, "ro", label="verlet")
ax[1].plot(dt, euler_r, "bo", label="euler")
ax[0].legend()
ax[1].legend()
ax[0].set_xlabel("dt [Yrs]")
ax[1].set_xlabel("dt [Yrs]")
ax[0].set_ylabel("Discrepancy from circular orbit [AU]")

fig.tight_layout()
fig.savefig("../doc/Figures/taskb_errors.pdf", dpi=1000)


x_coords_verlet = np.loadtxt(
        f"datafiles/filestaskc/x_{filename_verlet}{3}.txt", skiprows=2
    )
y_coords_verlet = np.loadtxt(
        f"datafiles/filestaskc/y_{filename_verlet}{3}.txt", skiprows=2
    )
x_coords_euler = np.loadtxt(
        f"datafiles/filestaskc/x_{filename_euler}{3}.txt", skiprows=2
    )
y_coords_euler = np.loadtxt(
        f"datafiles/filestaskc/y_{filename_euler}{3}.txt", skiprows=2
    )

fig, ax = plt.subplots(figsize=[3.35289, 3.35289])
ax = ax.ravel()
ax.plot(x_coords_verlet[:, 1], y_coords_verlet[:, 1], label="Velocity Verlet")
ax.plot(x_coords_euler[:, 1], y_coords_euler[:, 1], label="Forward Euler")
ax.legend()
ax.set_xlabel("x [AU]")
ax.set_ylabel("y [AU]")
fig.tight_layout()
fig.savefig("../doc/Figures/circularcomparison.pdf", dpi=1000)
