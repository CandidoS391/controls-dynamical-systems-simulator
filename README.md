This is a current work-in-process project for the summer of 2026, in which using dynamical systems, Euler and RK4 Integration, oscillators,controls-oriented systems, and electromagnetic signals and waves are simulated numerically using an Object-Oriented design language in C++ and visually displayed using Python/matplotlib.

# Dynamical Systems and Oscillators

Using Euler's and RK4 Integration, Ordinary Differential Equations are solved numerically and produce the behvaior of dynamical systems that are shown through time-domain plots and phase portraits.

Below are the main oscillators being studied using this numerical simulator:

## The Harmonic Oscillator
defined as:

$$
\ddot{x} + kx = 0
$$

For $x(t)$ is the position at time $t$, $\dot{x}(t)$ represents the velocity, and $\ddot{x}(t)$ is the acceleration at that time. Meanwhile $k$ represents the stiffness or restoring force coefficient of the oscillator. 

Here, the harmonic oscillator represents an ideal spring-mass system with energy being lost. As total energy remains constant, that leads in itself to a constant amplitude, which ultimately leads to the oscillator to continue oscillating forever.

This type of oscillator applies to various physical systems like a mass attached to a spring, a pendulum (with a small-angle approximation), and ideal LC circuits in electrical engineering.

## The Damped Oscillator
defined as:

$$
\ddot{x} + c\dot{x} + kx = 0
$$

Here with constants $c$ and $k$ representing the damping and stiffness coefficient respectively, now this oscillator represents a spring-mass system with some friction or resistance added on. With this friction applied, it causes the oscillator to lose energy and amplitude, causing motion to settle to equilibrium as $t \to \infty$, for $t$ denotes time.

As within the real-world, most phyiscal systems experience some form of damping - whether it is underdamped, or overdamped - the damped oscillator serves as the basis for stability analysis with many applications being found in the suspension of a car, RLC circuits with resistance, and in Mechanical vibrations with friction. 

## The Forced Oscillator
defined as:

$$
\ddot{x} + c\dot{x} + kx = A\sin{\omega t}
$$

For $A$ is the forcing amplitude, and $\omega$ is the forcing angular frequency.

Here a damped system much like the oscillator in the previous section is subjected to some form of external input, such as the motion caused by an earthquake, or the driving AC voltage to an electrical circuit.

For this oscillator, the behaviors studied form the basis of control system theory as given some external input, the responses of the system such as the steady-state response (which studies the response of the system that does not approach 0) or the transient response (the complete opposite of the steady-state) can be studied to specify the control system performance.

# The Step Response
For the forced oscillator and for this simulator in general, a step response is used to measure how a dynamical system reacts to a sudden change in input. It is represented by the **Unit Step Function**, denoted as $u(t - t_0)$ and defined by:

$$
u(t - t_0) =
\begin{cases}
0, & t \le 0 \\
1, & t > 0
\end{cases}
$$

The step response is one of the most important tools in control systems engineering because it provides insight into a system's transient and steady-state behavior. For instance depending on the system's parameters, the response may exhibit behaviors such as:

- Overshooting
- Oscillations
- Settling Behavior
- Steady-State error

And it is used to study:

- Rise Time
- Peak Time
- Maximum Overshoot
- Settling Timne
- Steady-State Value

For this project, the simulator uses both Euler's method and RK4 Integration to calculate the step response.


# The Future of this Project
As this project is in work-in-progress, more things will be added on. Eventually this project will also be able to do:

- Transfer Function Models
- Block Diagram Simulation
- Signal Flow Graph Analysis
- Bode Plot Generation
- Root Locus Analysis
- Nyquis Analysis
- RLC Circuit Models
- Electromagnetic Wave Simulations

As such, keep an eye out for new additions as they are being added on!