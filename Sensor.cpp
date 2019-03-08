///////////////////////////////////////////////////////////
//  sensor.cpp
//  Implementation of the Class sensor
//  Created on:      20-Feb-2019 11:56:45
//  Original author: wiegmink
///////////////////////////////////////////////////////////
#include <cstdlib>
#include <string>
#include <stdio.h>
#include "Sensor.h"



Sensor::Sensor():m_ruwe_state_data(NULL), data_is_op(false) {

  //  cout << "Called constructor sensor() for test from input file" << endl;
}

Sensor::~Sensor(){

   // cout << "Called destructor sensor()" << endl;
}


void Sensor::get_data(){

    // Produceer random test date
    
    DataStore::xsens_struct Xsensor_waarde;
    DataStore::AngleSensor Anglesensor_waarde;

    cout << "Called sensor::get_data(): " ;
    Xsensor_waarde.pitch = rand() % 100; 
    Xsensor_waarde.roll = rand() % 100; 
    Xsensor_waarde.Z_accel = (rand() % 5 + 1)/10; 
    Anglesensor_waarde.angle_left = rand() % 100; 
    Anglesensor_waarde.angle_right= rand() % 100; 
    m_ruwe_state_data->PutXsensData(&Xsensor_waarde);
    m_ruwe_state_data->PutAnglesensData(&Anglesensor_waarde);
    printf("%f,%f,%f,%f,%f",Xsensor_waarde.pitch, Xsensor_waarde.roll, Xsensor_waarde.Z_accel, Anglesensor_waarde.angle_left, Anglesensor_waarde.angle_right);
}

bool Sensor::data_op(){
    return data_is_op;
}