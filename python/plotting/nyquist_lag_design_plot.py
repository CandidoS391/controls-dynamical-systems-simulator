import csv
import matplotlib.pyplot as plt
import math

def load_lag_design_data(filename):
  # Create all of the required lists to hold all the data.
  frequencies = []
  original_real = []
  original_imaginary = []
  lag_1_real = []
  lag_1_imaginary = []
  lag_2_real = []
  lag_2_imaginary = []
  lag_3_real = []
  lag_3_imaginary = []

  # Open up the file and start to read in the data row by row
  with open(filename, "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
      frequencies.append(float(row["frequency"]))
      original_real.append(float(row["original_real"]))
      original_imaginary.append(float(row["original_imaginary"]))

      lag_1_real.append(float(row["lag_1_real"]))
      lag_1_imaginary.append(float(row["lag_1_imaginary"]))

      lag_2_real.append(float(row["lag_2_real"]))
      lag_2_imaginary.append(float(row["lag_2_imaginary"]))

      lag_3_real.append(float(row["lag_3_real"]))
      lag_3_imaginary.append(float(row["lag_3_imaginary"]))

  return frequencies, original_real, original_imaginary, lag_1_real, lag_1_imaginary, lag_2_real, lag_2_imaginary, lag_3_real, lag_3_imaginary

# Plotting unit circle helper function
def plot_unit_circle():
  circle_real = []
  circle_imaginary = []

  num_points = 500

  for i in range(num_points):
    theta = 2 * math.pi * i / (num_points - 1)

    circle_real.append(math.cos(theta))
    circle_imaginary.append(math.sin(theta))

  plt.plot(
     circle_real,
     circle_imaginary,
     color="gray",
     linestyle="--",
     linewidth=1.2,
     label="Unit Circle"
  )    

def find_nearest_frequency_index(frequencies, target_frequency):
    nearest_index = 0
    smallest_difference = abs(frequencies[0] - target_frequency)

    for i in range(1, len(frequencies)):
        current_difference = abs(frequencies[i] - target_frequency)

        if current_difference < smallest_difference:
            smallest_difference = current_difference
            nearest_index = i

    return nearest_index

# Infrastructure needed for gain-crossover detection for PM geometry
def find_gain_crossover_index(real_values, imaginary_values):
  crossover_idx = 0

  # Calculate the current magnitude and smallest difference
  # At the first recorded value
  curr_magnitude = math.sqrt(
    real_values[0] ** 2 + imaginary_values[0] ** 2
  )
  smallest_difference = abs(curr_magnitude - 1.0)

  # Iterate through the rest of the values
  for i in range(1, len(real_values)):
    # Recalculate the current magnitude and current difference
    curr_magnitude = math.sqrt(
      real_values[i] ** 2 + imaginary_values[i] ** 2
    )

    curr_difference = abs(curr_magnitude - 1.0)

    # If the smallest difference is greater than the current difference
    # Record the new smallest difference and the index it occurs
    if curr_difference < smallest_difference:
      smallest_difference = curr_difference
      crossover_idx = i

  return crossover_idx

def add_contour_arrow(real_values, imaginary_values, start_idx, end_idx, color):
  plt.annotate(
    "",
    xy=(real_values[end_idx], imaginary_values[end_idx]),
    xytext=(real_values[start_idx], imaginary_values[start_idx]),
    arrowprops=dict(
      arrowstyle="->",
      linewidth=1.5,
      color=color
    )
  )

def plot_lag_design(frequencies, original_real, original_imaginary, lag_1_real, lag_1_imaginary, lag_2_real, lag_2_imaginary, lag_3_real, lag_3_imaginary):
  # Create a brand new lag design figure
  plt.figure()

  # Plot the contour for the original response
  plt.plot(
    original_real,
    original_imaginary,
    label="Original",
    color="tab:blue"
  )

  # Plot the tree lag-compensated Nyquist contours
  plt.plot(
     lag_1_real,
     lag_1_imaginary,
     label="Lag 1",
     color="tab:orange"
  )
  plt.plot(
     lag_2_real,
     lag_2_imaginary,
     label="Lag 2",
     color="tab:green"
  )  
  plt.plot(
     lag_3_real,
     lag_3_imaginary,
     label="Lag 3",
     color="tab:red"
  )

  # Calculate the gain crossover for lag_2
  lag_2_gc_idx = find_gain_crossover_index(
    lag_2_real,
    lag_2_imaginary
  )

  # Find the real, imaginary, and frequency values
  gc_real = lag_2_real[lag_2_gc_idx]
  gc_imaginary = lag_2_imaginary[lag_2_gc_idx]
  gc_frequency = frequencies[lag_2_gc_idx]

  # Visualize the crossover
  plt.scatter(
    gc_real,
    gc_imaginary,
    color="tab:green",
    edgecolor="black",
    zorder=5
  )

  # Plot the unit circle for reference
  plot_unit_circle()

  # ----- Plotting the arrows -----
  # Find frequency indices for the Lag 1 direction
  lag_1_start_idx = find_nearest_frequency_index(frequencies, 0.025)
  lag_1_end_idx = find_nearest_frequency_index(frequencies, 0.028)

  # Find frequency indices for the Lag 2 direction
  lag_2_start_idx = find_nearest_frequency_index(frequencies, 0.25)
  lag_2_end_idx = find_nearest_frequency_index(frequencies, 0.28)

  # Find frequency indices for the Lag 3 direction
  lag_3_start_idx = find_nearest_frequency_index(frequencies, 2.5)
  lag_3_end_idx = find_nearest_frequency_index(frequencies, 2.8)

  # Show the direction of increasing frequency along each Lag contour
  add_contour_arrow(
    lag_1_real,
    lag_1_imaginary,
    lag_1_start_idx,
    lag_1_end_idx,
    "tab:orange"
  )

  add_contour_arrow(
    lag_2_real,
    lag_2_imaginary,
    lag_2_start_idx,
    lag_2_end_idx,
    "tab:green"
  )

  add_contour_arrow(
    lag_3_real,
    lag_3_imaginary,
    lag_3_start_idx,
    lag_3_end_idx,
    "tab:red"
  )

  # Plot the Real and imaginary axeses
  plt.axhline(
    0,
    color="black",
    linewidth=0.8
  )
  plt.axvline(
    0, 
    color="black",
    linewidth=0.8
  )

  # Add the critical point and the corresponding label
  plt.scatter(-1, 0)
  plt.annotate(
    "-1 + j0",
    (-1, 0)
  )

  # Set the Re-axis and the Im-axis labels
  plt.xlabel("Re")
  plt.ylabel("Im")

  # Title the plot
  plt.title("Nyquist Design via Lag Compensation")

  # Enable the grid, legend, and axis
  plt.grid(True)
  plt.legend()
  plt.gca().set_aspect("equal", adjustable="box")

  # Set the axis limits
  plt.xlim(-2.5, 1.5)
  plt.ylim(-2.5, 1.0)

  # Save the figure and then show it
  plt.savefig("output/nyquist_lag_design.png")
  plt.show()

def main():
  # Load up the filename
  filename = "output/nyquist_lag_design.csv"

  # Get the frequency, original real/imaginary data, and the lag-compensated real/imaginary data
  (
    frequencies,
    original_real,
    original_imaginary,
    lag_1_real,
    lag_1_imaginary,
    lag_2_real,
    lag_2_imaginary,
    lag_3_real,
    lag_3_imaginary
  ) = load_lag_design_data(filename)

  # Plot the graph
  plot_lag_design(
    frequencies,
    original_real,
    original_imaginary,
    lag_1_real,
    lag_1_imaginary,
    lag_2_real,
    lag_2_imaginary,
    lag_3_real,
    lag_3_imaginary
  )

if __name__ == "__main__":
  main()
