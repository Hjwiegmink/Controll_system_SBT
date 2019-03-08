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
    //cout << "Called constructor RuwDataFilter()" << endl;
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
    DataStore::xsens_struct ruw = m_ruwe_state_data->GetXsensData();
    DataStore::AngleSensor raw = m_ruwe_state_data->GetAnglesensData();

    // Filter het.
    float filtered_pitch = lpFilter->process(ruw.pitch);
    float filtered_roll = lpFilter->process(ruw.roll);
    float filtered_Z_accel = lpFilter->process(ruw.Z_accel);
    float filtered_angle_left = lpFilter->process(raw.angle_left);
    float filtered_angle_right = lpFilter->process(raw.angle_right);
    printf("%f,%f,%f,%f,%f",filtered_pitch, filtered_roll, filtered_Z_accel, filtered_angle_left, filtered_angle_right);
    // En bewaar het voor de volgende ronde.
    m_filtered_data->PutXsensData(&ruw);
    m_filtered_data->PutAnglesensData(&raw);

}

