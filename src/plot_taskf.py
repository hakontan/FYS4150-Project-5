import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

xOuter = np.loadtxt("datafiles/filestaskf/x_OuterSolarSystem.txt", skiprows = 2)
yOuter = np.loadtxt("datafiles/filestaskf/y_OuterSolarSystem.txt", skiprows = 2)
zOuter = np.loadtxt("datafiles/filestaskf/z_OuterSolarSystem.txt", skiprows = 2)
R_cmOuter = np.loadtxt("datafiles/filestaskf/R_cm_OuterSolarSystem.txt", skiprows = 2)

xInner = np.loadtxt("datafiles/filestaskf/x_InnerSolarSystem.txt", skiprows = 2)
yInner = np.loadtxt("datafiles/filestaskf/y_InnerSolarSystem.txt", skiprows = 2)
zInner = np.loadtxt("datafiles/filestaskf/z_InnerSolarSystem.txt", skiprows = 2)
R_cmInner = np.loadtxt("datafiles/filestaskf/R_cm_InnerSolarSystem.txt", skiprows = 2)

labels = ["Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptun", "Pluto", "Tesla Roadster"]

fig = plt.figure()
ax = fig.add_subplot(111, projection = '3d')

print(xInner)
for i in range(len(xOuter[0, :])):
    ax.plot(xOuter[:, i] - R_cmOuter[:, 0], yOuter[:, i] - R_cmOuter[:, 1], zOuter[:, i] - R_cmOuter[:, 2])

ax.legend(labels, loc = 2)
ax.set_xlabel(r"$x$ [AU]")
ax.set_ylabel(r"$y$ [AU]")
ax.set_zlabel(r"$z$ [AU]")

fig.set_size_inches([7.1014, 7.1014/1.618])
fig.tight_layout()
fig.savefig("../doc/Figures/OuterSolarSystem.pdf", dpi = 1000)

fig1 = plt.figure()
ax1 = fig1.add_subplot(111, projection = '3d')

for i in range(len(xInner[0, :])):
    ax1.plot(xInner[:, i] - R_cmInner[:, 0], yInner[:, i] - R_cmInner[:, 1], zInner[:, i] - R_cmInner[:, 2])

ax1.legend(labels, loc = 2)
ax1.set_xlabel(r"$x$ [AU]")
ax1.set_ylabel(r"$y$ [AU]")
ax1.set_zlabel(r"$z$ [AU]")


ax1.set_xlim([-2, 2])
ax1.set_ylim([-2, 2])
ax1.set_zlim([-2, 2])

fig1.tight_layout()
fig1.savefig("../doc/Figures/InnerSolarSystem.pdf", dpi = 1000)
