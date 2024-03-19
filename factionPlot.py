import matplotlib.pyplot as plt
import numpy as np
import csv

position = []
setpoint = []
time = []

signal = []

with open('time-position-signal.csv', 'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        time.append(float(row[0]))
        position.append(float(row[1]))
        signal.append(float(row[2]))
        setpoint.append(float(row[3]))


plt.subplot(2, 1, 1)
plt.plot(time, position, label='Position')
plt.plot(time, setpoint, label='Setpoint')
plt.xlabel('Time (s)')
plt.ylabel('Position (m)')
plt.title('Position vs Time')
plt.legend()

plt.subplot(2, 1, 2)
plt.plot(time, signal, label='Signal')
plt.xlabel('Time (s)')
plt.ylabel('Signal')
plt.legend()
plt.show()