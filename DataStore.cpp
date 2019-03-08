/* 
 * File:   DataStore.cpp
 */

#include <iostream>
#include "DataStore.h"

using namespace std;

DataStore::DataStore( ) {
   // cout << "Called constructor DataStore()" << endl;
}

DataStore::~DataStore( ) {
    //cout << "Called destructor DataStore()" << endl;
}

DataStore::xsens_struct DataStore::GetXsensData( ) {
   // cout << "Called DataStore::GetXsensData()" << endl;
    // Return inhoud member variabele.
    return xsens_data;
}

void DataStore::PutXsensData(xsens_struct * data) {
   // cout << "Called DataStore::PutXsensData()" << endl;
    // De inhoud van waar de pointer naar wijst toekennen aan member
    // variabele xsens_data.
    xsens_data = *data;
}
DataStore::AngleSensor DataStore::GetAnglesensData( ) {
   // cout << "Called DataStore::GetAnglesensData()" << endl;
    // Return inhoud member variabele.
    return Anglesens_data;
}
void DataStore::PutAnglesensData(AngleSensor * data2) {
   // cout << "Called DataStore::PutXsensData()" << endl;
    // De inhoud van waar de pointer naar wijst toekennen aan member
    // variabele xsens_data.
    Anglesens_data = *data2;
}