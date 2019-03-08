/* 
 * File:   ComplementaryFilter.h
 * Author: arjan
 *
 * Created on 1 maart 2019, 11:49
 */

#ifndef COMPLEMENTARYFILTER_H
#define	COMPLEMENTARYFILTER_H
class ComplementaryFilter {
public:
    ComplementaryFilter();
    ComplementaryFilter(const ComplementaryFilter& orig);
    float CalculateRealHeight(float angle_left, float angle_right, float accel_z, float Xsens_roll);
    virtual ~ComplementaryFilter();
private:

};

#endif	/* COMPLEMENTARYFILTER_H */

