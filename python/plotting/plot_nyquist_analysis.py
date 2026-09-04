import csv
import matplotlib.pyplot as plt
import math

# Read in value from csv file
def read_nyquist_analysis(filename):
  s_real_values = []
  s_imaginary_values = []
  mapped_real_values = []
  mapped_imaginary_values = []

  with open(filename, "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
      s_real_values.append(float(row["s_real"]))
      s_imaginary_values.append(float(row["s_imaginary"]))
      mapped_real_values.append(float(row["mapped_real"]))
      mapped_imaginary_values.append(float(row["mapped_imaginary"]))

  return s_real_values, s_imaginary_values, mapped_real_values, mapped_imaginary_values

# Read in myquist metrics
def read_nyquist_metrics(filename):
  with open(filename, "r") as file:
    reader = csv.DictReader(file)
    row = next(reader)

    phase_crossover_frequency = float(
      row["phase_crossover_frequency"]
    )
    phase_crossover_real = float(
      row["phase_crossover_real"]
    )
    phase_crossover_imaginary = float(
      row["phase_crossover_imaginary"]
    )
    gain_margin = float(
      row["gain_margin"]
    )
    gain_crossover_frequency = float(
      row["gain_crossover_frequency"]
    )
    gain_crossover_real = float(
      row["gain_crossover_real"]
    )
    gain_crossover_imaginary = float(
     row["gain_crossover_imaginary"] 
    )
    phase_margin = float(
      row["phase_margin"]
    )

  return (
    phase_crossover_frequency,
    phase_crossover_real,
    phase_crossover_imaginary,
    gain_margin,
    gain_crossover_frequency,
    gain_crossover_real,
    gain_crossover_imaginary,
    phase_margin
  )

def calculate_m_values(mapped_real_values, mapped_imaginary_values):
  # Verify that the mapped arrays have the same length
  if len(mapped_real_values) != len(mapped_imaginary_values):
    raise ValueError("Mapped real and imaginary values must have the same length.")
  
  m_values = []

  for i in range(len(mapped_real_values)):
    # Construct L from the mapped real and imaginary values
    L = complex(mapped_real_values[i], mapped_imaginary_values[i])

    # Check whether the denominator (1 + L) is too close to zero
    denominator = 1 + L
    if abs(denominator) < 1e-8:
      continue

    # Calculate the closed loop, and by extension M
    closed_loop = L / denominator
    M = abs(closed_loop)

    if math.isfinite(M):
      m_values.append(M)

  return m_values

# Get the m range based on the m values
def get_m_range(m_values):
  # Verify that the m_values list is not empty
  if len(m_values) == 0:
    raise ValueError("M values cannot be empty.")

  # Find the minimum and maximum values present, then return it
  min_m = min(m_values)
  max_m = max(m_values)

  return min_m, max_m

# Generate M level circles
def generate_m_levels(min_m, max_m, num_levels):
  # Validate the inputs
  if num_levels < 2:
    raise ValueError("There must be at least than 2 M-levels to be graphed.")

  if min_m < 0:
    raise ValueError("The minimum of M cannot be negative.")

  if max_m <= min_m:
    raise ValueError("The maximum of M must be greater than the minimum of M.")

  # Calculate the spacing between the M levels
  linear_step = (max_m - min_m) / (num_levels - 1)

  m_levels = []

  # For each level, calculate the M value representing that level
  for i in range(num_levels):
    M = min_m + i * linear_step
    m_levels.append(M)

  return m_levels

# Calculate the M circle
def calculate_m_circle(M):
  # Validiate passed in M
  if M < 0:
    raise ValueError("M cannot be negative.")

  # Calculate the denominator used by the M-circle
  denominator = (M ** 2) - 1

  # Special case if M = 1
  if abs(denominator) < 1e-8:
    return {
      "type": "line",
      "x": -0.5 
    }

  # Calculate the x-coordinate of the circle's center
  center_x = -(M ** 2) / denominator

  # All M-circle centers lie on the real axis
  center_y = 0

  # calculate the radius
  radius = M / abs(denominator)

  # return the circle geometry
  return {
    "type": "circle",
    "center_x": center_x,
    "center_y": center_y,
    "radius": radius
  }

# Generate the points needed for the M circle
def generate_m_circle_points(geometry, num_points):
  # Validate the number of points
  if num_points < 2:
    raise ValueError("The number of points must be at least 2.")

  # Determine what kind of M-contour was passed in
  if geometry["type"] == "line":
    # M = 1 is not a cricle, therefore circular points must not be generated
    return "The geometry is NOT a circle, it's a line."

  if geometry["type"] != "circle":
    raise ValueError("Invalid geometric type (Line or Circle).")

  # Extract the circle geometry
  center_x = geometry["center_x"]
  center_y = geometry["center_y"]
  radius = geometry["radius"]

  # Create empty coordinate lists
  x_values = []
  y_values = []

  # Generate points from 0 to 2pi
  for i in range(num_points):
    # Convert the current index into an angle
    # num_points - 1 ensures the final point reaches exactly 2pi
    theta = i * (2 * math.pi) / (num_points - 1)

    # Parameterize the circle
    x = center_x + radius * math.cos(theta)
    y = center_y + radius * math.sin(theta)

    # Store this point
    x_values.append(x)
    y_values.append(y)

  # Return coordinates for Matplotlib
  return x_values, y_values

def plot_nyquist(s_real_values, s_imaginary_values, mapped_real_values, mapped_imaginary_values, phase_crossover_frequency, phase_crossover_real, phase_crossover_imaginary, gain_margin, gain_crossover_frequency, gain_crossover_real, gain_crossover_imaginary, phase_margin):
  plt.plot(mapped_real_values, mapped_imaginary_values)

  # ---- Plotting the direction arrows
  # Frequencies where arrows should start
  # Frequencies where direction arrows should be placed
  arrow_frequencies = [
    0.5,
    2.0,
    -2.0,
    -0.5
  ]

  # Controls the visible length of each arrow
  arrow_length = 0.06

  for target_frequency in arrow_frequencies:
    closest_index = 0
    smallest_difference = float("inf")

    # Find the point on the imaginary axis closest
    # to the desired frequency
    for i in range(len(s_real_values)):
      if abs(s_real_values[i]) < 1e-8:
        current_difference = abs(
          s_imaginary_values[i] - target_frequency
        )

        if current_difference < smallest_difference:
          smallest_difference = current_difference
          closest_index = i

    # Make sure there are neighboring points available
    if closest_index == 0:
      continue

    if closest_index == len(mapped_real_values) - 1:
      continue

    # Use neighboring mapped points to estimate
    # the local tangent direction of the curve
    delta_real = (
      mapped_real_values[closest_index + 1]
      - mapped_real_values[closest_index - 1]
    )

    delta_imaginary = (
      mapped_imaginary_values[closest_index + 1]
      - mapped_imaginary_values[closest_index - 1]
    )

    # Find the length of the tangent vector
    direction_length = math.hypot(
      delta_real,
      delta_imaginary
    )

    if direction_length < 1e-8:
      continue

    # Normalize the tangent direction
    unit_real = delta_real / direction_length
    unit_imaginary = delta_imaginary / direction_length

    # Construct a short arrow following the tangent
    arrow_end_real = (
      mapped_real_values[closest_index]
      + arrow_length * unit_real
    )

    arrow_end_imaginary = (
      mapped_imaginary_values[closest_index]
      + arrow_length * unit_imaginary
    )

    # Draw the direction arrow
    plt.annotate(
      "",
      xy=(
        arrow_end_real,
        arrow_end_imaginary
      ),
      xytext=(
        mapped_real_values[closest_index],
        mapped_imaginary_values[closest_index]
      ),
      arrowprops=dict(arrowstyle="->")
    )

  # ---- Plotting Frequencies ----
  label_frequencies = [
    0.0,
    0.25,
    0.5,
    1.0,
    2.0,
    5.0,
    10.0
  ]

  arrow_frequency_step = 0.1

  for target_frequency in label_frequencies:
    closest_index = 0
    smallest_difference = float("inf")

    for i in range(len(s_real_values)):
      # Consider points on the imaginary axis
      if abs(s_real_values[i]) < 1e-8:
        current_difference = abs(
          s_imaginary_values[i] - target_frequency
        )

        if current_difference < smallest_difference:
          smallest_difference = current_difference
          closest_index = i

    # Mark the mapped locations
    plt.scatter(
      mapped_real_values[closest_index],
      mapped_imaginary_values[closest_index]
    )

    # Label the corresponding frequency
    plt.annotate(
      f"ω = {s_imaginary_values[closest_index]:.2f}",
      (
        mapped_real_values[closest_index],
        mapped_imaginary_values[closest_index]
      )
    )

  # Mark the Nyquist crtiical point
  plt.scatter(-1.0, 0.0)

  plt.annotate(
    "(-1, 0)",
    (-1.0, 0.0)
  )

  # Mark the phase-crossover point
  plt.scatter(
    phase_crossover_real,
    phase_crossover_imaginary,
    zorder=6
  )

  # Mark the gain-crossover point
  plt.scatter(
    gain_crossover_real,
    gain_crossover_imaginary,
    zorder=6
  )

  # Draw the gain-margin indicator
  plt.plot(
    [phase_crossover_real, -1.0],
    [phase_crossover_imaginary, 0.0],
    linestyle="--"
  )

  # Draw the radius to the gain-crossover point
  plt.plot(
    [0.0, gain_crossover_real],
    [0.0, gain_crossover_imaginary],
    linestyle="--"
  )

  # Draw the negative real-axis reference
  plt.plot(
    [0.0, -1.0],
    [0.0, 0.0],
    linestyle="--"
  )

  # ---- Phase Margin Arc ----
  arc_radius = 0.20
  num_arc_points = 100

  gain_crossover_angle = math.atan2(
    gain_crossover_imaginary,
    gain_crossover_real
  )

  arc_angles = [
    -math.pi + i * (
      gain_crossover_angle + math.pi
    ) / (num_arc_points - 1)
    for i in range(num_arc_points)
  ]

  arc_real = [
    arc_radius * math.cos(angle)
    for angle in arc_angles
  ]

  arc_imaginary = [
    arc_radius * math.sin(angle)
    for angle in arc_angles
  ]

  plt.plot(
    arc_real,
    arc_imaginary
  )

  # Reference for the crossover angle
  reference_real = -arc_radius

  crossover_ray_real = (
    arc_radius * math.cos(gain_crossover_angle)
  )
  crossover_ray_imaginary = (
    arc_radius * math.sin(gain_crossover_angle)
  )

  plt.plot(
    [0.0, reference_real],
    [0.0, 0.0],
    linestyle="--"
  )

  plt.plot(
    [0.0, crossover_ray_real],
    [0.0, crossover_ray_imaginary],
    linestyle="--"
  )

  # Annotate the actual numerical gain margin
  plt.annotate(
    f"GM = {gain_margin:.2f}\n"
    f"$\\omega_{{pc}}$ = {phase_crossover_frequency:.2f}",
    (phase_crossover_real, phase_crossover_imaginary),
    xytext=(-75, 55),
    textcoords="offset points",
    arrowprops=dict(arrowstyle="->")
  )

  # Annotate the actual numerical phase margin
  plt.annotate(
    f"PM = {phase_margin:.2f}°\n"
    f"$\\omega_{{gc}}$ = {gain_crossover_frequency:.2f}",
    (gain_crossover_real, gain_crossover_imaginary),
    xytext=(55, 25),
    textcoords="offset points",
    arrowprops=dict(arrowstyle="->")
  )



  # Plot formatting
  plt.xlabel("Re")
  plt.ylabel("Im")
  plt.title("Nyquist plot")

  plt.axhline(0)
  plt.axvline(0)

  plt.grid(True)


def plot_m_circles(m_levels, num_points):
  # Validate the inputs
  if len(m_levels) == 0:
    raise ValueError("There is no m-levels passed in.")

  if num_points < 2:
    raise ValueError("The number of points must be at least 2 or greater.")

  # Loop through each m-level
  for m in m_levels:
    # Determine whether or not the M-level is a circle or a line
    geometry = calculate_m_circle(m)

    # Special case: M = 1
    if geometry["type"] == "line":
      plt.axvline(
        x = geometry["x"]
      )
      continue

    # Ordinary M-circle case
    if geometry["type"] == "circle":
      x_values, y_values = generate_m_circle_points(
        geometry,
        num_points
      )
      plt.plot(
        x_values,
        y_values
      )
      continue

    # Defensive case in case an invalid geometric type is catched
    raise ValueError("There exists an invalid geometric type.")



def main():
  # Read Nyquist path data
  (
    s_real_values,
    s_imaginary_values,
    mapped_real_values,
    mapped_imaginary_values
  ) = read_nyquist_analysis(
    "output/nyquist_data.csv"
  )

  # Read Nyquist relative-stability metrics
  (
    phase_crossover_frequency,
    phase_crossover_real,
    phase_crossover_imaginary,
    gain_margin,
    gain_crossover_frequency,
    gain_crossover_real,
    gain_crossover_imaginary,
    phase_margin
  ) = read_nyquist_metrics(
    "output/nyquist_metrics.csv"
  )

  # Calculate M values from the mapped Nyquist response
  m_values = calculate_m_values(
    mapped_real_values,
    mapped_imaginary_values
  )

  # Find the observed M range
  min_m, max_m = get_m_range(
    m_values
  )

  # Automatically generate the M levels
  m_levels = generate_m_levels(
    min_m,
    max_m,
    5
  )

  # Create one shared matplotlib figure
  plt.figure()

  # Plot Nyquist Response
  plot_nyquist(
    s_real_values,
    s_imaginary_values,
    mapped_real_values,
    mapped_imaginary_values,
    phase_crossover_frequency,
    phase_crossover_real,
    phase_crossover_imaginary,
    gain_margin,
    gain_crossover_frequency,
    gain_crossover_real,
    gain_crossover_imaginary,
    phase_margin
  )

  # Overlay the M circles on the same figure
  plot_m_circles(
    m_levels,
    200
  )

  # Save and display only after every overlay
  plt.savefig(
    "output/nyquist_plot.png"
  )

  plt.show()


if __name__ == "__main__":
  main()
  

