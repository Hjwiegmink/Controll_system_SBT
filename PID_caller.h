/* 
 * File:   PID_caller.h
 * Author: arjan
 *
 * Created on 11 maart 2019, 12:23
 */

#ifndef PID_CALLER_H
#define	PID_CALLER_H
#include "pid.h"
#include "DataStore.h"
class PID_caller {
public:
    DataStore* m_complementary_data;
    DataStore* m_PID_data;
    PID_caller();
    PID_caller(const PID_caller& orig);
    virtual ~PID_caller();
    void PID_in();
private:

};

#endif	/* PID_CALLER_H */

