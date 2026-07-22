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

# The Input Signals
This simulator besides oscillators also supports several input signal models that can be applied to the forced dynamical systems represented by the forced oscillator. These include the:

## Sine Signal
A sinusoidial input models periodic forcing applied to a system and is Denoted as:

```math
u(t)=A\sin(\omega t)
```

This signal is commonly used to study oscillatory behavior, resonance and frequency-dependent responses. Here, the amplitude $A$ controls the strenght of the forcing while the angular frequency $\omega$ determines how rapid the input oscillates. this signal has applications in:

- Mechanical vibrations
- AC electrical circuits
- Resonance Studies

## The Step Signal
A step response is used to measure how a dynamical system reacts to a sudden change in input. It is represented by the **Unit Step Function**, denoted as $u(t - t_0)$ and defined by:

$$
u(t - t_0) =
\begin{cases}
0 \quad & t \le 0 \\
1 \quad & t > 0
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

The applications of this signal include:

- Control-system testing
- Setpoint changes
- Motor Activation
- Stability Analyis

## The Constant Signal
A constant signal applies a fixed input to the system for the whole duration of the simulation. It is denoted as:

$$
u(t) = A
$$

this type of forcing is useful for stduying equilibrium behavior and long-term steady state responses, with applications including:

- Static loading
- constant force analysis
- DC voltage inputs
- Equilibrium studies

## The Ramp Signal
A ramp signal increases linearly with time after a specified starting point and is denoted as:

$$
u(t) =
\begin{cases}
0 \quad t < t_0 \\
m(t - t_0) \quad t \ge t_0
\end{cases}
$$

Unlike a step input, a ramp input grows gradually and continuously. Ramp responses are frequently used in control engineering to evaluate a system's ability to track changing inputs and to study steady-state tracking error. Applications include:

- Tracking performance analysis
- Guidance Systems
- Motion control
- Slowly increasing loads

## The Pulse Signal
A pulse signal applies a temporary input to the system for a finite duration (i.e from $t_{start}$ to $t_{end}$) before returning to zero. Such signal can be denoted as:

$$
u(t) =
\begin{cases}
0 \quad t < t_{start} \\
A \quad t_{start} \le t \le t_{end} \\
0 \quad t > t_{end}
\end{cases}
$$

This type of signal is useful for studying transient effects, distrubances, and the natural response of a system after external forcing is removed. Short pulse can also approximate impulse-like excitations. Applications include:

- Disturbance rejection studies
- Impact and shock loading
- Transient analysis
- Impulse-response approximations

# The Transfer Function
Besides Dynamical systems and oscillators, this project also covers transfer functions which describes the relationship between a system's input and output within an $s$-plane, found by transforming its given differential equation into an algebraic equation using a Laplace transform. By doing such transformation, transfer functions provide a convenient way to analyze and design dynamic systems.

Transfer functions serve as the basis of control system analysis as instead of having to solve directly a bunch of differential equations that govern a dynamical system, transfer functions simplify said differential equations into simple algebraic equations, which makes analyzing the stability, the frequency response, the feedback control, and the interconnections of the system, easier.

Within this project, a transfer function is represented by the `TransferFunction` class, and is defined as:

$$
G(s) = \frac{N(s)}{D(s)}
$$

in which within the class, $N(s)$, the numerator, and $D(s)$, the denominator are represented by two vectors.

Within the `TransferFunction` class, there are private helper functions that evaluates the polynomials $N(s)$ and $D(s)$ at a specified value $s$, evaluates the degree of the polynomials, as well as perform several operations including adding, subtracting, dividing, and taking the derivative of the polynomials.

## Zeros and Poles
In a transfer function, the terms **poles** and **zeros** refer to the roots of the denominator polynomial and numerator polynomial of the transfer function respectively. On one hand, poles represent the frequencies or conditions for where the system's output theoretically approaches infinity, and act as *attractors* for signals. On the other hand, zeros represent frequencies or conditions where the output is perfectly zero, and act as *repellors* for signals.

Poles are important as they determine the stability of the system (See Stability section for more detail), whereas zeros shape the transient response (e.g how fast a system reacts) and the frequency response.

For this project, the `TransferFunction` class include functions that calculate the poles and zeros of a transfer function by simply calculating the roots of polynomial, using a private helper.

Additionally, this project also allows for the graphing of poles and zeros, as through python's matplotlib graphing capabilities, a transfer functions poles and zeros can be graphed on a **pole-zero map**, in which poles are represented with an 'x', while zeros are represented with a circle. See the plotting files for an example.

## Stability of a Transfer Function
Within the study of transfer functions, the stability of said functions are critical as stability dictates whether a system's output remains bounded in response to an input. If a system is deemed *unstable*, the said system can produce outputs that grow exponentially, leading to unpredictable behavior in the control system.

The stability of transfer functions are determined by the system's poles, or in other words the roots of the denominator polynomial $D(s)$. By setting $D(s) = 0$, we get the **characteristic equation** of the transfer function, and by plotting it out on a **pole-zero map**, which sits on a complex $s$-plane, we can determine the following stabilities:

- If all poles of the system have stricly negative real parts (i.e they lay on the **Left-Half Plane** for $\text{Re}(s) < 0$>), that means the output decays over time and that the system is **stable**.
- If at least one pole has one positive real part (i.e there's a pole graphed on the **Right-Half Plane** for $\text{Re}(s) > 0$, then output will grow exponentially, deeming the system as **unstable**).
- If poles are situatied on the imaginary axis (i.e $\text{Re}(s) = 0$), then oscillations are sustained, and the system is **marginally stable**.

### Routh-Hurwitz Stability Criterion and Routh Tables
Whilst this project can calculate the roots $n^{th}$ order polynomials using the Durand-Kerner method, another way that the stability of a transfer function can be determined is via the **Routh-Hurwitz stability criterion**. Instead of calculating roots, this method uses a structured array called the **Routh table** based on the coefficients of the characteristic equation.

A Routh table is built in the following order:
- First the coefficients of the characteristic equations are arranged in descending powers of $s$ from $s^n$ to $s^0$.
- Next, the first two rows are populated with the coefficients in an alternating pattern.
- For all subsequent rows, they're calcualted by using a cross-multiplication determinant formula (divide by the leading term of the row directly above) until the table is complete.

#### Example Routh Table

Given the characteristic polynomial

$$
P\(s\) \= s\^3 \+ 6s\^2 \+ 11s \+ 6
$$

the corresponding Routh table is:

| Power of $s$ | Column 1 | Column 2 |
|----------------|----------|----------|
| $s^3$ | 1 | 11 |
| $s^2$ | 6 | 6 |
| $s^1$ | 10 | 0 |
| $s^0$ | 6 | 0 |

The first column is:

$$
1\,\\\;6\,\\\;10\,\\\;6
$$

Since there are no sign changes in the first column, the system is **stable**.

Once the table is filled, the stability is determined based only on the **first column** of the array:
- A system is stable if and only if every element in the first column is positive
- If there are changes in the sign of the elements in the first column, then the system is unstable. Furthermore, the exact number of sign changes equals the number of unstable poles that are located in the right half plane of the complex $s$-plane.
- If there exists a row of zeros within the table, then it signals that the system has roots on the imaginary axis and therefore the system is marginally stable.

In this project, Routh Tables have their own separate class, in which the table itself is built on a vector of vectors of double type. This class can:
- Construct Routh Tables from given characteristic polynomial coefficients.
- Classfy the systems based on the aforementioned classifications.
- Detect sign changes in the first column of the Routh table to determine the number of right-half-plane poles
- Handle zero first-colum elements using the epsilon substitution method.
- Handle rows of zeros using the auxiliary polynomial method.
- Print out a completed Routh table in a way that is readable to humans.

# How Systems are Represented
Within control system theory, there are two main ways of representing a control system, a block diagram and a signal flow graph.

A block diagram uses functional blocks, summing junctions and take-off points to visualize the flow of signals through subsystems. Looking more in detail:

- Blocks: Represent system components or operations.
- Summing Points: Circles where signals are either added or subtracted.
- Take-off Points: Locations where a signal branches off to multiple destinations.

A signal flow graph on the otherhand is more streamlined, consisting of only nodes that represent a signal/variable, and directional branches that represents the "branch gains" of the system. What makes flow graphs more advantageous compared to block diagrams is that using a flow graph allows engineers and mathematicians to compute the system's overall transfer function using something called **Mason's gain formula**, which is defined as:

$$
T = \frac{\sum_{i} P_i \Delta_{i}}{\Delta}
$$

in which three components are calculated:
- $P_i$ represents the $i$ number of forward paths, or the continuous, unidirectional paths from the input node to the output node
- $\Delta$ represents the determinant of the graph, which is calculated using all the loops in the signal flow graph, with the equation being: $\Delta = 1 - \sum (\text{Individual loop gains}) + \sum (\text{Gain products of all possible two non-touching loops}) - \sum (\text{Gain products of all possible three non-touching loops}) \ldots$
- $\Delta_{i}$ represents cofactor of the $i^{th}$ path of $\Delta$ for the portion of the graph that does **not touch** the $i^{th}$ forward path. If all loops touch the $i^{th}$ forward path, then $\Delta_{i} = 1$.

*Footnote: A loop gain (L) is the product of all branch gains that form from a loop (a closed path that begins and ends at the same node). While a loop is considered to be non-touching if the loop does not share any common nodes.*

In this project, Signal Flow Graphs are represented by the `SignalFlowGraph` class, with functions being able to add Nodes and Branches, find Forward Paths using Depth-First Search, and calculate all parts needed for Mason's Gain Formula.

# Feedback Systems
A **feedback system** is a type of control system, in which a process where the output of an action or system is circled back and used as a new input, to regulate, correct, or enhance future performance.

## Components of a Feedback System
Within a standard feedback system, the following components are featured:
- **Reference Input**: The target value or state the system needs to reach.
- **Controller**: The "brain" of the system that calculates the corrective action based on the error.
- **Actuator**: The physical mechanism that drives the system or process.
- **Plant**: The dynamic system or process that's being controlled (i.e a motor, heater, or engine).
- **Sensor**: The elements used to measure the actual input, closing the loop

## Types of Feedback
The way that the measured signal is applied back to the input defines the type of feedback
- **Negative Feedback**: Used in most control systems, this reduces the difference between the reference and the measured output, improving stability and reduces the system sensitivity to parameter variations. The transfer function for a closed-loop negative feedback system is defined as: $T(s) = \frac{G(s)}{1 + G(s)H(s)}$ For $G(s)$ is the open-loop plant gain, and $H(s)$ is the feedback path gain.
- **Positive Feedback**: the feedback signal is *added* to the reference, amplifying the signal in-phase and increasing the overall system gain.

## Implementation in this Project
In this project, Feedback Systems are represented by the `FeedbackSystem` class, in which the forward path (or the main path of the system), as well as the feedback path (the path in which the output is fed back into the input), are represented by objects of the `TransferFunction` class. Additionally, there's another object of the `TransferFunction` class that represents the desired transfer function of the system, which simply represents the transfer function of the system in desired conditions. This `desired_transfer_function` plays importance in calculating the **error** of the system, or the difference between the aforementioned desired function and the actual transfer function representing the system, a job taken care of by the `GetTransferError()` function.

Other functions besides basic accessor functions include `GetLoopTransferFunction()`, which calculates multiplying $G(s)$ and $H(s)$ together; `GetClosedLoopTransferFunction()`, which calculates the main transfer function for the feedback system; and `EvaluateErrorConstant()` function that evaluates the error constant, something that will be discussed in the next section. 

# System Types, Error Constants, and Sensitivity

## System Type Definition
In control system theory, a **system type** is a metric that describes a closed-loop's ability to track standard input signals. In a technical sense, if an open-loop transfer function of a system is defined/written as:

$$
G(s)H(s) = \frac{K \prod_{i=1}^{m}(s + z_i)}{s^l \prod_{i=1}^{n} (s + p_i)}
$$

then here, $l$ represents the system type, for which using the definition of a transfer function, that means there are $l$ open-loop poles at the origin $(s = 0)$.

System types are important in control systems theory as they serve a purpose of determining the **steady-state error**, or in other words the difference between the desired input, and the actual output after the system's transient response has died out.

## Error Constants
This leads into the concept of **error constants**, in which there are three types of error constants: **position** $(K_p)$, **velocity** $(K_v)$, and **acceleration** $(K_p)$. These constants define the system's steady-state error $(e_{ss})$ when tracking standard inputs (step, ramp, and parabolic respectively). The magnitude of these constants - and the resulting error - depends entirely on the system type.

### Position Error Constants
The **position error constant** $K_p$ for an type *stable* $l$ system is defined as:

$$
K_P \equiv \lim_{s \to 0} G(s) = \lim_{s \to 0} \frac{K B_1(s)}{s^l B_2(s)} =
\begin{cases}
\frac{K B_1(0)}{B_2(0)}, l = 0 \\
\infty, l > 0
\end{cases}
$$

The steady state error for a *stable* type $l$ system when the input is the unit-step function is

$$
e_{ss} = \lim_{t \to \infty} e_{ss} = \frac{1}{1 + K_p}
$$

### Velocity Error Constants
The **velocity error constant** $K_v$ for a *stable* type $l$ system is defined as:

$$
K_v \equiv \lim_{s \to 0} sG(s) = \lim_{s \to 0} \frac{K B_1(s)}{s^{l-1}B_2(s)} =
\begin{cases}
0 \quad l = 0 \\
\frac{K B_1(0)}{B_2(0)} \quad l = 1 \\
\infty \quad l > 1
\end{cases}
$$

The steady-state error for a *stable* type $l$ system when the input is the unit-ramp function is

$$
e_{ss} = \frac{1}{K_v}
$$

### Acceleration Error Constants
The **acceleration error constant** $K_a$ of type $l$ system is defined as:

$$
K_a \equiv \lim_{s \to 0} s^2 G(s) = \lim_{s \to 0} \frac{K B_1(s)}{s^{l-2} B_2(s)} =
\begin{cases}
0 \quad l = 0,1 \\
\frac{K B_1(0)}{B_2(0)} \quad l = 2 \\
\infty \quad l > 2
\end{cases}
$$

The steady-state error of a *stable* type $l$ system when the input is a unit-parabolic function is:

$$
e_{ss} = \frac{1}{K_a}
$$

# The RLC Circuit
So far, the only part of this project that is related to the Electromagnetic section and that is the RLC Circuit.

An series RLC circuit is a fundamental electrical engineering system that is consists of a resistor $R$, an inductor $L$, and a capacitor $C$; and is governed by this differential equation:

$$
L\frac{d^2q}{dt^2} + R\frac{dq}{dt} + \frac{1}{C}q = V(t)
$$

for $q(t)$ is the electrical charge stored on the capacitor, $\frac{dq}{dt}$ is the circuit current, and $V(t)$ is the applied input voltage.

Here, It is similar to the mechanical oscillator implemented via the forced oscillator in this project. So therefore with the existing numerical framework, the simulator can generate the circuit's step response and phase portrait the same way as a mechanical oscillator can be generated via both Euler's and RK4 Integration.

# The Future of this Project
As this project is in work-in-progress, more things will be added on. Eventually this project will also be able to do:

- Transfer Function Models (WIP)
- Block Diagram Simulation
- Signal Flow Graph Analysis
- Bode Plot Generation
- Root Locus Analysis
- Nyquis Analysis
- RLC Circuit Models (WIP)
- Electromagnetic Wave Simulations

As such, keep an eye out for new additions as they are being added on!