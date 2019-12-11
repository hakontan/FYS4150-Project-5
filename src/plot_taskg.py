import numpy as np 
import matplotlib.pyplot as plt 
import scipy.signal as signal 

x_New = np.loadtxt("x_MercuryNewton.txt", skiprows = 2)
y_New = np.loadtxt("y_MercuryNewton.txt", skiprows = 2)
z_New = np.loadtxt("z_MercuryNewton.txt", skiprows = 2)
R_cm_New = np.loadtxt("R_cm_MercuryNewton.txt", skiprows = 2)

x_Ein = np.loadtxt("x_MercuryEinstein.txt", skiprows = 2)
y_Ein = np.loadtxt("y_MercuryEinstein.txt", skiprows = 2)
z_Ein = np.loadtxt("z_MercuryEinstein.txt", skiprows = 2)
R_cm_Ein = np.loadtxt("R_cm_MercuryEinstein.txt", skiprows = 2)

Energy = np.loadtxt("l_MercuryEinstein.txt", skiprows = 2)
t = Energy[:, 0]
"""
yr_i = (0.24052 - t).argmin()
total_i = len(x_New[:, 0])

x_p_New = []
y_p_New = []
x_p_Ein = []
y_p_Ein = []
t_New = []
t_Ein = []

print(t)


for i in range(int(round(total_i / yr_i))):
    index_New = (np.sqrt((x_New[i:i + 1, 1] - R_cm_New[i:i + 1, 0]) ** 2 + (y_New[i:i + 1, 1] - R_cm_New[i:i + 1, 1]) ** 2)).argmin()
    index_Ein = (np.sqrt((x_Ein[i:i + 1, 1] - R_cm_Ein[i:i + 1, 0]) ** 2 + (y_Ein[i:i + 1, 1] - R_cm_Ein[i:i + 1, 1]) ** 2)).argmin()
    x_p_New.append(x_New[index_New, 1] - R_cm_New[index_New, 0])
    y_p_New.append(y_New[index_New, 1] - R_cm_New[index_New, 1])
    x_p_Ein.append(x_Ein[index_Ein, 1] - R_cm_Ein[index_Ein, 0])
    y_p_Ein.append(y_Ein[index_Ein, 1] - R_cm_Ein[index_Ein, 1])
    t_New.append(t[index_New])
    t_Ein.append(t[index_Ein])


x_p_New = np.array(x_p_New)
y_p_New = np.array(y_p_New)
x_p_Ein = np.array(x_p_Ein)
y_p_Ein = np.array(y_p_Ein)


theta_New = np.pi / (3600* 180) * np.arctan(x_p_New / y_p_New)
theta_Ein = np.pi / (3600* 180) * np.arctan(x_p_Ein / y_p_Ein)
"""
R_New = np.sqrt((x_New[:, 1] - R_cm_New[:, 0]) ** 2 + (y_New[:, 1] - R_cm_New[:, 1]) ** 2)
index_p_New = signal.argrelextrema(R_New, np.less)

R_Ein = np.sqrt((x_Ein[:, 1] - R_cm_Ein[:, 0]) ** 2 + (y_Ein[:, 1] - R_cm_Ein[:, 1]) ** 2)
index_p_Ein = signal.argrelextrema(R_Ein, np.less)

theta_New = np.pi / (3600* 180) * np.arctan(x_New[index_p_New, 1] / y_New[index_p_New, 1])
theta_Ein = np.pi / (3600* 180) * np.arctan(x_Ein[index_p_Ein, 1] / y_Ein[index_p_Ein, 1])

print(R_New[index_p_New])

fig, ax = plt.subplots()

ax.plot(x_Ein[:, 1] - R_cm_Ein[:, 0], y_Ein[:, 1] - R_cm_Ein[:, 1], "r-.", label="Mercury GR")
ax.plot(x_New[:, 0] - R_cm_New[:, 0], y_New[:, 0] - R_cm_New[:, 1], "ro", label="Sun")
ax.plot(x_New[:, 1] - R_cm_New[:, 0], y_New[:, 1] - R_cm_New[:, 1], "g", label="Mercury Newtonian")
ax.set_xlabel(r"$x$ [AU]")
ax.set_ylabel(r"$y$ [AU]")
ax.legend(loc=0)

fig2, ax2 = plt.subplots()
ax2.plot(t, R_New, label=r"Newtonian $\theta_p$")
ax2.plot(t, R_Ein, label=r"GR $\theta_p$")
ax2.set_xlabel(r"$t$ [yr]")
ax2.set_ylabel(r"$\theta_p$ [arcsec]")
ax2.legend(loc=0)


fig1, ax1 = plt.subplots()
ax1.plot(t[index_p_New], theta_New[0], label=r"Newtonian $\theta_p$")
ax1.plot(t[index_p_Ein], theta_Ein[0], label=r"GR $\theta_p$")
ax1.set_xlabel(r"$t$ [yr]")
ax1.set_ylabel(r"$\theta_p$ [arcsec]")
ax1.legend(loc=0)

plt.show()