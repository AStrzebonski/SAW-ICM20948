from kalman_filter import *
from data_read import *
import mouse
import matplotlib.pyplot as plt
import datetime


if __name__ == '__main__':
    # Parameters

    dt = 0.02

    A_turn = np.array([[1., -dt], [0., 1.]])
    B_turn = np.array([[dt, 0.]])
    C_turn = np.array([[1., 0.]])

    A_move = np.array([1.])
    B_move = np.array([dt])
    C_move = np.array([1.])

    V_turn = np.array([[0.04 * dt, 0], [0, 0.04 * dt]]) * 5  # processing noise
    V_move = np.array([0.1 * dt])
    W = 0.2  # measurement noise

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
    theta_filter = KalmanFilter(V_turn.copy(), W, A_turn, B_turn, C_turn, x0_roll, P0_roll)
    phi_filter = KalmanFilter(V_turn.copy(), W, A_turn, B_turn, C_turn, x0_roll, P0_roll)
    mx_filter = KalmanFilter(V_move.copy(), W, A_move, B_move, C_move, x0_m, P0_m)
    my_filter = KalmanFilter(V_move.copy(), W, A_move, B_move, C_move, x0_m, P0_m)

    ser = serial_init(rate=115200, port='COM7')

    while True:
        ax, ay, az, ux, uy, uz = read_data(ser)

        # conversion because of rotated mount
        ax_ = -ay
        ay_ = ax
        ux_ = -uy
        uy_ = ux
        ax = ax_
        ay = ay_
        ux = ux_
        uy = uy_

        # conversion to rad/s * tuning factor
        ux = ux * 0.0010642 * 3.1
        uy = -uy * 0.0010642 * 3.1
        uz = -uz * 0.0010642 * 3.1
        # gravity estimation
        g += 0.2 * (np.sqrt(np.square(ax) + np.square(ay) + np.square(az)) - g)

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

        ax_list = np.append(ax_list, amx)
        ax_list = np.delete(ax_list, 0)
        ay_list = np.append(ay_list, amy)
        ay_list = np.delete(ay_list, 0)


        if np.var(ax_list) < 1000:
            vmx = 0
            mx_filter.xpost = 0
        if np.var(ax_list) < 1000:
            vmy = 0
            my_filter.xpost = 0

        mouse.move(mx_filter.xpost, my_filter.xpost, absolute=False, duration=dt/5)

        print('x: \t', mx_filter.xpost, 'y: \t', my_filter.xpost, 'phi: \t', phi, 'theta: \t', theta)
