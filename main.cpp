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

using namespace std;

/*
 * main.
 */
int main(int argc, char** argv) {

    // Maak de objecten.
    DataStore * ruwe_data = new DataStore();
    DataStore * filtered = new DataStore();
    Sensor * de_sensor = new Sensor();
    RuwDataFilter * filter = new RuwDataFilter;

    // De associaties, de verbindingen tussen de objecten.
    de_sensor->m_ruwe_state_data = ruwe_data;  // (1)
    filter->m_ruwe_state_data = ruwe_data;     // (2)
    filter->m_filtered_data = filtered;        // (3)

    // Hier begint het echte werk.
    de_sensor->get_data();
    int N=0;
    while (N < 100) {
        filter->FilterIt();
        de_sensor->get_data();
         
    N=N+1;    
    }

    // Als de klus klaar is ruim de objecten op.    
    delete (ruwe_data);
    delete (filtered);
    delete (de_sensor);
    delete (filter);

    return 0;
}