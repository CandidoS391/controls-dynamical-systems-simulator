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

# Helper function for plotting the contour direction arrows
def add_contour_arrow(real_values, imaginary_values, start_idx, end_idx):
  plt.annotate(
    "",
    xy=(real_values[end_idx], imaginary_values[end_idx]),
    xytext=(real_values[start_idx], imaginary_values[start_idx]),
    arrowprops=dict(
      arrowstyle="->",
      linewidth=1.5
    )
  )

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

  # Calculate where the contour arrows should start and end
  original_arrow_1_start = find_nearest_frequency_index(frequencies, 0.4)
  original_arrow_1_end = find_nearest_frequency_index(frequencies, 0.6)

  original_arrow_2_start = find_nearest_frequency_index(frequencies, 2.5)
  original_arrow_2_end = find_nearest_frequency_index(frequencies, 3.5)  

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

  # Plot the mirrored branches for negative frequencies
  plt.plot(original_real, [-y for y in original_imaginary], color="tab:blue")
  plt.plot(compensated_real, [-y for y in compensated_imaginary], color="tab:orange")

  # Describe how the system remains stable
  plt.text(
    0.02,
    0.02,
    "Nyquist Stability\n"
    r"$P = 0$" "\n"
    r"$N = 0$" "\n"
    r"$Z = N + P = 0$" "\n"
    "Closed-loop stable",
    transform=plt.gca().transAxes,
    verticalalignment="bottom",
    bbox=dict(boxstyle="round", alpha=0.8)
  )

  # Add the low/mid/high markers for the unaltered response
  plt.scatter(original_real[low_index], original_imaginary[low_index])
  plt.scatter(original_real[mid_index], original_imaginary[mid_index])
  plt.scatter(original_real[high_index], original_imaginary[high_index])

  # Add the low/mid/high markers for the lead-compensated response
  plt.scatter(compensated_real[low_index], compensated_imaginary[low_index])
  plt.scatter(compensated_real[mid_index], compensated_imaginary[mid_index])
  plt.scatter(compensated_real[high_index], compensated_imaginary[high_index])

  # Add annotations to the low/mid/high markers added
  plt.annotate(
    r"Low: $\omega = 0.1$",
    xy=(compensated_real[low_index], compensated_imaginary[low_index]),
    xytext=(100, -15),
    textcoords="offset points"
  )

  plt.annotate(
    r"Mid: $\omega = \sqrt{5}$",
    xy=(compensated_real[mid_index], compensated_imaginary[mid_index]),
    xytext=(-75, -20),
    textcoords="offset points"
  )

  plt.annotate(
    r"High: $\omega = 10$",
    xy=(compensated_real[high_index], compensated_imaginary[high_index]),
    xytext=(20, 15),
    textcoords="offset points"
  )

  # Show how Lead compensation moves the low-frequency point
  plt.annotate(
      "",
      xy=(compensated_real[low_index], compensated_imaginary[low_index]),
      xytext=(original_real[low_index], original_imaginary[low_index]),
      arrowprops=dict(
          arrowstyle="->",
          linestyle="--",
          linewidth=1.5,
          shrinkA=5,
          shrinkB=5
      )
  )

  # Show how Lead compensation moves the mid-frequency point
  plt.annotate(
      "",
      xy=(compensated_real[mid_index], compensated_imaginary[mid_index]),
      xytext=(original_real[mid_index], original_imaginary[mid_index]),
      arrowprops=dict(
          arrowstyle="->",
          linestyle="--",
          linewidth=1.5,
          shrinkA=5,
          shrinkB=5
      )
  )

  # Show how Lead compensation moves the high-frequency point
  plt.annotate(
      "",
      xy=(compensated_real[high_index], compensated_imaginary[high_index]),
      xytext=(original_real[high_index], original_imaginary[high_index]),
      arrowprops=dict(
          arrowstyle="->",
          linestyle="--",
          linewidth=1.5,
          shrinkA=5,
          shrinkB=5
      )
  )

  # Add the direction arrows
  add_contour_arrow(
    original_real,
    original_imaginary,
    original_arrow_1_start,
    original_arrow_1_end
  )
  add_contour_arrow(
    original_real,
    original_imaginary,
    original_arrow_2_start,
    original_arrow_2_end
  )
  add_contour_arrow(
    compensated_real,
    compensated_imaginary,
    original_arrow_1_start,
    original_arrow_1_end
  )
  add_contour_arrow(
    compensated_real,
    compensated_imaginary,
    original_arrow_2_start,
    original_arrow_2_end
  )

  # Add the horizontal real-axis line and vertical imaginary axis line
  plt.axhline(0, color="black", linewidth=0.8)
  plt.axvline(0, color="black", linewidth=0.8)

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
  plt.title("Nyquist Design via Lead Compensation")

  # Enable the grid, legend, and axis
  plt.grid(True)
  plt.legend()
  plt.axis('equal')

  # Save the figure and then show it
  plt.savefig("output/nyquist_lead_design.png")
  plt.show()

def main():
  # Load up the filename
  filename = "output/nyquist_lead_design.csv"

  # Get the frequency, original real/imaginary data, and the compensated real/imaginary data
  (
    frequencies,
    original_real,
    original_imaginary,
    compensated_real,
    compensated_imaginary
  ) = load_lead_design_data(filename)

  # Plot the function
  plot_lead_design(
    frequencies,
    original_real,
    original_imaginary,
    compensated_real,
    compensated_imaginary
  )

if __name__ == "__main__":
  main()


