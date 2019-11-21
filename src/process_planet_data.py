import numpy as np
import sys


masses = {
    "Sun": 1.989e30,
    "Mercury": 0.3302e24,
    "Venus": 4.8685e24,
    "Earth": 5.97219e24,
    "Mars": 6.4171e23,
    "Jupiter": 1898.13e24,
    "Saturn": 5.6834e26,
    "Uranus": 86.813e24,
    "Neptune": 102.413e24,
    "Pluto": 1.307e22,
}

planets = []
for index, arg in enumerate(sys.argv[1:]):
    planets.append(arg)
planets_data = np.zeros((len(planets), 8), dtype=object)
for row, planet in enumerate(planets):
    with open(f"datafiles/{planet}.txt") as infile:
        skiprow = 1
        while not "$$SOE" in infile.readline():
            skiprow += 1
    data = np.loadtxt(
        f"datafiles/{planet}.txt",
        skiprows=skiprow,
        max_rows=1,
        dtype=object,
        usecols=range(4, 10),
    )
    for i in range(len(data)):
        data[i] = data[i][:-1]
    planets_data[row, :] = np.append(np.append(planet, data), masses[planet])

print(planets_data.astype(str))
np.savetxt("datafiles/planets_data.txt", planets_data.astype(str), fmt="%s")