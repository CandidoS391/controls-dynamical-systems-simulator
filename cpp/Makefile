CXX := g++
CXXFLAGS := -Wall -Werror -std=c++17 -Iinclude

all: simulation

simulation: src/main.cc \
	src/StateVector.cc \
	src/FirstOrderDecay.cc \
	src/EulerIntegration.cc \
	src/HarmonicOscillator.cc \
	src/RK4Integration.cc \
	src/DampedOscillator.cc \
	src/ForcedOscillator.cc \
	src/SineSignal.cc \
	src/StepSignal.cc \
	src/ConstantSignal.cc \
	src/RampSignal.cc \
	src/ImpulseSignal.cc
	$(CXX) $(CXXFLAGS) \
	src/main.cc \
	src/StateVector.cc \
	src/FirstOrderDecay.cc \
	src/EulerIntegration.cc \
	src/HarmonicOscillator.cc \
	src/RK4Integration.cc \
	src/DampedOscillator.cc \
	src/ForcedOscillator.cc \
	src/SineSignal.cc \
	src/StepSignal.cc \
	src/ConstantSignal.cc \
	src/RampSignal.cc \
	src/ImpulseSignal.cc \
	-o simulation

run: simulation
	./simulation

clean:
	rm -f simulation