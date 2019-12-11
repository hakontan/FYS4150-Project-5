import numpy as np
import matplotlib.pyplot as plt


V_verlet = np.loadtxt("datafiles/filestaskc/V_energy_verlet.txt", skiprows=2)
V_euler = np.loadtxt("datafiles/filestaskc/V_energy_euler.txt", skiprows=2)
K_verlet = np.loadtxt("datafiles/filestaskc/K_energy_verlet.txt", skiprows=2)
K_euler = np.loadtxt("datafiles/filestaskc/K_energy_euler.txt", skiprows=2)
l_verlet = np.loadtxt("datafiles/filestaskc/l_energy_verlet.txt", skiprows=2)
l_euler = np.loadtxt("datafiles/filestaskc/l_energy_euler.txt", skiprows=2)
fig, ax = plt.subplots()

ax.plot(V_verlet[:, 0], V_verlet[:, 2], label=r"$V_\mathrm{Verlet}$")
ax.plot(V_verlet[:, 0], K_verlet[:, 2], label=r"$K_\mathrm{Verlet}$")
ax.plot(
    V_verlet[:, 0],
    V_verlet[:, 2] + K_verlet[:, 2],
    label=r"$E_\mathrm{Verlet}$",
    linestyle="-.",
)
ax.plot(V_euler[:, 0], V_euler[:, 2], label=r"$V_\mathrm{Euler}$")
ax.plot(V_euler[:, 0], K_euler[:, 2], label=r"$K_\mathrm{Euler}$")
ax.plot(
    V_euler[:, 0],
    V_euler[:, 2] + K_euler[:, 2],
    label=r"$E_\mathrm{Euler}$",
    linestyle="-.",
)
ax.set_xlabel(r"Time $[\mathrm{yr}]$")
ax.set_ylabel(r"Energy $[\mathrm{M}_\odot \frac{\mathrm{AU}^2}{\mathrm{yr}^2}]$")
ax.legend(loc=0)

fig1, ax1 = plt.subplots()

ax1.plot(l_verlet[:, 0], l_verlet[:, 2], label=r"$l_\mathrm{Verlet}$")
ax1.plot(l_euler[:, 0], l_euler[:, 2], label=r"$l_\mathrm{euler}$")
ax1.legend(loc=0)
ax1.set_ylabel(r"Angular Momentum per Mass $[\frac{\mathrm{AU}^2}{\mathrm{yr}}]$")
ax1.set_xlabel(r"Time $[\mathrm{yr}]$")

plt.show()
