import matplotlib.pyplot as plt
import csv
import sys
import os

def PlotSPlane(filename):
  pole_real = []
  pole_imag = []
  zero_real = []
  zero_imag = []

  with open(filename, mode='r') as csv_file:
    next(csv_file)
    reader = csv.reader(csv_file)

    for row in reader:
      point_type = row[0]
      real = float(row[1])
      imaginary = float(row[2])

      if point_type == "pole":
        pole_real.append(real)
        pole_imag.append(imaginary)
      elif point_type == "zero":
        zero_real.append(real)
        zero_imag.append(imaginary)
  
  plt.figure()

  plt.scatter(pole_real, pole_imag, marker="x", label="Poles")
  plt.scatter(zero_real, zero_imag, marker="o", label="Zeros")

  plt.axhline(0)
  plt.axvline(0)

  plt.title("Pole-Zero Map")
  plt.xlabel("Real Axis")
  plt.ylabel("Imaginary Axis")

  plt.grid(True)
  plt.legend()

  output_filename = os.path.splitext(filename)[0] + ".png"
  plt.savefig(output_filename)
  plt.show()

if len(sys.argv) < 2:
  print("USAGE: python3 plot_s_plane.py <csv_file>")
else:
  PlotSPlane(sys.argv[1])


