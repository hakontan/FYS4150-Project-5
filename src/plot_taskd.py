import numpy as np
import matplotlib.pyplot as plt


file_ending = ["025", "05", "1", "15", "2"]

fig, ax = plt.subplots()

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
    ax.plot(x_coords[:, 1], y_coords[:, 1])


ax.set_xlim([-15, 15])
ax.set_ylim([-15, 15])
plt.show()