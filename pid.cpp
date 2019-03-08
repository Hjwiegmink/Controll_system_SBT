/* 
 * File:   pid.cpp
 * Author: User
 * 
 * Created on 27 februari 2019, 10:28
 */
#include <iostream>
#include <cmath>
#include "pid.h"

using namespace std;

control::PID::PID( double dt, double Kp, double Kd, double Ki )
{
    pimpl = new PIDImpl(dt,Kp,Kd,Ki);
}
double control::PID::calculate( double reference, double pv )
{
    return pimpl->calculate(reference,pv);
}
control::PID::~PID() 
{
    delete pimpl;
}

/**
 * Implementation
 */
control::PIDImpl::PIDImpl( double dt, double Kp, double Kd, double Ki ) :
    _dt(dt),
    _Kp(Kp),
    _Kd(Kd),
    _Ki(Ki),
    _pre_error(0),
    _integral(0)
{
}
/*The input for the calculate function will be the reference and the 'previous 
 * value (pv)' that comes in reality from the sensors. This data is stored in 
 * DataStore so we should add these values. This is different for all the PID 
 * controllers   
*/
double control::PIDImpl::calculate( double reference, double pv )
{
    
    // Calculate error
    double error = reference - pv;

    // Proportional term
    double Pout = _Kp * error;

    // Integral term
    _integral += error * _dt;
    double Iout = _Ki * _integral;

    // Derivative term
    double derivative = (error - _pre_error) / _dt;
    double Dout = _Kd * derivative;

    // Calculate total output
    double output = Pout + Iout + Dout;

    // Save error to previous error
    _pre_error = error;

    return output;
}

control::PIDImpl::~PIDImpl()
{
}
