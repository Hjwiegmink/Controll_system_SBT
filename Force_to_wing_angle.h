/* 
 * File:   Force_to_wing_angle.h
 * Author: User
 *
 * Created on 28 februari 2019, 10:05
 */

#ifndef FORCE_TO_WING_ANGLE_H
#define	FORCE_TO_WING_ANGLE_H

namespace control{

class ForceToWingAngle {
public:
    ForceToWingAngle();
    ForceToWingAngle(const ForceToWingAngle& orig);
    virtual ~ForceToWingAngle();
    
    float MMA(float roll_force, float pitch_force, float height_force, float velocity, float pitch_angle);    
private:

};   
}

#endif	/* FORCE_TO_WING_ANGLE_H */

