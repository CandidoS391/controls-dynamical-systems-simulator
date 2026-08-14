import csv
import matplotlib.pyplot as plt

# Read in values from csv file
def read_frequency_response(filename):
  frequencies = []
  real_values = []
  imaginary_values = []

  with open(filename, "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
      frequencies.append(float(row["frequency"]))
      real_values.append(float(row["real"]))
      imaginary_values.append(float(row["imaginary"]))

  return frequencies, real_values, imaginary_values

def plot_polar_response(frequencies, real_values, imaginary_values):
  plt.figure()

  plt.plot(real_values, imaginary_values)

  # ------ Graphing the arrows -------
  # Starting off by selecting the locations along the curve where the arrows will be placed
  arrow_indices = [
    len(real_values) // 50,
    len(real_values) // 10,
    len(real_values) // 3
  ]

  # Plot arrows showing the direction of increasing frequency
  for arrow_index in arrow_indices:
    plt.annotate(
      "",
      xy=(
        real_values[arrow_index + 1],
        imaginary_values[arrow_index + 1]
      ),
      xytext=(
        real_values[arrow_index],
        imaginary_values[arrow_index]
      ),
      arrowprops=dict(arrowstyle="->")
    )

  # ------ Plotting certain frequencies on the polar plot ------
  # Frequencies meant to be label on the polar plot
  label_frequencies = [
    0.0,
    0.25,
    0.5,
    1.0,
    2.0,
    5.0,
    20.0
  ]

  # Find the closest frequency sample for each requested label
  for target_frequency in label_frequencies:
    closest_index = 0
    smallest_difference = abs(frequencies[0] - target_frequency)

    for i in range(1, len(frequencies)):
      current_difference = abs(frequencies[i] - target_frequency)

      if current_difference < smallest_difference:
        smallest_difference = current_difference
        closest_index = i

    # Mark the selected frequency on the plot
    plt.scatter(
      real_values[closest_index],
      imaginary_values[closest_index]
    )

    # Label the selected frequency
    plt.annotate(
      f"ω = {frequencies[closest_index]:.2f}",
      (
        real_values[closest_index],
        imaginary_values[closest_index]
      ) 
    )

  plt.xlabel("Re")
  plt.ylabel("Im")
  plt.title("Polar Plot of G(jω)")

  plt.axhline(0)
  plt.axvline(0)

  plt.grid(True)

  plt.savefig("output/polar_response.png")

  plt.show()

def main():
  frequencies, real_values, imaginary_values = read_frequency_response("output/frequency_response.csv")
  plot_polar_response(frequencies, real_values, imaginary_values)

if __name__ == "__main__":
  main()
