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

def plot_nyquist(s_real_values, s_imaginary_values, mapped_real_values, mapped_imaginary_values):
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
  plot_nyquist(s_real_values, s_imaginary_values, mapped_real_values, mapped_imaginary_values)

if __name__ == "__main__":
  main()
  

