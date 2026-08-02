#ifndef PERFORMANCEANALYSIS_H_
#define PERFORMANCEANALYSIS_H_

#include <vector>
#include <stdexcept>
#include <algorithm>

class PerformanceAnalysis {
  private:
    std::vector<double> time_values;
    std::vector<double> response_values;
    double steady_state_value;

  public:
    PerformanceAnalysis(const std::vector<double>& time_vals, const std::vector<double>& response_vals);
    double GetSteadyStateValue() const;
    double GetOvershoot() const;
    double GetPercentOvershoot() const;
    double GetDelayTime() const;
    double GetRiseTime() const;
    double GetSettlingTime(double tolerance_percent) const;
}; 

#endif