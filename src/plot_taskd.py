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

file_ending = ["025", "05", "1", "15", "2"]
beta_ending = ["2", "22", "24", "26", "28", "30"]
v_init = ["7.00", "8.00", "8.86", "9.50", "11.0"]
beta = ["2.0", "2.2", "2.4", "2.6", "2.8", "3.0"]

fig, ax = plt.subplots(figsize=[3.35289, 3.35289])

c = 0
for i in file_ending:
    x_coords = np.loadtxt(f"datafiles/filestaskd/x_escapevel{i}.txt", skiprows=2)
    y_coords = np.loadtxt(f"datafiles/filestaskd/y_escapevel{i}.txt", skiprows=2)
    z_coords = np.loadtxt(f"datafiles/filestaskd/z_escapevel{i}.txt", skiprows=2)
    ax.plot(
        x_coords[:, 1], y_coords[:, 1], label=fr"$v_\mathrm{{init}}$={v_init[c]}AU/Yr"
    )
    c += 1

ax.set_xlim([-50, 15])
ax.set_ylim([-15, 50])
ax.grid()
ax.legend()
ax.set_xlabel("x [AU]")
ax.set_ylabel("y [AU]")
fig.tight_layout()
fig.savefig("../doc/Figures/espace.pdf", dpi=1000)
fig.clf()


fig, ax = plt.subplots(figsize=[3.35289, 3.35289])

for index, i in enumerate(beta_ending):
    x_coords = np.loadtxt(f"datafiles/filestaskd/x_beta_var{i}.txt", skiprows=2)
    y_coords = np.loadtxt(f"datafiles/filestaskd/y_beta_var{i}.txt", skiprows=2)
    z_coords = np.loadtxt(f"datafiles/filestaskd/z_beta_var{i}.txt", skiprows=2)
    ax.plot(x_coords[:, 1], y_coords[:, 1], label=fr"$\beta$={beta[index]}")


ax.grid()
ax.legend()
ax.set_title(r"$v_\mathrm{init}$ = 6.7 AU/Yr")
ax.set_xlabel(r"$x$ [AU]")
ax.set_ylabel(r"$y$ [AU]")
fig.tight_layout()
fig.savefig("../doc/Figures/beta.pdf", dpi=1000)
