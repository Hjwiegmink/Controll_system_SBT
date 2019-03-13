/* 
 * File:   RuwDataFilter.cpp
 */
#include <stdio.h>
#include <string>
#include <iostream>
#include "Filtered_data.h"

using namespace std;

// Constructor die geen file opent.
RuwDataFilter::RuwDataFilter( ) {
    cout << "Called constructor RuwDataFilter()" << endl;
    double Fc=10;
    double sampleRate=100;
    // Create a Biquad, lpFilter.
    lpFilter = new Biquad(bq_type_lowpass, Fc / sampleRate, 0.707, 0);  
    lpFilter->setBiquad(bq_type_lowpass, Fc / sampleRate, 0.707, 0);
}

RuwDataFilter::~RuwDataFilter( ) {
   // cout << "Called destructor RuwDataFilter()" << endl;
}

void RuwDataFilter::FilterIt( ) {
    // Haal de data op.
    DataStore::sensor_struct ruw = m_ruwe_state_data->GetSensorData();
    DataStore::FilteredData filtereddata;
    // Filter het.
    filtereddata.filtered_pitch = lpFilter->process(ruw.pitch);
    filtereddata.filtered_roll = lpFilter->process(ruw.roll);
    filtereddata.filtered_Z_accel = lpFilter->process(ruw.Z_accel);
    filtereddata.filtered_angle_left = lpFilter->process(ruw.angle_left);
    filtereddata.filtered_angle_right = lpFilter->process(ruw.angle_right);
    printf("%f,%f,%f,%f,%f",filtereddata.filtered_pitch,filtereddata.filtered_roll,filtereddata.filtered_Z_accel, filtereddata.filtered_angle_left, filtereddata.filtered_angle_right);
    // En bewaar het voor de volgende ronde.
    m_filtered_data->PutSensorData(&ruw);
    m_filtered_data->PutFilteredData(&filtereddata);

}

