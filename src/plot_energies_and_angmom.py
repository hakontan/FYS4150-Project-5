import numpy as np
import matplotlib.pyplot as plt

fonts = {
    "font.family": "serif",
    "axes.labelsize": 10,
    "font.size": 10,
    "legend.fontsize": 10,
    "xtick.labelsize": 10,
    "ytick.labelsize": 10,
}

plt.rcParams.update(fonts)


V_verlet = np.loadtxt("datafiles/filestaskc/V_energy_verlet.txt", skiprows=2)
V_euler = np.loadtxt("datafiles/filestaskc/V_energy_euler.txt", skiprows=2)
K_verlet = np.loadtxt("datafiles/filestaskc/K_energy_verlet.txt", skiprows=2)
K_euler = np.loadtxt("datafiles/filestaskc/K_energy_euler.txt", skiprows=2)
l_verlet = np.loadtxt("datafiles/filestaskc/l_energy_verlet.txt", skiprows=2)
l_euler = np.loadtxt("datafiles/filestaskc/l_energy_euler.txt", skiprows=2)
fig, ax = plt.subplots(figsize=[3.35289, 3.35289])

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
ax.ticklabel_format(axis="y", style="sci", scilimits=(0, 0))
ax.legend(framealpha=0.2)
ax.grid()
fig.tight_layout()
fig.savefig("../doc/Figures/taskb_energies.pdf", dpi=1000)
fig.clf()

fig1, ax1 = plt.subplots(figsize=[3.35289, 3.35289])
ax1.plot(l_verlet[:, 0], l_verlet[:, 2], label=r"$l_\mathrm{Verlet}$")
ax1.plot(l_euler[:, 0], l_euler[:, 2], label=r"$l_\mathrm{Euler}$")
ax1.legend(loc=0)
ax1.set_ylabel(r"Angular Momentum per Mass $[\frac{\mathrm{AU}^2}{\mathrm{yr}}]$")
ax1.set_xlabel(r"Time $[\mathrm{yr}]$")
ax1.grid()
fig1.tight_layout()
fig1.savefig("../doc/Figures/taskb_angmom.pdf", dpi=1000)
