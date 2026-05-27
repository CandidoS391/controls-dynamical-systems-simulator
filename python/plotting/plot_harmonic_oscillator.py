import matplotlib.pyplot as plt
import csv 

# Empty Data
time_euler = []
x_euler = []
v_euler = []

time_rk4 = []
x_rk4 = []
v_rk4 = []


# Read Euler CSV File
with open("output/harmonic_oscillator_euler.csv", mode='r') as euler_file:
  next(euler_file)
  reader = csv.reader(euler_file)

  for row in reader:
    time = float(row[0])
    x = float(row[1])
    v = float(row[2])

    time_euler.append(time)
    x_euler.append(x)
    v_euler.append(v)

with open("output/harmonic_oscillator_rk4.csv", mode='r') as rk4_file:
  next(rk4_file)
  reader = csv.reader(rk4_file)

  for row in reader:
    time = float(row[0])
    x = float(row[1])
    v = float(row[2])

    time_rk4.append(time)
    x_rk4.append(x)
    v_rk4.append(v)


# ===== Building the Plot over time =====
plt.figure()

# Plotting Euler position over time
plt.plot(time_euler, x_euler, label="Euler")

# Plotting RK4 position over time
plt.plot(time_rk4, x_rk4, label="RK4")

# Title and axis
plt.title("Harmonic Oscillator: Position vs Time")
plt.xlabel("Time")
plt.ylabel("Position x(t)")

# Grid lines
plt.grid(True)

# Legend
plt.legend()

# ===== Building the Plot as a phase portrait =====
plt.figure()

plt.plot(x_euler, v_euler, label="Euler")
plt.plot(x_rk4, v_rk4, label="RK4")

plt.title("Harmonic Oscillator Phase Portrait")
plt.xlabel("Position x")
plt.ylabel("Velocity v")

plt.grid(True)

plt.legend()

# Makes circles look like circles instead of stretched ovals
plt.axis("equal")

plt.figure(1)
plt.savefig("output/position_vs_time.png")

plt.figure(2)
plt.savefig("output/phase_portrait.png")

plt.show()