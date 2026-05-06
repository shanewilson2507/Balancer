#!usr/bin/python3

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

df = pd.read_csv("../../data/raw/trim_S50_blockSupport_stepTest_2026-04-26_run04.csv")

t = df["t (ms)"] / 1000
uL = df[" uL (%)"]
uR = df[" uR (%)"]
w_y = df[" w_y (rad/s)"]

theta_y = (df[" f_x (ms^-2)"] * (-9.8))

fig, axs = plt.subplots(2,2, sharex = True)

axs[0, 0].plot(t, uL)
axs[0, 0].set_ylabel("uL (%)")

axs[0, 1].plot(t, uR)
axs[0, 1].set_ylabel("uR (%)")

axs[1, 0].plot(t, w_y)
axs[1, 0].set_ylabel("w_y (rad / s)")
axs[1, 0].set_xlabel("t (s)")

axs[1, 1].plot(t, theta_y)
axs[1, 1].set_ylabel("f_x (ms^-2)")
axs[1, 1].set_xlabel("t (s)")

plt.show()

