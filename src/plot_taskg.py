import numpy as np 
import matplotlib.pyplot as plt 
import scipy.signal as signal 

x_Ein = np.loadtxt("datafiles/outputtaskg/x_MercuryEinsteinLarge.txt", skiprows = 2)
y_Ein = np.loadtxt("datafiles/outputtaskg/y_MercuryEinsteinLarge.txt", skiprows = 2)
R_cm_Ein = np.loadtxt("datafiles/outputtaskg/R_cm_MercuryEinsteinLarge.txt", skiprows = 2)
t_Ein = np.loadtxt("datafiles/outputtaskg/t_MercuryEinsteinLarge.txt", skiprows = 2)

x_New = np.loadtxt("datafiles/outputtaskg/x_MercuryNewtonLarge.txt", skiprows = 2)
y_New = np.loadtxt("datafiles/outputtaskg/y_MercuryNewtonLarge.txt", skiprows = 2)
R_cm_New = np.loadtxt("datafiles/outputtaskg/R_cm_MercuryNewtonLarge.txt", skiprows = 2)
t_New = np.loadtxt("datafiles/outputtaskg/t_MercuryNewtonLarge.txt", skiprows = 2)

R_New = np.sqrt((x_New[:, 1] - R_cm_New[:, 0]) ** 2 + (y_New[:, 1] - R_cm_New[:, 1]) ** 2)
index_p_New = signal.argrelextrema(R_New, np.less)
index_p_New = index_p_New[0]

R_Ein = np.sqrt((x_Ein[:, 1] - R_cm_Ein[:, 0]) ** 2 + (y_Ein[:, 1] - R_cm_Ein[:, 1]) ** 2)
index_p_Ein = signal.argrelextrema(R_Ein, np.less)
index_p_Ein = index_p_Ein[0]

print(x_New[index_p_New[-1], 1] , y_New[index_p_New[-1], 1])
print(x_Ein[index_p_Ein[-1], 1] , y_Ein[index_p_Ein[-1], 1])
theta_New_0 = 3600 * 180 / np.pi  * np.arctan(y_New[index_p_New[0], 1] / x_New[index_p_New[0], 1])
theta_New_1 = 3600 * 180 / np.pi * np.arctan(y_New[index_p_New[-1], 1] / x_New[index_p_New[-1], 1])

theta_Ein_0 = 3600* 180 / np.pi * np.arctan(y_Ein[index_p_Ein[0], 1] / x_Ein[index_p_Ein[0], 1])
theta_Ein_1 = 3600* 180 / np.pi * np.arctan(y_Ein[index_p_Ein[-1], 1] / x_Ein[index_p_Ein[-1], 1])

print(np.abs(theta_Ein_1 - theta_Ein_0), np.abs(theta_New_1 - theta_New_0))
