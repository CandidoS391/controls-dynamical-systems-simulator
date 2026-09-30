import csv
import matplotlib.pyplot as plt
import math

# Read in value from CSV file
def load_lag_lead_design_data(filename):
  # Create all the required lists to hold all the data
  frequencies = []
  original_real = []
  original_imaginary = []
  lag_lead_1_real = []
  lag_lead_1_imaginary = []
  lag_lead_2_real = []
  lag_lead_2_imaginary = []  
  lag_lead_3_real = []
  lag_lead_3_imaginary = []

  # Open up the file and start to read in the data row by row
  with open(filename, "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
      frequencies.append(float(row["frequency"]))
      original_real.append(float(row["original_real"]))
      original_imaginary.append(float(row["original_imaginary"]))

      lag_lead_1_real.append(float(row["lag_lead_1_real"]))
      lag_lead_1_imaginary.append(float(row["lag_lead_1_imaginary"]))

      lag_lead_2_real.append(float(row["lag_lead_2_real"]))
      lag_lead_2_imaginary.append(float(row["lag_lead_2_imaginary"]))

      lag_lead_3_real.append(float(row["lag_lead_3_real"]))
      lag_lead_3_imaginary.append(float(row["lag_lead_3_imaginary"]))

  return frequencies, original_real, original_imaginary, lag_lead_1_real, lag_lead_1_imaginary, lag_lead_2_real, lag_lead_2_imaginary, lag_lead_3_real, lag_lead_3_imaginary