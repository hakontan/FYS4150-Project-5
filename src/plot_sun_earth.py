import sys
import matplotlib.pyplot as plt
import numpy as np

filename = "simulation_"
for index, arg in enumerate(sys.argv[1:]):
    filename += arg
    if index < len(sys.argv[1:]) - 1:
        filename += "_"


x_coords = np.loadtxt(f"x_{filename}.txt", skiprows=2)
y_coords = np.loadtxt(f"y_{filename}.txt", skiprows=2)
z_coords = np.loadtxt(f"z_{filename}.txt", skiprows=2)
plt.plot(x_coords[:, 0], y_coords[:, 0], "ro")
plt.plot(x_coords[:, 1], y_coords[:, 1], "b--")
plt.plot(x_coords[:, 2], y_coords[:, 2], color = "orange", linestyle = "-.")
#plt.axis("equal")
plt.show()
