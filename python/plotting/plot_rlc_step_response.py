import matplotlib.pyplot as plt
import csv

time_euler = []
q_euler = []
i_euler = []

time_rk4 = []
q_rk4 = []
i_rk4 = []

with open("output/rlc_step_response_euler.csv", mode="r") as euler_file:
  next(euler_file)
  reader = csv.reader(euler_file)
  for row in reader:
    time_euler.append(float(row[0]))
    q_euler.append(float(row[1]))
    i_euler.append(float(row[2]))

with open("output/rlc_step_response_rk4.csv", mode="r") as rk4_file:
  next(rk4_file)
  reader = csv.reader(rk4_file)
  for row in reader:
    time_rk4.append(float(row[0]))
    q_rk4.append(float(row[1]))
    i_rk4.append(float(row[2]))

plt.figure()
plt.plot(time_euler, q_euler, label="Euler")
plt.plot(time_rk4, q_rk4, label="RK4")

plt.title("RLC Circuit Step Response: Charge vs Time")
plt.xlabel("Time")
plt.ylabel("Charge q(t)")

plt.grid(True)
plt.legend()

plt.figure()
plt.plot(q_euler, i_euler, label="Euler")
plt.plot(q_rk4, i_rk4, label="RK4")

plt.title("RLC Circuit Phase Portrait")
plt.xlabel("Charge q")
plt.ylabel("Current i")

plt.grid(True)
plt.legend()
plt.axis("equal")

plt.figure(1)
plt.savefig("output/rlc_charge_vs_time.png")

plt.figure(2)
plt.savefig("output/rlc_phase_portrait.png")

plt.show()