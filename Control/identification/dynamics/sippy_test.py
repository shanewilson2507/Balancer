from sippy_unipi import *
import numpy as np
import control as ct
import matplotlib.pyplot as plt

L = 1000
u = 25*np.random.randn(1,L)
u = np.clip(u, -50, 50)
x = np.zeros(shape=(2, L))
y = np.zeros(shape=(2, L))

w = 1*np.random.randn(2,L)
n = 1*np.random.randn(2,L)

#system matrices
A = np.array([[0.6, 0.2], [-0.1, 0.7]])
B = np.array([[1],[0.5]])
C = np.array([[1, 0], [0, 1]])
D = np.zeros((2,1)) 

#simulate system
for i in range(L-1):
    x[:,i+1] = A@x[:,i] + B@u[:,i] + w[:,i]
    y[:,i+1] = C@x[:,i+1] + D@u[:,i+1] + n[:,i+1]

model_pred = system_identification(y, u, "N4SID")

ss_model = ct.ss(A,B,C,D, dt=True)
ss_model_pred = ct.ss(model_pred.A, model_pred.B, model_pred.C, model_pred.D, dt=True)

#tf = ct.ss2tf(ss_model)
#tf_pred = ct.ss2tf(ss_model_pred)

ct.bode_plot([ss_model, ss_model_pred])

plt.show()
