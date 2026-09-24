import csv
import matplotlib.pyplot as plt
import math

def load_lag_design_data(filename):
  # Create all of the required lists to hold all the data.
  frequencies = []
  original_real = []
  original_imaginary = []
  compensated_real = []
  compensated_imaginary = []

  # Open up the file and start to read in the data row by row
  with open(filename, "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
      frequencies.append(float(row["frequency"]))
      original_real.append(float(row["original_real"]))
      original_imaginary.append(float(row["original_imaginary"]))
      compensated_real.append(float(row["compensated_real"]))
      compensated_imaginary.append(float(row["compensated_imaginary"]))

  return frequencies, original_real, original_imaginary, compensated_real, compensated_imaginary

def find_nearest_frequency_index(frequencies, target_frequency):
    nearest_index = 0
    smallest_difference = abs(frequencies[0] - target_frequency)

    for i in range(1, len(frequencies)):
        current_difference = abs(frequencies[i] - target_frequency)

        if current_difference < smallest_difference:
            smallest_difference = current_difference
            nearest_index = i

    return nearest_index

# Create a new contour segement helper function
def plot_frequency_segment(frequencies, real_values, imaginary_values, start_frequency, end_frequency, color="tab:orange"):
  # Identify the starting index
  start_idx = find_nearest_frequency_index(
     frequencies,
     start_frequency
  )

  # Identify the end index
  end_idx = find_nearest_frequency_index(
     frequencies,
     end_frequency
  )

  # Plot the real/imaginary values from starting index up until the end index
  plt.plot(
     real_values[start_idx:end_idx],
     imaginary_values[start_idx:end_idx],
     color=color
  )

  return start_idx, end_idx


def plot_lag_design(frequencies, original_real, original_imaginary, compensated_real, compensated_imaginary):
  # Create a brand new lag design figure
  plt.figure()

  # Plot the contour for the original response
  plt.plot(
    original_real,
    original_imaginary,
    label="Original",
    color="tab:blue"
  )

  # Plot the selected low_frequency portion
  plot_frequency_segment(
     frequencies,
     compensated_real,
     compensated_imaginary,
     0.0,
     0.15
  )

  # Plot the transition-frequency portion
  plot_frequency_segment(
     frequencies,
     compensated_real,
     compensated_imaginary,
     0.25,
     0.9
  )

  # Plot the high-frequency portion
  plot_frequency_segment(
     frequencies,
     compensated_real,
     compensated_imaginary,
     1.1,
     5.0
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
  plt.axis('equal')

  # Save the figure and then show it
  plt.savefig("output/nyquist_lag_design.png")
  plt.show()

def main():
  # Load up the filename
  filename = "output/nyquist_lag_design.csv"

  # Get the frequency, original real/imaginary data, and the compensated real/imaginary data
  (
    frequencies,
    original_real,
    original_imaginary,
    compensated_real,
    compensated_imaginary
  ) = load_lag_design_data(filename)

  # Plot the function
  plot_lag_design(
    frequencies,
    original_real,
    original_imaginary,
    compensated_real,
    compensated_imaginary
  )

if __name__ == "__main__":
  main()
