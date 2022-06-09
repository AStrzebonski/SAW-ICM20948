from kalman_filter import *
from data_read import *
import mouse
import matplotlib.pyplot as plt
import datetime


if __name__ == '__main__':
    # Parameters

    dt = 1./10.

    A_turn = np.array([[1., -dt], [0., 1.]])
    B_turn = np.array([[dt, 0.]])
    C_turn = np.array([[1., 0.]])

    A_move = np.array([1.])
    B_move = np.array([dt])
    C_move = np.array([1.])

    std_dev_v = 0.1     # processing noise
    std_dev_w = 0.08    # measurement noise
    V_turn = np.array([[std_dev_v * std_dev_v * dt, 0], [0, std_dev_v * std_dev_v * dt]])  # processing noise
    V_move = np.array([std_dev_v*dt])
    W = std_dev_w * std_dev_w

    # initial values:
    # roll:
    x0_roll = np.array([[0., 0.]]).T
    P0_roll = np.array([[1., 0.], [0., 1.]])
    # move:
    x0_m = np.array([0])
    P0_m = np.array([1.])

    g = 1000
    vmx = 0
    vmy = 0
    phi = 0
    theta = 0

    ax_list = np.array([0, 0, 0, 0, 0, 0])
    ay_list = np.array([0, 0, 0, 0, 0, 0])

    # Kalman Filters init:
    theta_filter = KalmanFilter(V_turn.copy()*5, W, A_turn, B_turn, C_turn, x0_roll, P0_roll)
    phi_filter = KalmanFilter(V_turn.copy()*5, W, A_turn, B_turn, C_turn, x0_roll, P0_roll)
    mx_filter = KalmanFilter(V_move.copy()*1, W, A_move, B_move, C_move, x0_m, P0_m)
    my_filter = KalmanFilter(V_move.copy()*1, W, A_move, B_move, C_move, x0_m, P0_m)

    ser = serial_init(rate=115200, port='COM7')

    t_p = []
    vmx_p = []
    vmxpost_p = []
    vmy_p = []
    vmypost_p = []
    phipri_p = []
    phi_p = []
    thetapri_p = []
    theta_p = []
    ux_p = []

    for i in range(100):
        # start = datetime.datetime.now()
        ax, ay, az, ux, uy, uz = read_data(ser)

        ux = ux * 0.0010642
        uy = uy * 0.0010642
        uz = uz * 0.0010642
        g += 0.2 * (np.sqrt(np.square(ax) + np.square(ay) + np.square(az)) - g)
        # step1 = datetime.datetime.now()

        phi_pri = np.arctan2(ax, az)
        theta_pri = np.arctan2(ay, az)

        amx = ax - 50*np.round(g * np.sin(phi)/50)
        amy = ay - 50*np.round(g * np.sin(theta)/50)
        vmx += amx*dt
        vmy += amy*dt

        Utheta = ux * np.cos(phi) + uz * np.sin(phi)
        Uphi = uy * np.cos(theta) + uz * np.sin(theta)

        theta_filter.predict(Utheta)
        phi_filter.predict(Uphi)
        mx_filter.predict(0)
        my_filter.predict(0)

        theta_filter.update(theta_pri)
        phi_filter.update(phi_pri)
        mx_filter.update(vmx)
        my_filter.update(vmy)
        theta = theta_filter.xpost[0, 0].copy()
        phi = phi_filter.xpost[0, 0].copy()

        ax_list = np.append(ax_list, mx_filter.xpost)
        ax_list = np.delete(ax_list, 0)
        ay_list = np.append(ay_list, my_filter.xpost)
        ay_list = np.delete(ay_list, 0)

        # print(np.var(ax_list), np.var(ay_list))

        if np.var(ax_list) < 40:
            vmx = 0
        if np.var(ax_list) < 40:
            vmy = 0
        # step2 = datetime.datetime.now()

        mouse.move(-mx_filter.xpost, -my_filter.xpost, absolute=False, duration=dt/10)

        # stop = datetime.datetime.now()
        # execute_time1 = step1 - start
        # execute_time2 = step2 - step1

        # print('ax: \t', ax, 'ay:\t', ay, 'az:\t', az, 'ux:\t', ux, 'uy:\t', uy, 'uz:\t', uz)
        # print('amx: \t', amx, 'amy: \t', amy, 'phi pri: \t', phi_pri, 'theta_pri: \t', theta_pri)
        # print('vmx: \t', vmx, 'vmy: \t', vmy, 'U theta: \t', Utheta, 'U phi: \t', Uphi)
        # print('x: \t', mx_filter.xpost, 'y: \t', my_filter.xpost, 'phi: \t', phi, 'theta: \t', theta)
        # execute_time = stop - start
        # print(g)
        # print(execute_time1)
        # print(execute_time2)
        # print(execute_time)

    #     t_p.append(i*dt)
    #     vmx_p.append(vmx)
    #     vmxpost_p.append(mx_filter.xpost)
    #     vmy_p.append(vmy)
    #     vmypost_p.append(my_filter.xpost)
    #     phi_p.append(phi)
    #     phipri_p.append(phi_pri)
    #     theta_p.append(theta)
    #     thetapri_p.append(theta_pri)
    #     ux_p.append(ux)
    #
    # plt.plot(t_p, vmx_p)
    # plt.plot(t_p, vmxpost_p)
    # # plt.plot(t_p, thetapri_p)
    # # plt.plot(t_p, theta_p)
    # # plt.plot(t_p, ux_p)
    # plt.show()
