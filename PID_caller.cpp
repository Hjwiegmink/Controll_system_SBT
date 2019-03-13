/* 
 * File:   PID_caller.cpp
 * Author: arjan
 * 
 * Created on 11 maart 2019, 12:23
 */

#include "PID_caller.h"

PID_caller::PID_caller():m_PID_data(NULL){
}

PID_caller::~PID_caller() {
}
void PID_caller::PID_in(){ 
    DataStore::RealData inputdata = m_complementary_data-> GetComplementaryData();
    DataStore::PIDDataTotal PIDData;
    control::PID roll = control::PID(0.1, 0.1, 0.01, 0.5);
      
              //0, val = reference, previous value
               PIDData.Force_roll  = roll.calculate(0, inputdata.Real_roll);
        
    
    control::PID pitch = control::PID(0.1, 0.6, 0.01, 0.8);   
                //0, val = reference, previous value
                PIDData.Force_pitch = pitch.calculate(0, inputdata.Real_pitch);
        
    
    control::PID height = control::PID(0.1, 0.8, 0.02, 0.2);
                //0, val = reference, previous value
                PIDData.Force_height = height.calculate(0.3, inputdata.Real_height);
    printf("%f,%f,%f",PIDData.Force_height,PIDData.Force_pitch,PIDData.Force_roll);    
    m_PID_data-> PutPIDData(&PIDData);
}
    

