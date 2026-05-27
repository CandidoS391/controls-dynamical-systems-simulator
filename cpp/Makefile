CXX := g++
CXXFLAGS := -Wall -Werror -std=c++17 -Icpp/include

all: simulation

simulation: cpp/src/main.cc cpp/src/StateVector.cc cpp/src/FirstOrderDecay.cc cpp/src/EulerIntegration.cc cpp/src/HarmonicOscillator.cc cpp/src/RK4Integration.cc cpp/src/DampedOscillator.cc cpp/src/ForcedOscillator.cc
	$(CXX) $(CXXFLAGS) \
	cpp/src/main.cc \
	cpp/src/StateVector.cc \
	cpp/src/FirstOrderDecay.cc \
	cpp/src/EulerIntegration.cc \
	cpp/src/HarmonicOscillator.cc \
	cpp/src/RK4Integration.cc \
	cpp/src/DampedOscillator.cc \
	cpp/src/ForcedOscillator.cc \
	-o simulation

run: simulation
	./simulation

clean:
	rm -f simulation