from scipy import linalg as la
import pylab as pl
import numpy as np

numEdges = 5
numAgents = 4

time = np.loadtxt("./log/enc_quad/log_formation.txt", usecols = [0])
X_h = np.loadtxt("./log/enc_quad/log_formation.txt", usecols = (1,2,3,4,5,6,7,8))
Z_h = np.loadtxt("./log/enc_quad/log_formation.txt", usecols = (9,10,11,12,13,14,15,16,17,18))
E_h = np.loadtxt("./log/enc_quad/log_formation.txt", usecols = (19,20,21,22,23))
V_hat_h = np.loadtxt("./log/enc_quad/log_formation.txt", usecols = (24,25,26,27,28,29,30,31))
U_h = np.loadtxt("./log/enc_quad/log_formation.txt", usecols = (32,33,34,35,36,37,38,39))
w_h = np.loadtxt("./log/enc_quad/log_formation.txt", usecols = (40,41,42))

sk = 50

time1 = np.loadtxt("./log/enc_quad/log_gnc_1.txt", usecols = [0], skiprows = sk)
X1_h = np.loadtxt("./log/enc_quad/log_gnc_1.txt", usecols = (1, 2, 3), skiprows = sk)
V1_h = np.loadtxt("./log/enc_quad/log_gnc_1.txt", usecols = (4, 5, 6), skiprows = sk)
Att1_h = np.loadtxt("./log/enc_quad/log_gnc_1.txt", usecols = (7, 8, 9), skiprows = sk)
Gps1_h = np.loadtxt("./log/enc_quad/log_gnc_1.txt", usecols = (10, 11, 12), skiprows = sk)

time2 = np.loadtxt("./log/enc_quad/log_gnc_2.txt", usecols = [0], skiprows = sk)
X2_h = np.loadtxt("./log/enc_quad/log_gnc_2.txt", usecols = (1, 2, 3), skiprows = sk)
V2_h = np.loadtxt("./log/enc_quad/log_gnc_2.txt", usecols = (4, 5, 6), skiprows = sk)
Att2_h = np.loadtxt("./log/enc_quad/log_gnc_2.txt", usecols = (7, 8, 9), skiprows = sk)
Gps2_h = np.loadtxt("./log/enc_quad/log_gnc_2.txt", usecols = (10, 11, 12), skiprows = sk)

time3 = np.loadtxt("./log/enc_quad/log_gnc_3.txt", usecols = [0], skiprows = sk)
X3_h = np.loadtxt("./log/enc_quad/log_gnc_3.txt", usecols = (1, 2, 3), skiprows = sk)
V3_h = np.loadtxt("./log/enc_quad/log_gnc_3.txt", usecols = (4, 5, 6), skiprows = sk)
Att3_h = np.loadtxt("./log/enc_quad/log_gnc_3.txt", usecols = (7, 8, 9), skiprows = sk)
Gps3_h = np.loadtxt("./log/enc_quad/log_gnc_3.txt", usecols = (10, 11, 12), skiprows = sk)

time4 = np.loadtxt("./log/enc_quad/log_gnc_4.txt", usecols = [0], skiprows = sk)
X4_h = np.loadtxt("./log/enc_quad/log_gnc_4.txt", usecols = (1, 2, 3), skiprows = sk)
V4_h = np.loadtxt("./log/enc_quad/log_gnc_4.txt", usecols = (4, 5, 6), skiprows = sk)
Att4_h = np.loadtxt("./log/enc_quad/log_gnc_4.txt", usecols = (7, 8, 9), skiprows = sk)
Gps4_h = np.loadtxt("./log/enc_quad/log_gnc_4.txt", usecols = (10, 11, 12), skiprows = sk)

pl.rcParams.update({'font.size': 20})

pl.figure(0)
for i in range(0, numEdges):
    pl.plot(time, E_h[:, i], label="$e_%i$"%(i+1))
pl.legend()
pl.grid()
pl.xlabel("Time [s]")
pl.ylabel("Error Interdistances [m]")
pl.xlim((15, 700))
pl.annotate('', xytext=(350, 400), xy=(500, 0), \
        arrowprops=dict(arrowstyle="<|-",
                  connectionstyle="arc3,rad=-0.2",
                  fc="w",color="black"))
a = pl.axes([0.3, 0.6, 0.2, 0.2])
for i in range(0, numEdges):
    pl.plot(time, E_h[:, i], label="$e_%i$"%(i+1))
pl.plot(time, 0*np.ones(np.size(time)), 'k--', linewidth = 3.0)
pl.xlim((500, 600))
pl.ylim((-5, 5))
pl.grid()
pl.xticks([])


pl.figure(1)
pl.plot(time1, V1_h[:, 0], 'k--', label="Target's $v_N$", linewidth = 3.0)
pl.plot(time1, V1_h[:, 1], 'r--', label="Target's $v_E$", linewidth = 3.0)
for i in range(1, numAgents):
    if i == 1:
        pl.plot(time, V_hat_h[:, 2*i], 'm', label="Pursuers' $\hat v_N$")
        pl.plot(time, V_hat_h[:, 2*i+1], 'b', label="Pursuers' $\hat v_E$")
    else:
        pl.plot(time, V_hat_h[:, 2*i], 'm')
        pl.plot(time, V_hat_h[:, 2*i+1], 'b')
pl.legend()
pl.grid()
pl.xlabel("Time [s]")
pl.ylabel("Velocity  [meters/sec]")
pl.xlim((1, 700))

pl.figure(2)
pl.plot(time, -V_hat_h[:, 1]*0.017*4*180/np.pi, 'k--', label="Desired $||\omega||$", linewidth = 2.0)
for i in range(0, numAgents-1):
    pl.plot(time, w_h[:, i]/2500*180/np.pi, label="$||\omega_%i||$"%(i+2))
pl.legend()
pl.grid()
pl.xlabel("Time [s]")
pl.ylabel("Angular speed [deg/sec]")
pl.xlim((15, 700))

pl.figure(3)
pl.title("Quadcopter 2")
pl.subplot(1, 2, 1)
pl.plot(time, U_h[:, 2], 'r--', label="Commanded $v_N$")
pl.plot(time2, V2_h[:, 0], 'k', label="Actual $v_N$")
pl.grid()
pl.legend()
pl.ylabel("Velocity [m/sec]")
pl.xlim((15, 700))
pl.subplot(1, 2, 2)
pl.plot(time, U_h[:, 3], 'r--', label="Commanded $v_E$")
pl.plot(time2, V2_h[:, 1], 'k', label="Actual $v_E$")
pl.legend()
pl.grid()
pl.xlim((15, 700))
pl.xlabel("Time [s]")

#pl.subplot(2, 2, 3)
#pl.plot(time2, -X2_h[:, 2], 'r', label="Actual altitude Quad 2")
#pl.plot(time, -V_hat_h[:, 1]*23.5, 'k--', label="Commanded altitude", linewidth=3.0)
#pl.grid()
#pl.legend()
#pl.xlim((1, 700))
#pl.xlabel("Time [s]")
#pl.ylabel("Altitude over ground [m]")
#pl.subplot(2, 2, 4)
#pl.plot(time2, Att2_h[:, 2]*180/np.pi, 'r', label="Actual Yaw Quad 2")
#pl.plot(time, -V_hat_h[:, 1]*45, 'k--', label="Commanded Yaw", linewidth=3.0)
#pl.grid()
#pl.legend()
#pl.xlim((1, 700))
#pl.xlabel("Time [s]")
#pl.ylabel("Yaw angle [deg]")

pl.show()
