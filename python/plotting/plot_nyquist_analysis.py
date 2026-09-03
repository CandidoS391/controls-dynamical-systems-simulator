import csv
import matplotlib.pyplot as plt
import math

# Read in value from csv file
def read_nyquist_analysis(filename):
  s_real_values = []
  s_imaginary_values = []
  mapped_real_values = []
  mapped_imaginary_values = []

  with open(filename, "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
      s_real_values.append(float(row["s_real"]))
      s_imaginary_values.append(float(row["s_imaginary"]))
      mapped_real_values.append(float(row["mapped_real"]))
      mapped_imaginary_values.append(float(row["mapped_imaginary"]))

  return s_real_values, s_imaginary_values, mapped_real_values, mapped_imaginary_values

# Read in myquist metrics
def read_nyquist_metrics(filename):
  with open(filename, "r") as file:
    reader = csv.DictReader(file)
    row = next(reader)

    phase_crossover_frequency = float(
      row["phase_crossover_frequency"]
    )
    phase_crossover_real = float(
      row["phase_crossover_real"]
    )
    phase_crossover_imaginary = float(
      row["phase_crossover_imaginary"]
    )
    gain_margin = float(
      row["gain_margin"]
    )
    gain_crossover_frequency = float(
      row["gain_crossover_frequency"]
    )
    gain_crossover_real = float(
      row["gain_crossover_real"]
    )
    gain_crossover_imaginary = float(
     row["gain_crossover_imaginary"] 
    )
    phase_margin = float(
      row["phase_margin"]
    )

  return (
    phase_crossover_frequency,
    phase_crossover_real,
    phase_crossover_imaginary,
    gain_margin,
    gain_crossover_frequency,
    gain_crossover_real,
    gain_crossover_imaginary,
    phase_margin
  )

def plot_nyquist(s_real_values, s_imaginary_values, mapped_real_values, mapped_imaginary_values, phase_crossover_frequency, phase_crossover_real, phase_crossover_imaginary, gain_margin, gain_crossover_frequency, gain_crossover_real, gain_crossover_imaginary, phase_margin):
  plt.figure()

  plt.plot(mapped_real_values, mapped_imaginary_values)

  # ---- Plotting the direction arrows
  # Frequencies where arrows should start
  # Frequencies where direction arrows should be placed
  arrow_frequencies = [
    0.5,
    2.0,
    -2.0,
    -0.5
  ]

  # Controls the visible length of each arrow
  arrow_length = 0.06

  for target_frequency in arrow_frequencies:
    closest_index = 0
    smallest_difference = float("inf")

    # Find the point on the imaginary axis closest
    # to the desired frequency
    for i in range(len(s_real_values)):
      if abs(s_real_values[i]) < 1e-8:
        current_difference = abs(
          s_imaginary_values[i] - target_frequency
        )

        if current_difference < smallest_difference:
          smallest_difference = current_difference
          closest_index = i

    # Make sure there are neighboring points available
    if closest_index == 0:
      continue

    if closest_index == len(mapped_real_values) - 1:
      continue

    # Use neighboring mapped points to estimate
    # the local tangent direction of the curve
    delta_real = (
      mapped_real_values[closest_index + 1]
      - mapped_real_values[closest_index - 1]
    )

    delta_imaginary = (
      mapped_imaginary_values[closest_index + 1]
      - mapped_imaginary_values[closest_index - 1]
    )

    # Find the length of the tangent vector
    direction_length = math.hypot(
      delta_real,
      delta_imaginary
    )

    if direction_length < 1e-8:
      continue

    # Normalize the tangent direction
    unit_real = delta_real / direction_length
    unit_imaginary = delta_imaginary / direction_length

    # Construct a short arrow following the tangent
    arrow_end_real = (
      mapped_real_values[closest_index]
      + arrow_length * unit_real
    )

    arrow_end_imaginary = (
      mapped_imaginary_values[closest_index]
      + arrow_length * unit_imaginary
    )

    # Draw the direction arrow
    plt.annotate(
      "",
      xy=(
        arrow_end_real,
        arrow_end_imaginary
      ),
      xytext=(
        mapped_real_values[closest_index],
        mapped_imaginary_values[closest_index]
      ),
      arrowprops=dict(arrowstyle="->")
    )

  # ---- Plotting Frequencies ----
  label_frequencies = [
    0.0,
    0.25,
    0.5,
    1.0,
    2.0,
    5.0,
    10.0
  ]

  arrow_frequency_step = 0.1

  for target_frequency in label_frequencies:
    closest_index = 0
    smallest_difference = float("inf")

    for i in range(len(s_real_values)):
      # Consider points on the imaginary axis
      if abs(s_real_values[i]) < 1e-8:
        current_difference = abs(
          s_imaginary_values[i] - target_frequency
        )

        if current_difference < smallest_difference:
          smallest_difference = current_difference
          closest_index = i

    # Mark the mapped locations
    plt.scatter(
      mapped_real_values[closest_index],
      mapped_imaginary_values[closest_index]
    )

    # Label the corresponding frequency
    plt.annotate(
      f"ω = {s_imaginary_values[closest_index]:.2f}",
      (
        mapped_real_values[closest_index],
        mapped_imaginary_values[closest_index]
      )
    )

  # Mark the Nyquist crtiical point
  plt.scatter(-1.0, 0.0)

  plt.annotate(
    "(-1, 0)",
    (-1.0, 0.0)
  )

  # Mark the phase-crossover point
  plt.scatter(
    phase_crossover_real,
    phase_crossover_imaginary,
    zorder=6
  )

  # Mark the gain-crossover point
  plt.scatter(
    gain_crossover_real,
    gain_crossover_imaginary,
    zorder=6
  )

  # Draw the gain-margin indicator
  plt.plot(
    [phase_crossover_real, -1.0],
    [phase_crossover_imaginary, 0.0],
    linestyle="--"
  )

  # Draw the radius to the gain-crossover point
  plt.plot(
    [0.0, gain_crossover_real],
    [0.0, gain_crossover_imaginary],
    linestyle="--"
  )

  # Draw the negative real-axis reference
  plt.plot(
    [0.0, -1.0],
    [0.0, 0.0],
    linestyle="--"
  )

  # ---- Phase Margin Arc ----
  arc_radius = 0.20
  num_arc_points = 100

  gain_crossover_angle = math.atan2(
    gain_crossover_imaginary,
    gain_crossover_real
  )

  arc_angles = [
    -math.pi + i * (
      gain_crossover_angle + math.pi
    ) / (num_arc_points - 1)
    for i in range(num_arc_points)
  ]

  arc_real = [
    arc_radius * math.cos(angle)
    for angle in arc_angles
  ]

  arc_imaginary = [
    arc_radius * math.sin(angle)
    for angle in arc_angles
  ]

  plt.plot(
    arc_real,
    arc_imaginary
  )

  # Reference for the crossover angle
  reference_real = -arc_radius

  crossover_ray_real = (
    arc_radius * math.cos(gain_crossover_angle)
  )
  crossover_ray_imaginary = (
    arc_radius * math.sin(gain_crossover_angle)
  )

  plt.plot(
    [0.0, reference_real],
    [0.0, 0.0],
    linestyle="--"
  )

  plt.plot(
    [0.0, crossover_ray_real],
    [0.0, crossover_ray_imaginary],
    linestyle="--"
  )

  # Annotate the actual numerical gain margin
  plt.annotate(
    f"GM = {gain_margin:.2f}\n"
    f"$\\omega_{{pc}}$ = {phase_crossover_frequency:.2f}",
    (phase_crossover_real, phase_crossover_imaginary),
    xytext=(-75, 55),
    textcoords="offset points",
    arrowprops=dict(arrowstyle="->")
  )

  # Annotate the actual numerical phase margin
  plt.annotate(
    f"PM = {phase_margin:.2f}°\n"
    f"$\\omega_{{gc}}$ = {gain_crossover_frequency:.2f}",
    (gain_crossover_real, gain_crossover_imaginary),
    xytext=(55, 25),
    textcoords="offset points",
    arrowprops=dict(arrowstyle="->")
  )



  # Plot formatting
  plt.xlabel("Re")
  plt.ylabel("Im")
  plt.title("Nyquist plot")

  plt.axhline(0)
  plt.axvline(0)

  plt.grid(True)

  plt.savefig("output/nyquist_plot.png")

  plt.show()

def main():
  s_real_values, s_imaginary_values, mapped_real_values, mapped_imaginary_values = read_nyquist_analysis("output/nyquist_data.csv")

  phase_crossover_frequency, phase_crossover_real, phase_crossover_imaginary, gain_margin, gain_crossover_frequency, gain_crossover_real, gain_crossover_imaginary, phase_margin = read_nyquist_metrics(
  "output/nyquist_metrics.csv"
  )

  plot_nyquist(s_real_values, s_imaginary_values, mapped_real_values, mapped_imaginary_values, phase_crossover_frequency, phase_crossover_real, phase_crossover_imaginary, gain_margin, gain_crossover_frequency, gain_crossover_real, gain_crossover_imaginary, phase_margin)

if __name__ == "__main__":
  main()
  

