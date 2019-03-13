/* 
 * File:   DataStore.h
 */

#ifndef _DATASTORE_H_
#define _DATASTORE_H_

#include <string>

class DataStore
{
    public:
        struct sensor_struct
        {
            float pitch;
            float roll;
            float Z_accel;
            float angle_left;
            float angle_right;

        };
        struct FilteredData
        {
          float filtered_pitch;
          float filtered_roll ;
          float filtered_Z_accel ;
          float filtered_angle_left ;
          float filtered_angle_right ;
        };
        struct RealData
        {
          float Real_height;
          float Real_roll;
          float Real_pitch;
        };
        
        struct PIDDataTotal
        {
          float Force_height;
          float Force_roll;
          float Force_pitch;
        };
        struct AngleWings
        {
            float Wing_left;
            float Wing_right;
            float Wing_back;
        };
        
        DataStore();
        
        virtual ~DataStore();
        
        void PutSensorData(sensor_struct * data);
        void PutFilteredData(FilteredData * data3);
        void PutComplementaryData(RealData * data4);
        void PutPIDData(PIDDataTotal * data5);
        void PutWingData(AngleWings * data6);
        sensor_struct GetSensorData();
        FilteredData GetFilteredData();
        RealData GetComplementaryData();
        PIDDataTotal GetPIDData();
        AngleWings GetWingData();
        

    private:
        sensor_struct sensor_data;
        FilteredData Filtered_data;
        RealData Complementary_data;
        PIDDataTotal PID_data;
        AngleWings Wing_data;
};

#endif

