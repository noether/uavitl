from scipy import linalg as la
import pylab as pl
import numpy as np

sk = 50

time1 = np.loadtxt("./log/xyz_quad/log_gnc_1.txt", usecols = [0], skiprows = sk)
X1_h = np.loadtxt("./log/xyz_quad/log_gnc_1.txt", usecols = (1, 2, 3), skiprows = sk)
V1_h = np.loadtxt("./log/xyz_quad/log_gnc_1.txt", usecols = (4, 5, 6), skiprows = sk)
Att1_h = np.loadtxt("./log/xyz_quad/log_gnc_1.txt", usecols = (7, 8, 9), skiprows = sk)
Gps1_h = np.loadtxt("./log/xyz_quad/log_gnc_1.txt", usecols = (10, 11, 12), skiprows = sk)
xi_g1_h = np.loadtxt("./log/xyz_quad/log_gnc_1.txt", usecols = [13], skiprows = sk)
xi_CD1_h = np.loadtxt("./log/xyz_quad/log_gnc_1.txt", usecols = [14], skiprows = sk)

pl.figure(0)
pl.plot(time1, -X1_h[:, 2], 'r', label="Actual altitude")
pl.plot(time1, np.ones(np.size(time1))*20, 'k--', label="Commanded altitude", linewidth=3.0)
pl.grid()
pl.legend()
pl.xlim((0, 120))
pl.xlabel("Time [s]")
pl.ylabel("Altitude w.r.t. ground station [m]")

pl.figure(1)
pl.plot(time1, X1_h[:, 0], 'r', label="Actual North Pos")
pl.plot(time1, np.ones(np.size(time1))*5, 'r--', label="Commanded Norh Pos", linewidth=3.0)
pl.plot(time1, X1_h[:, 1], 'k', label="Actual East Pos")
pl.plot(time1, np.ones(np.size(time1))*-2.5, 'k--', label="Commanded East Pos", linewidth=3.0)
pl.grid()
pl.legend()
pl.xlim((0, 120))
pl.xlabel("Time [s]")
pl.ylabel("Quad Position w.r.t. ground station [m]")

pl.figure(2)
pl.plot(time1, Att1_h[:, 2]*180/np.pi, 'r', label="Actual Yaw")
pl.plot(time1, np.ones(np.size(time1))*45, 'k--', label="Commanded Yaw", linewidth=3.0)
pl.grid()
pl.legend()
pl.xlim((0, 120))
pl.xlabel("Time [s]")
pl.ylabel("Yaw angle [deg]")

pl.figure(3)
pl.plot(time1, xi_g1_h, 'r', label="$\\xi_g$")
pl.plot(time1, np.ones(np.size(time1))*9.78, 'k--', label="Gravity", linewidth=3.0)
pl.grid()
pl.legend()
pl.xlim((0, 120))
pl.xlabel("Time [s]")
pl.ylabel("$\\xi_g$ estimator value [m/$s^2$]")

pl.show()
