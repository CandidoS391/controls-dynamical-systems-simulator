import csv
import matplotlib.pyplot as plt

def read_frequency_response(filename):
  real_values = []
  imaginary_values = []

  with open(filename, "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
      real_values.append(float(row["real"]))
      imaginary_values.append(float(row["imaginary"]))

  return real_values, imaginary_values

def plot_polar_response(real_values, imaginary_values):
  plt.figure()

  plt.plot(real_values, imaginary_values)

  plt.xlabel("Re")
  plt.ylabel("Im")
  plt.title("Polar Plot of G(jω)")

  plt.axhline(0)
  plt.axvline(0)

  plt.grid(True)

  plt.savefig("output/polar_response.png")

  plt.show()

def main():
  real_values, imaginary_values = read_frequency_response("output/frequency_response.csv")
  plot_polar_response(real_values, imaginary_values)

if __name__ == "__main__":
  main()
