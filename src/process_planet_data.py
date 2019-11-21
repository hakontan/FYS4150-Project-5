import numpy as np
import sys

planets = []
for index, arg in enumerate(sys.argv[1:]):
    planets.append(arg)
planets_data = np.zeros((len(planets), 6))
for row, planet in enumerate(planets):
    with open(f"datafiles/{planet}.txt") as infile:
        skiprow = 1
        while not "$$SOE" in infile.readline():
            skiprow += 1
    data = np.loadtxt(f"datafiles/{planet}.txt", skiprows=skiprow, max_rows=1, dtype=object, usecols=range(4, 10))
    for i in range(len(data)):
        data[i] = data[i][:-1]
    planets_data[row, :] = data.astype(np.float)
np.savetxt("datafiles/planets_data.txt", planets_data)
