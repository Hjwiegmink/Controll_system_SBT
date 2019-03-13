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
    
    DataStore::sensor_struct sensor_waarde;

    cout << "Called sensor::get_data(): " ;
    sensor_waarde.pitch = rand() % 100; 
    sensor_waarde.roll = rand() % 100; 
    sensor_waarde.Z_accel = (rand() % 5 + 1)/10; 
    sensor_waarde.angle_left = rand() % 100; 
    sensor_waarde.angle_right= rand() % 100; 
    m_ruwe_state_data->PutSensorData(&sensor_waarde);
    printf("%f,%f,%f,%f,%f",sensor_waarde.pitch, sensor_waarde.roll, sensor_waarde.Z_accel, sensor_waarde.angle_left, sensor_waarde.angle_right);
}

bool Sensor::data_op(){
    return data_is_op;
}