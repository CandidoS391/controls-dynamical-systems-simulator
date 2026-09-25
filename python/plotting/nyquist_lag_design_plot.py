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

def find_nearest_frequency_index(frequencies, target_frequency):
    nearest_index = 0
    smallest_difference = abs(frequencies[0] - target_frequency)

    for i in range(1, len(frequencies)):
        current_difference = abs(frequencies[i] - target_frequency)

        if current_difference < smallest_difference:
            smallest_difference = current_difference
            nearest_index = i

    return nearest_index

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
