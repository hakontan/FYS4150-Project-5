import numpy as np


def test_energy_conservation():
    V_verlet = np.loadtxt("datafiles/filestaskc/V_energy_verlet.txt", skiprows=2)
    K_verlet = np.loadtxt("datafiles/filestaskc/K_energy_verlet.txt", skiprows=2)
    tot = (V_verlet + K_verlet)[:, 1:]
    diff = np.abs(tot[1:] - tot[:1])
    assert np.isclose(diff.mean(), 0, atol=1e-5)


def test_angular_momentum_conservation():
    l_verlet = np.loadtxt("datafiles/filestaskc/l_energy_verlet.txt", skiprows=2)[:, 1:]
    diff = np.abs(l_verlet[1:] - l_verlet[1:])
    assert np.isclose(diff.sum(), 0)
