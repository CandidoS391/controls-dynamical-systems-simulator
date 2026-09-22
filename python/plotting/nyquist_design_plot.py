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

def plot_lead_design(frequencies, original_real, original_imaginary, compensated_real, compensated_imaginary):
  # Create a brand new lead design figure
  plt.figure()

  # Plot the original uncompensated plant
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


