from scipy import linalg as la
import pylab as pl
import numpy as np

numEdges = 5
numAgents = 4

time = np.loadtxt("../log/square_miss/log_dis_for.txt", usecols = [0])
X_h = np.loadtxt("../log/square_miss/log_dis_for.txt", usecols = (1,2,3,4,5,6,7,8))
Z_h = np.loadtxt("../log/square_miss/log_dis_for.txt", usecols = (9,10,11,12,13,14,15,16,17,18))
E_h = np.loadtxt("../log/square_miss/log_dis_for.txt", usecols = (19,20,21,22,23))
V_hat_h = np.loadtxt("../log/square_miss/log_dis_for.txt", usecols = (24,25,26,27,28,29,30,31))
U_h = np.loadtxt("../log/square_miss/log_dis_for.txt", usecols = (32,33,34,35,36,37,38,39))
w_h = np.loadtxt("../log/square_miss/log_dis_for.txt", usecols = (40,41,42))
V_h = np.loadtxt("../log/square_miss/log_dis_for.txt", usecols = (43,44,45,46,47,48,49,50))
mu_hat_h = np.loadtxt("./log/square_miss/log_dis_for.txt", usecols = (51,52,53,54,55))


sk = 50

time1 = np.loadtxt("../log/square_miss/log_gnc_1.txt", usecols = [0], skiprows = sk)
X1_h = np.loadtxt("../log/square_miss/log_gnc_1.txt", usecols = (1, 2, 3), skiprows = sk)
V1_h = np.loadtxt("../log/square_miss/log_gnc_1.txt", usecols = (4, 5, 6), skiprows = sk)
Att1_h = np.loadtxt("../log/square_miss/log_gnc_1.txt", usecols = (7, 8, 9), skiprows = sk)
Gps1_h = np.loadtxt("../log/square_miss/log_gnc_1.txt", usecols = (10, 11, 12), skiprows = sk)
xi_g_1_h = np.loadtxt("../log/square_miss/log_gnc_1.txt", usecols = [13], skiprows = sk)
xi_CD_1_h = np.loadtxt("../log/square_miss/log_gnc_1.txt", usecols = [14], skiprows = sk)
acc1_h = np.loadtxt("../log/square_miss/log_gnc_1.txt", usecols = (15, 16, 17), skiprows = sk)

time2 = np.loadtxt("../log/square_miss/log_gnc_2.txt", usecols = [0], skiprows = sk)
X2_h = np.loadtxt("../log/square_miss/log_gnc_2.txt", usecols = (1, 2, 3), skiprows = sk)
V2_h = np.loadtxt("../log/square_miss/log_gnc_2.txt", usecols = (4, 5, 6), skiprows = sk)
Att2_h = np.loadtxt("../log/square_miss/log_gnc_2.txt", usecols = (7, 8, 9), skiprows = sk)
Gps2_h = np.loadtxt("../log/square_miss/log_gnc_2.txt", usecols = (10, 11, 12), skiprows = sk)
xi_g_2_h = np.loadtxt("../log/square_miss/log_gnc_2.txt", usecols = [13], skiprows = sk)
xi_CD_2_h = np.loadtxt("../log/square_miss/log_gnc_2.txt", usecols = [14], skiprows = sk)
acc2_h = np.loadtxt("../log/square_miss/log_gnc_2.txt", usecols = (15, 16, 17), skiprows = sk)


time3 = np.loadtxt("../log/square_miss/log_gnc_3.txt", usecols = [0], skiprows = sk)
X3_h = np.loadtxt("../log/square_miss/log_gnc_3.txt", usecols = (1, 2, 3), skiprows = sk)
V3_h = np.loadtxt("../log/square_miss/log_gnc_3.txt", usecols = (4, 5, 6), skiprows = sk)
Att3_h = np.loadtxt("../log/square_miss/log_gnc_3.txt", usecols = (7, 8, 9), skiprows = sk)
Gps3_h = np.loadtxt("../log/square_miss/log_gnc_3.txt", usecols = (10, 11, 12), skiprows = sk)
xi_g_3_h = np.loadtxt("../log/square_miss/log_gnc_3.txt", usecols = [13], skiprows = sk)
xi_CD_3_h = np.loadtxt("../log/square_miss/log_gnc_3.txt", usecols = [14], skiprows = sk)
acc3_h = np.loadtxt("../log/square_miss/log_gnc_3.txt", usecols = (15, 16, 17), skiprows = sk)


time4 = np.loadtxt("../log/square_miss/log_gnc_4.txt", usecols = [0], skiprows = sk)
X4_h = np.loadtxt("../log/square_miss/log_gnc_4.txt", usecols = (1, 2, 3), skiprows = sk)
V4_h = np.loadtxt("../log/square_miss/log_gnc_4.txt", usecols = (4, 5, 6), skiprows = sk)
Att4_h = np.loadtxt("../log/square_miss/log_gnc_4.txt", usecols = (7, 8, 9), skiprows = sk)
Gps4_h = np.loadtxt("../log/square_miss/log_gnc_4.txt", usecols = (10, 11, 12), skiprows = sk)
xi_g_4_h = np.loadtxt("../log/square_miss/log_gnc_4.txt", usecols = [13], skiprows = sk)
xi_CD_4_h = np.loadtxt("../log/square_miss/log_gnc_4.txt", usecols = [14], skiprows = sk)
acc4_h = np.loadtxt("../log/square_miss/log_gnc_4.txt", usecols = (15, 16, 17), skiprows = sk)

pl.rcParams.update({'font.size': 20})

tf = 350

pl.figure(0)
for i in range(0, numEdges):
    pl.plot(time, E_h[:, i], label="$e_%i$"%(i+1))
pl.legend(ncol=2)
pl.grid()
pl.xlabel("Time [s]")
pl.ylabel("Error Interdistances [m]")
pl.xlim((15, tf))
pl.annotate('', xytext=(160, 80), xy=(300, 0), \
        arrowprops=dict(arrowstyle="<|-",
                  connectionstyle="arc3,rad=-0.2",
                  fc="w",color="black"))
a = pl.axes([0.25, 0.5, 0.2, 0.2])
for i in range(0, numEdges):
    pl.plot(time, E_h[:, i], label="$e_%i$"%(i+1))
pl.plot(time, 0*np.ones(np.size(time)), 'k--', linewidth = 3.0)
pl.xlim((300, 350))
pl.ylim((-5, 5))
pl.grid()
pl.xticks([])

pl.figure(1)
pl.subplot(1, 2, 1)
pl.plot(time3, -acc3_h[:, 0]*0.9 -0.03, 'k', label="Actual $a_N$")
pl.plot(time, U_h[:, 4]*0.9, 'r--', label="Commanded $a_N$")
pl.grid()
pl.legend()
pl.ylabel("Acceleration [m/$s^2$]")
pl.xlim((1, 350))
pl.xlabel("Time [s]")
pl.subplot(1, 2, 2)
pl.plot(time3, -acc3_h[:, 1]*0.9 -0.02, 'k', label="Actual $a_E$")
pl.plot(time, U_h[:, 5]*0.9, 'r--', label="Commanded $a_E$")
pl.legend()
pl.grid()
pl.xlim((1, 350))
pl.xlabel("Time [s]")

pl.figure(2)
for i in range(0, numEdges):
    pl.plot(time, mu_hat_h[:, i], label="$\hat\mu_%i$"%(i+1))
pl.plot(time, -0.4*np.ones(np.size(time)), 'k--', label="Actual mismatches")
pl.plot(time, 0.3*np.ones(np.size(time)), 'k--')
pl.plot(time, 0.1*np.ones(np.size(time)), 'k--')
pl.plot(time, -0.6*np.ones(np.size(time)), 'k--')
pl.plot(time, 0.7*np.ones(np.size(time)), 'k--')
pl.legend(ncol=2)
pl.grid()
pl.xlabel("Time [s]")
pl.ylabel("Estimator $\hat\mu$ [m]")
pl.xlim((15, tf))

pl.show()
