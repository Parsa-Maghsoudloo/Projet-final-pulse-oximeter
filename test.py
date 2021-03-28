from sympy import nsolve
from sympy import var
from scipy.interpolate import CubicSpline
import numpy as np
import matplotlib.pyplot as plt

Rh = 0.6700816636311964
Rn = 0.6695165810900068
Rref = 0.4

M1 = [[Rref ** 2, Rref, 1], [Rn ** 2, Rn, 1], [1 ** 2, 1, 1]]
M2 = [[Rref ** 2, Rref, 1], [Rh ** 2, Rh, 1], [1 ** 2, 1, 1]]

RES1 = [1, 0.968692, 0.85]
RES2 = [1, 0.967983, 0.85]

COEFF1 = np.linalg.solve(M1, RES1)
COEFF2 = np.linalg.solve(M2, RES2)

a = (COEFF1[0] + COEFF2[0])/2
b = (COEFF1[1] + COEFF2[1])/2
c = (COEFF1[2] + COEFF2[2])/2
x = np.linspace(0.4, 1, 500)

plt.plot(x, a * x ** 2 + b * x + c)
plt.show()

print(a, b, c)