import csv
import matplotlib.pyplot as plt
import math

def load_lead_design_data(filename):
  # Define all of the lists required to hold all of the data
  frequencies = []
  original_real = []
  original_imaginary  = []
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
  # Set up the nearest_index and the smallest_difference variables
  nearest_index = 0

  smallest_difference = abs(frequencies[0] - target_frequency)

  for i in range(1, len(frequencies)):
    current_difference = abs(frequencies[i] - target_frequency)

    # If there exists a current_difference that is smaller than the
    # recorded distance, then set the smallest distance as that current distance
    # And record the index where it is at
    if current_difference < smallest_difference:
      smallest_difference = current_difference
      nearest_index = i

  return nearest_index

def plot_lead_design(frequencies, original_real, original_imaginary, compensated_real, compensated_imaginary):
  # Create a brand new lead design figure
  plt.figure()

  # Set low, mid, and high frequencies, as well as their corresponding indices
  low_frequency = 0.1
  mid_frequency = math.sqrt(1.0 * 5.0)
  high_frequency = 10.0

  low_index = find_nearest_frequency_index(frequencies, low_frequency)
  mid_index = find_nearest_frequency_index(frequencies, mid_frequency)
  high_index = find_nearest_frequency_index(frequencies, high_frequency)  

  # Plot the contour for the original response
  plt.plot(
    original_real,
    original_imaginary,
    label="Original"
  )

  # Plot the Lead-compensated response
  plt.plot(
    compensated_real,
    compensated_imaginary,
    label="Lead Compensated"
  )

  # Add the low/mid/high markers for the unaltered response
  plt.scatter(original_real[low_index], original_imaginary[low_index])
  plt.scatter(original_real[mid_index], original_imaginary[mid_index])
  plt.scatter(original_real[high_index], original_imaginary[high_index])

  # Add the low/mid/high markers for the lead-compensated response
  plt.scatter(compensated_real[low_index], compensated_imaginary[low_index])
  plt.scatter(compensated_real[mid_index], compensated_imaginary[mid_index])
  plt.scatter(compensated_real[high_index], compensated_imaginary[high_index])

  # Add the horizontal real-axis line and vertical imaginary axis line
  plt.axhline(0)
  plt.axvline(0)

  # Add the critical point and the corresponding label
  plt.scatter(-1, 0)
  plt.annotate(
    "-1 + j0",
    (-1, 0)
  )

  # Set the x-axis and y-axis labels
  plt.xlabel("Re")
  plt.ylabel("Im")

  # Title the plot
  plt.title("Nyquist Lead Compensation")

  # Enable the grid and legend
  plt.grid(True)
  plt.legend()

  plt.axis('equal')

  plt.savefig("output/nyquist_lead_design.png")
  plt.show()

def main():
  filename = "output/nyquist_lead_design.csv"

  (
    frequencies,
    original_real,
    original_imaginary,
    compensated_real,
    compensated_imaginary
  ) = load_lead_design_data(filename)

  plot_lead_design(
    frequencies,
    original_real,
    original_imaginary,
    compensated_real,
    compensated_imaginary
  )

if __name__ == "__main__":
  main()


