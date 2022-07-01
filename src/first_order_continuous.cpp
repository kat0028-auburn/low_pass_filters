#include "low_pass_filters/first_order_continuous.hpp"

namespace filter
{

firstOrderContinuous::firstOrderContinuous(double& freq_in)
{
    this->freq = freq_in; 

    this->output = 0.0;
    this->d_output = 0.0;

    this->time_new = std::chrono::steady_clock::now();
    this->time_old = this->time_new;
}

firstOrderContinuous::~firstOrderContinuous()
{
    // shutdown
}

void firstOrderContinuous::updateFreq(double& freq_in)
{
    this->freq = freq_in;
}

double firstOrderContinuous::runSisoFilter(double& input)
{
    if(this->time_new == this->time_old)
    {
        this->time_old = std::chrono::steady_clock::now();
        return 0.0;
    }
    else
    {
        double dt = updateTimeStep();

        runFilter(input, dt);

        return this->output;
    }
}

double firstOrderContinuous::runObsFilter(double& input)
{
    if(this->time_new == this->time_old)
    {
        this->time_old = std::chrono::steady_clock::now();
        return 0.0;
    }
    else
    {
        double dt = updateTimeStep();

        runFilter(input, dt);

        return this->d_output;
    }
}

void firstOrderContinuous::runMimoFilter(double& input, double& d_input)
{
    if(this->time_new == this->time_old)
    {
        std::cout<<"should only see this once"<<std::endl;
        this->time_old = std::chrono::steady_clock::now();
    }
    else
    {
        double dt = updateTimeStep();
        std::cout<<"computer time: "<<dt<<std::endl;
        runFilter(input, dt);

        input = this->output;
        d_input = this->d_output;
    }    
}

double firstOrderContinuous::updateTimeStep()
{
    this->time_new = std::chrono::steady_clock::now();
    double dt = std::chrono::duration<double>(this->time_new - this->time_old).count();
    this->time_old = time_new;
    this->time_new = std::chrono::steady_clock::now();
    return dt;
}

void firstOrderContinuous::runFilter(double& input, double& dt)
{
    this->d_output = this->freq * (input - this->output);
    this->output += this->d_output * dt;
}

}