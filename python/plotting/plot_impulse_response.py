import matplotlib.pyplot as plt
import csv

time_euler = []
x_euler = []
v_euler = []

time_rk4 = []
x_rk4 = []
v_rk4 = []

with open("output/pulse_response_euler.csv", mode="r") as euler_file:
  next(euler_file)
  reader = csv.reader(euler_file)

  for row in reader:
    time_euler.append(float(row[0]))
    x_euler.append(float(row[1]))
    v_euler.append(float(row[2]))

with open("output/pulse_response_rk4.csv", mode="r") as rk4_file:
  next(rk4_file)
  reader = csv.reader(rk4_file)

  for row in reader:
    time_rk4.append(float(row[0]))
    x_rk4.append(float(row[1]))
    v_rk4.append(float(row[2]))

plt.figure()

plt.plot(time_euler, x_euler, label="Euler")
plt.plot(time_rk4, x_rk4, label="RK4")

plt.title("Pulse Input Response: Position vs Time")
plt.xlabel("Time")
plt.ylabel("Position x(t)")

plt.grid(True)
plt.legend()

plt.figure()

plt.plot(x_euler, v_euler, label="Euler")
plt.plot(x_rk4, v_rk4, label="RK4")

plt.title("Pulse Input Response Phase Portrait")
plt.xlabel("Position x")
plt.ylabel("Velocity v")

plt.grid(True)
plt.legend()
plt.axis("equal")

plt.figure(1)
plt.savefig("output/pulse_position_vs_time.png")

plt.figure(2)
plt.savefig("output/pulse_phase_portrait.png")

plt.show()