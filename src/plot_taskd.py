import numpy as np
import matplotlib.pyplot as plt


file_ending = ["025", "05", "1", "15", "2"]
beta_ending = ["2", "22", "24", "26", "28", "30"]
v_init = ["7.088", "8.42", "8.86", "9.746", "13.29"]
beta = ["2.0", "2.2", "2.4", "2.6", "2.8", "3.0"]

fig, ax = plt.subplots()

c = 0
for i in file_ending:
    x_coords= np.loadtxt(
        f"datafiles/filestaskd/x_escapevel{i}.txt", skiprows=2
    )
    y_coords = np.loadtxt(
        f"datafiles/filestaskd/y_escapevel{i}.txt", skiprows=2
    )
    z_coords = np.loadtxt(
        f"datafiles/filestaskd/z_escapevel{i}.txt", skiprows=2
    )
    ax.plot(x_coords[:, 1], y_coords[:, 1], label=fr"$v_{{init}}$={v_init[c]}AU/Yr")
    c += 1

ax.set_xlim([-200, 15])
ax.set_ylim([-15, 200])
ax.legend()
plt.show()


fig, ax = plt.subplots()
c=0
for i in beta_ending:
    x_coords= np.loadtxt(
        f"datafiles/filestaskd/x_beta_var{i}.txt", skiprows=2
    )
    y_coords = np.loadtxt(
        f"datafiles/filestaskd/y_beta_var{i}.txt", skiprows=2
    )
    z_coords = np.loadtxt(
        f"datafiles/filestaskd/z_beta_var{i}.txt", skiprows=2
    )
    ax.plot(x_coords[:, 1], y_coords[:, 1], label=fr"$\beta$={beta[c]}")
    c += 1

ax.set_xlim([-200, 15])
ax.set_ylim([-15, 200])
ax.legend()
plt.show()