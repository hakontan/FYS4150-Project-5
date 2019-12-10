import numpy as np 
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt 

x = np.loadtxt("x_SolarSystem.txt", skiprows = 2)
y = np.loadtxt("y_SolarSystem.txt", skiprows = 2)
z = np.loadtxt("z_SolarSystem.txt", skiprows = 2)
R_cm = np.loadtxt("R_cm_SolarSystem.txt", skiprows = 2)

labels = ["Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptun", "Pluto", "Tesla Roadster"]

fig = plt.figure()
ax = fig.add_subplot(111, projection = '3d')

for i in range(len(x[0, :])):
    ax.plot(x[:, i] - R_cm[:, 0], y[:, i] - R_cm[:, 1], z[:, i] - R_cm[:, 2])

ax.legend(labels, loc = 2)
ax.set_xlabel(r"$x$ [AU]")
ax.set_ylabel(r"$y$ [AU]")
ax.set_zlabel(r"$z$ [AU]")


fig.savefig("../doc/Figures/OuterSolarSystem.pdf", dpi = 1000)

ax.set_xlim([1.5 * np.min(x[:, -1]), 1.5 * np.max(x[:, -1])])    
ax.set_ylim([1.5 * np.min(x[:, -1]), 1.5 * np.max(x[:, -1])])
ax.set_zlim([-3, 3])

fig.savefig("../doc/Figures/InnerSolarSystem.pdf", dpi = 1000)

plt.show()