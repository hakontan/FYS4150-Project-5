import numpy as np
import matplotlib.pyplot as plt


x = np.loadtxt("x_SunEarthJupiter.txt", skiprows=2)
y = np.loadtxt("y_SunEarthJupiter.txt", skiprows=2)
R_cm = np.loadtxt("R_cm_SunEarthJupiter.txt", skiprows=2)

x10 = np.loadtxt("x_SunEarthJupiter10.txt", skiprows=2)
y10 = np.loadtxt("y_SunEarthJupiter10.txt", skiprows=2)
R_cm10 = np.loadtxt("R_cm_SunEarthJupiter.txt", skiprows=2)


x1000 = np.loadtxt("x_SunEarthJupiter1000.txt", skiprows=2)
y1000 = np.loadtxt("y_SunEarthJupiter1000.txt", skiprows=2)
R_cm1000 = np.loadtxt("R_cm_SunEarthJupiter.txt", skiprows=2)


fig, ax = plt.subplots()

ax.plot(x[1:, 0] - R_cm[1:, 0], y[1:, 0] - R_cm[1:, 1], label="Sun")
ax.plot(x[1:, 1] - R_cm[1:, 0], y[1:, 1] - R_cm[1:, 1], label="Earth")
ax.plot(x[1:, 2] - R_cm[1:, 0], y[1:, 2] - R_cm[1:, 1], label="Jupiter")
ax.set_xlabel(r"$x$ [AU]")
ax.set_ylabel(r"$y$ [AU]")
ax.legend(loc=0)

fig10, ax10 = plt.subplots()

ax10.plot(x10[1:, 0] - R_cm10[1:, 0], y10[1:, 0] - R_cm10[1:, 1], label="Sun")
ax10.plot(x10[1:, 1] - R_cm10[1:, 0], y10[1:, 1] - R_cm10[1:, 1], label="Earth")
ax10.plot(x10[1:, 2] - R_cm10[1:, 0], y10[1:, 2] - R_cm10[1:, 1], label="Jupiter X 10")
ax10.set_xlabel(r"$x$ [AU]")
ax10.set_ylabel(r"$y$ [AU]")
ax10.legend(loc=0)

fig1000, ax1000 = plt.subplots()

ax1000.plot(x1000[1:, 0] - R_cm1000[1:, 0], y1000[1:, 0] - R_cm1000[1:, 1], label="Sun")
ax1000.plot(
    x1000[1:, 1] - R_cm1000[1:, 0], y1000[1:, 1] - R_cm1000[1:, 1], label="Earth"
)
ax1000.plot(
    x1000[1:, 2] - R_cm1000[1:, 0],
    y1000[1:, 2] - R_cm1000[1:, 1],
    label="Jupiter X 1000",
)
ax1000.set_xlabel(r"$x$ [AU]")
ax1000.set_ylabel(r"$y$ [AU]")
ax1000.legend(loc=0)

plt.show()
