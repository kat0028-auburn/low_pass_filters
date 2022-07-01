#ifndef FIRST_ORDER_CONTINUOUS_H
#define FIRST_ORDER_CONTINUOUS_H

#include <cmath>
#include <chrono>
#include <iostream>

namespace filter
{

class firstOrderContinuous
{
    private:
        double output;
        double d_output;

        double freq;

        std::chrono::steady_clock::time_point time_new;
        std::chrono::steady_clock::time_point time_old;

        double updateTimeStep();
        void runFilter(double& input, double& dt);

    public:
        firstOrderContinuous(double& freq_in);
        ~firstOrderContinuous();

        void updateFreq(double& freq_in);

        double runSisoFilter(double& input);
        double runObsFilter(double& input);
        void runMimoFilter(double& input, double& d_input);
        
};

}

#endif