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

x = np.loadtxt("datafiles/filestaske/x_SunEarthJupiter.txt", skiprows=2)
y = np.loadtxt("datafiles/filestaske/y_SunEarthJupiter.txt", skiprows=2)
R_cm = np.loadtxt("datafiles/filestaske/R_cm_SunEarthJupiter.txt", skiprows=2)

x10 = np.loadtxt("datafiles/filestaske/x_SunEarthJupiter10.txt", skiprows=2)
y10 = np.loadtxt("datafiles/filestaske/y_SunEarthJupiter10.txt", skiprows=2)
R_cm10 = np.loadtxt("datafiles/filestaske/R_cm_SunEarthJupiter10.txt", skiprows=2)


x1000 = np.loadtxt("datafiles/filestaske/x_SunEarthJupiter1000.txt", skiprows=2)
y1000 = np.loadtxt("datafiles/filestaske/y_SunEarthJupiter1000.txt", skiprows=2)
R_cm1000 = np.loadtxt("datafiles/filestaske/R_cm_SunEarthJupiter1000.txt", skiprows=2)


fig, ax = plt.subplots(figsize=[3.35289, 3.35289])

ax.plot(x[1:, 0] - R_cm[1:, 0], y[1:, 0] - R_cm[1:, 1], label="Sun")
ax.plot(x[1:, 1] - R_cm[1:, 0], y[1:, 1] - R_cm[1:, 1], label="Earth")
ax.plot(x[1:, 2] - R_cm[1:, 0], y[1:, 2] - R_cm[1:, 1], label="Jupiter")

ax.set_xlabel(r"$x$ [AU]")
ax.set_ylabel(r"$y$ [AU]")
ax.grid()
ax.legend(loc=0)

fig10, ax10 = plt.subplots(figsize=[3.35289, 3.35289])

ax10.plot(x10[1:, 0] - R_cm10[1:, 0], y10[1:, 0] - R_cm10[1:, 1], label="Sun")
ax10.plot(x10[1:, 1] - R_cm10[1:, 0], y10[1:, 1] - R_cm10[1:, 1], label="Earth")
ax10.plot(x10[1:, 2] - R_cm10[1:, 0], y10[1:, 2] - R_cm10[1:, 1], label="Jupiter X 10")

ax10.set_xlabel(r"$x$ [AU]")
ax10.set_ylabel(r"$y$ [AU]")
ax10.grid()
ax10.legend(loc=0)

fig1000, ax1000 = plt.subplots(figsize=[3.35289, 3.35289])

ax1000.plot(x1000[1:, 0] - R_cm1000[1:, 0], y1000[1:, 0] - R_cm1000[1:, 1], label="Sun")
ax1000.plot(
    x1000[1:, 1] - R_cm1000[1:, 0], y1000[1:, 1] - R_cm1000[1:, 1], label="Earth"
)
ax1000.plot(
    x1000[1:, 2] - R_cm1000[1:, 0],
    y1000[1:, 2] - R_cm1000[1:, 1],
    label="Jupiter X 1000",
)

ax1000.set_xlim([-5, 20])
ax1000.set_ylim([-10, 2.5])
ax1000.set_xlabel(r"$x$ [AU]")
ax1000.set_ylabel(r"$y$ [AU]")
ax1000.grid()
ax1000.legend(loc=0)


fig.tight_layout()
fig.savefig("../doc/Figures/jupiter.pdf", dpi=1000)
fig10.tight_layout()
fig10.savefig("../doc/Figures/jupiter10.pdf", dpi=1000)
fig1000.tight_layout()
fig1000.savefig("../doc/Figures/jupiter1000.pdf", dpi=1000)
plt.show()
