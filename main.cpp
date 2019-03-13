/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kwieg
 *
 * Created on February 28, 2019, 7:54 PM
 */

#include <cstdlib>
#include "Sensor.h"
#include "Filtered_data.h"
#include "DataStore.h"
#include "ComplementaryFilter.h"
#include "PID_caller.h"
#include "Force_to_wing_angle.h"

using namespace std;

/*
 * main.
 */
int main(int argc, char** argv) {

    // Maak de objecten.
    DataStore * ruwe_data = new DataStore();
    DataStore * filtered_data = new DataStore();
    DataStore * complementary_data= new DataStore();
    DataStore * pid_data = new DataStore();
    DataStore * FtoW_data = new DataStore();
    Sensor * de_sensor = new Sensor();
    RuwDataFilter * filter = new RuwDataFilter();
    ComplementaryFilter * com_filter = new ComplementaryFilter();
    PID_caller * PID =new PID_caller();
    control::ForceToWingAngle * FtoW = new control::ForceToWingAngle();
    

    // De associaties, de verbindingen tussen de objecten.
    de_sensor->m_ruwe_state_data = ruwe_data;  // (1)
    filter->m_ruwe_state_data = ruwe_data;     // (2)
    filter->m_filtered_data = filtered_data;        // (3)
    com_filter->m_filtered_data = filtered_data; //(4)
    com_filter->m_complementary_data = complementary_data; //(5)
    PID->m_complementary_data=complementary_data;  //(6)
    PID->m_PID_data=pid_data; //(7)
    FtoW->m_complementary_data=complementary_data; //(8)
    FtoW->m_PID_data=pid_data; //(9)
    FtoW->m_FtoW_data=FtoW_data; //(10)
    
    // Hier begint het echte werk.
    de_sensor->get_data();
    int N=0;
    while (N < 100) {
        filter->FilterIt();
        com_filter->CalculateRealHeight();
        PID->PID_in();
        FtoW->MMA();
        de_sensor->get_data();
    N=N+1;    
    }

    // Als de klus klaar is ruim de objecten op.    
    delete (ruwe_data);
    delete (filtered_data);
    delete (pid_data);
    delete (de_sensor);
    delete (filter);
    delete (complementary_data);
    delete (PID);
    delete (com_filter);
    delete (FtoW);

    return 0;
}