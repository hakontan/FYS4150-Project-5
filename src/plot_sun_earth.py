import sys
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

filename = "simulation_"
for index, arg in enumerate(sys.argv[1:]):
    filename += arg
    if index < len(sys.argv[1:]) - 1:
        filename += "_"



sun_init_x = -0.00000302599
sun_init_y = 0.0


earth_init_x = 0.99999697
earth_init_y = 0.0


x_coords = np.loadtxt(f"x_{filename}.txt", skiprows=2)
y_coords = np.loadtxt(f"y_{filename}.txt", skiprows=2)
z_coords = np.loadtxt(f"z_{filename}.txt", skiprows=2)

a = x_coords[np.where(np.logical_and(x_coords[:, 1] >= 0, y_coords[:, 1] <=  0)), 1]
best_index = np.argmin(np.abs(a - earth_init_x))
print(a[0])

print(a[0, best_index])

fig, ax = plt.subplots()
ax.plot(x_coords[:, 0], y_coords[:, 0], "ro", label = "Sun")
ax.plot(x_coords[:, 1], y_coords[:, 1], label = "Earth")
ax.legend(loc = 0)
ax.set_xlim([1.5 * np.min(x_coords[:, -1]), 1.5 * np.max(x_coords[:, -1])])    
ax.set_ylim([1.5 * np.min(x_coords[:, -1]), 1.5 * np.max(x_coords[:, -1])])
plt.show()

