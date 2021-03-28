from sympy import nsolve
from sympy import var
from scipy.interpolate import CubicSpline
import numpy as np
import matplotlib.pyplot as plt


a = -0.18794074
b = 1.075176295


M = [[0.4, 1], [0.543683906533006, 1]]
RES = [1, 0.968692]
print(np.linalg.solve(M, RES))