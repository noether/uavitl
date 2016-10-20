from scipy import linalg as la
import pylab as pl
import numpy as np

numEdges = 5
numAgents = 4

time = np.loadtxt("./log/square_trav_quad/log_dis_for.txt", usecols = [0])
X_h = np.loadtxt("./log/square_trav_quad/log_dis_for.txt", usecols = (1,2,3,4,5,6,7,8))
Z_h = np.loadtxt("./log/square_trav_quad/log_dis_for.txt", usecols = (9,10,11,12,13,14,15,16,17,18))
E_h = np.loadtxt("./log/square_trav_quad/log_dis_for.txt", usecols = (19,20,21,22,23))
V_hat_h = np.loadtxt("./log/square_trav_quad/log_dis_for.txt", usecols = (24,25,26,27,28,29,30,31))
U_h = np.loadtxt("./log/square_trav_quad/log_dis_for.txt", usecols = (32,33,34,35,36,37,38,39))
w_h = np.loadtxt("./log/square_trav_quad/log_dis_for.txt", usecols = (40,41,42))
V_h = np.loadtxt("./log/square_trav_quad/log_dis_for.txt", usecols = (43,44,45))


sk = 50

time1 = np.loadtxt("./log/square_trav_quad/log_gnc_1.txt", usecols = [0], skiprows = sk)
X1_h = np.loadtxt("./log/square_trav_quad/log_gnc_1.txt", usecols = (1, 2, 3), skiprows = sk)
V1_h = np.loadtxt("./log/square_trav_quad/log_gnc_1.txt", usecols = (4, 5, 6), skiprows = sk)
Att1_h = np.loadtxt("./log/square_trav_quad/log_gnc_1.txt", usecols = (7, 8, 9), skiprows = sk)
Gps1_h = np.loadtxt("./log/square_trav_quad/log_gnc_1.txt", usecols = (10, 11, 12), skiprows = sk)
xi_g_1_h = np.loadtxt("./log/square_trav_quad/log_gnc_1.txt", usecols = [13], skiprows = sk)
xi_CD_1_h = np.loadtxt("./log/square_trav_quad/log_gnc_1.txt", usecols = [14], skiprows = sk)
acc1_h = np.loadtxt("./log/square_trav_quad/log_gnc_1.txt", usecols = (15, 16, 17), skiprows = sk)

time2 = np.loadtxt("./log/square_trav_quad/log_gnc_2.txt", usecols = [0], skiprows = sk)
X2_h = np.loadtxt("./log/square_trav_quad/log_gnc_2.txt", usecols = (1, 2, 3), skiprows = sk)
V2_h = np.loadtxt("./log/square_trav_quad/log_gnc_2.txt", usecols = (4, 5, 6), skiprows = sk)
Att2_h = np.loadtxt("./log/square_trav_quad/log_gnc_2.txt", usecols = (7, 8, 9), skiprows = sk)
Gps2_h = np.loadtxt("./log/square_trav_quad/log_gnc_2.txt", usecols = (10, 11, 12), skiprows = sk)
xi_g_2_h = np.loadtxt("./log/square_trav_quad/log_gnc_2.txt", usecols = [13], skiprows = sk)
xi_CD_2_h = np.loadtxt("./log/square_trav_quad/log_gnc_2.txt", usecols = [14], skiprows = sk)
acc2_h = np.loadtxt("./log/square_trav_quad/log_gnc_2.txt", usecols = (15, 16, 17), skiprows = sk)


time3 = np.loadtxt("./log/square_trav_quad/log_gnc_3.txt", usecols = [0], skiprows = sk)
X3_h = np.loadtxt("./log/square_trav_quad/log_gnc_3.txt", usecols = (1, 2, 3), skiprows = sk)
V3_h = np.loadtxt("./log/square_trav_quad/log_gnc_3.txt", usecols = (4, 5, 6), skiprows = sk)
Att3_h = np.loadtxt("./log/square_trav_quad/log_gnc_3.txt", usecols = (7, 8, 9), skiprows = sk)
Gps3_h = np.loadtxt("./log/square_trav_quad/log_gnc_3.txt", usecols = (10, 11, 12), skiprows = sk)
xi_g_3_h = np.loadtxt("./log/square_trav_quad/log_gnc_3.txt", usecols = [13], skiprows = sk)
xi_CD_3_h = np.loadtxt("./log/square_trav_quad/log_gnc_3.txt", usecols = [14], skiprows = sk)
acc3_h = np.loadtxt("./log/square_trav_quad/log_gnc_3.txt", usecols = (15, 16, 17), skiprows = sk)


time4 = np.loadtxt("./log/square_trav_quad/log_gnc_4.txt", usecols = [0], skiprows = sk)
X4_h = np.loadtxt("./log/square_trav_quad/log_gnc_4.txt", usecols = (1, 2, 3), skiprows = sk)
V4_h = np.loadtxt("./log/square_trav_quad/log_gnc_4.txt", usecols = (4, 5, 6), skiprows = sk)
Att4_h = np.loadtxt("./log/square_trav_quad/log_gnc_4.txt", usecols = (7, 8, 9), skiprows = sk)
Gps4_h = np.loadtxt("./log/square_trav_quad/log_gnc_4.txt", usecols = (10, 11, 12), skiprows = sk)
xi_g_4_h = np.loadtxt("./log/square_trav_quad/log_gnc_4.txt", usecols = [13], skiprows = sk)
xi_CD_4_h = np.loadtxt("./log/square_trav_quad/log_gnc_4.txt", usecols = [14], skiprows = sk)
acc4_h = np.loadtxt("./log/square_trav_quad/log_gnc_4.txt", usecols = (15, 16, 17), skiprows = sk)

pl.rcParams.update({'font.size': 20})

tf = 290

pl.figure(0)
for i in range(0, numEdges):
    pl.plot(time, E_h[:, i], label="$e_%i$"%(i+1))
pl.legend()
pl.grid()
pl.xlabel("Time [s]")
pl.ylabel("Error Interdistances [m]")
pl.xlim((15, tf))

pl.figure(1)
pl.title("Quadcopter 3")
pl.subplot(1, 2, 1)
pl.plot(time3, -acc3_h[:, 0], 'k', label="Actual $a_N$")
pl.plot(time, U_h[:, 4], 'r--', label="Commanded $a_N$")
pl.grid()
pl.legend()
pl.ylabel("Acceleration [m/$s^2$]")
pl.xlim((1, 120))
pl.xlabel("Time [s]")
pl.subplot(1, 2, 2)
pl.plot(time3, -acc3_h[:, 1], 'k', label="Actual $a_E$")
pl.plot(time, U_h[:, 5], 'r--', label="Commanded $a_E$")
pl.legend()
pl.grid()
pl.xlim((1, 70))
pl.xlabel("Time [s]")

#pl.subplot(2, 2, 3)
#pl.plot(time3, -X3_h[:, 2], 'r', label="Actual altitude Quad 3")
#pl.plot(time3, np.ones(np.size(time3))*23.5, 'k--', label="Commanded altitude", linewidth=3.0)
#pl.grid()
#pl.legend()
#pl.xlim((1, tf))
#pl.xlabel("Time [s]")
#pl.ylabel("Altitude over ground [m]")
#pl.subplot(2, 2, 4)
#pl.plot(time3, Att3_h[:, 2]*180/np.pi, 'r', label="Actual Yaw Quad 3")
#pl.plot(time3, np.ones(np.size(time3))*45, 'k--', label="Commanded Yaw", linewidth=3.0)
#pl.grid()
#pl.legend()
#pl.xlim((1, 290))
#pl.xlabel("Time [s]")
#pl.ylabel("Yaw angle [deg]")

pl.figure(2)
pl.plot(time2, V2_h[:, 0], 'r', label="Actual $v_N$")
pl.plot(time2, np.ones(np.size(time2))*0, 'r--', linewidth=3.0, label="Commanded $v_N$")
pl.plot(time2, V2_h[:, 1], 'k', label="Actual $v_E$")
pl.plot(time2, -np.ones(np.size(time2))*6, 'k--', linewidth=3.0, label="Commanded $v_E$")
pl.grid()
pl.legend()
pl.ylabel("Velocity [m/s]")
pl.xlim((1, tf))
pl.xlabel("Time [s]")
pl.annotate('Stationary error\n   due to Wind', xytext=(60, -12), xy=(200, -0.5), \
        arrowprops=dict(arrowstyle="-|>",
                  connectionstyle="arc3,rad=-0.2",
                  fc="w",color="black"))

pl.annotate('       Stationary error\n             due to\nnon-modelled dynamics', xytext=(180, -12), xy=(220, -5.5), \
        arrowprops=dict(arrowstyle="-|>",
                  connectionstyle="arc3,rad=-0.2",
                  fc="w",color="black"))

pl.figure(3)
pl.plot(time, Z_h[:, 0], label="$^Nz_{1_x}$")
pl.plot(time, Z_h[:, 1], label="$^Nz_{1_y}$")
pl.grid()
pl.legend(loc=4)
pl.ylabel("Relative distance [m]")
pl.xlim((15, tf))
pl.xlabel("Time [s]")

pl.show()
