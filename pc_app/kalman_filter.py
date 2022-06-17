import numpy as np


class KalmanFilter:

    def __init__(self, V, W, A, B, C, x0, P0):
        """
        :param std_dev_v: processing noise standard deviation
        :param std_dev_w: measurement noise standard deviation
        :param A: state matrix
        :param B: input matrix
        :param C: output matrix
        :param x0: initial position
        :param P0: initial covariance matrix
        """
        self.V = V
        self.W = W
        self.A = A.copy()
        self.B = B.copy()
        self.C = C.copy()
        self.x0 = x0.copy()
        self.xpri = x0.copy()
        self.xpost = x0.copy()
        self.Ppri = P0.copy()
        self.Ppost = P0.copy()

    def predict(self, u):
        """
        :param u: velocity
        :return:
        """
        self.xpri = np.dot(self.A, self.xpost) + np.dot(self.B.T, [u])
        self.Ppri = np.dot(np.dot(self.A, self.Ppost), np.transpose(self.A)) + self.V

    def update(self, Y):
        """
        :param Y: current state
        :return:
        """
        eps = Y - np.dot(self.C, self.xpri)
        S = np.dot(np.dot(self.C, self.Ppri), np.transpose(self.C)) + self.W
        K = np.dot(np.dot(self.Ppri, np.transpose(self.C)), S ** (-1))
        self.xpost = self.xpri + np.dot(K, eps)
        self.Ppost = self.Ppri - np.dot(np.dot(K, S), np.transpose(K))
