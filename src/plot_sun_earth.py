import sys
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

filename = "simulation_"
for index, arg in enumerate(sys.argv[1:]):
    filename += arg
    if index < len(sys.argv[1:]) - 1:
        filename += "_"


fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

x_coords = np.loadtxt(f"x_{filename}.txt", skiprows=2)
y_coords = np.loadtxt(f"y_{filename}.txt", skiprows=2)
z_coords = np.loadtxt(f"z_{filename}.txt", skiprows=2)
ax.plot(x_coords[:, 0], y_coords[:, 0], z_coords[:, 0], "ro", label = "Sun")
ax.plot(x_coords[:, 3], y_coords[:, 3], z_coords[:, 3], label = "Earth")
ax.plot(x_coords[:, 4], y_coords[:, 4], z_coords[:, 4], label = "Mars")
ax.plot(x_coords[:, -1], y_coords[:, -1], z_coords[:, -1], label = "Tesla Roadster")
ax.legend(loc = 0)
#for i in range(1, len(sys.argv[1:]) - 1):
#    ax.plot(x_coords[:, i], y_coords[:, i], z_coords[:, i], "--")

ax.set_xlim3d([1.5 * np.min(x_coords[:, 4]), 1.5 * np.max(x_coords[:, 4])])    
ax.set_ylim3d([1.5 * np.min(x_coords[:, 4]), 1.5 * np.max(x_coords[:, 4])])
ax.set_zlim3d([1.5 * np.min(x_coords[:, 4]), 1.5 * np.max(x_coords[:, 4])])
plt.show()
