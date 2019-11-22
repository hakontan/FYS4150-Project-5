
import matplotlib.pyplot as plt
import numpy as np

x_coords = np.loadtxt("x_coords.txt", skiprows=2)
y_coords = np.loadtxt("y_coords.txt", skiprows=2)
z_coords = np.loadtxt("z_coords.txt", skiprows=2)
print(x_coords.shape)
plt.plot(x_coords[:, 0], y_coords[:, 0], "ro")
plt.plot(x_coords[:, 1], y_coords[:, 1], "b--")
plt.plot(x_coords[:, 2], y_coords[:, 2], color = "orange", linestyle = "-.")
plt.axis("equal")
plt.show()