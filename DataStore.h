/* 
 * File:   DataStore.h
 */

#ifndef _DATASTORE_H_
#define _DATASTORE_H_

#include <string>

class DataStore
{
    public:
        struct xsens_struct
        {
            float pitch;
            float roll;
            float Z_accel;

        };
        struct AngleSensor
        {
            float angle_left;
            float angle_right;
        };
        
        DataStore();
        virtual ~DataStore();
        void PutXsensData(xsens_struct * data);
        void PutAnglesensData(AngleSensor * data2);
        xsens_struct GetXsensData();
        AngleSensor GetAnglesensData();

    private:
        xsens_struct xsens_data;
        AngleSensor Anglesens_data;
};

#endif

