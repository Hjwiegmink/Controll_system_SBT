/* 
 * File:   Force_to_wing_angle.cpp
 * Author: User
 * 
 * Created on 28 februari 2019, 10:05
 */

#include "Force_to_wing_angle.h"
#include "DataStore.h"
#include <iostream>
#include <cmath>

control::ForceToWingAngle::ForceToWingAngle(){
}

control::ForceToWingAngle::ForceToWingAngle(const ForceToWingAngle& orig) {
}

control::ForceToWingAngle::~ForceToWingAngle() {
}

void control::ForceToWingAngle::MMA() {
    /* First we will start with the MMA. This is the motor mixing algorithm that 
     * divides the incoming forces from the 3 PID controllers in 3 different 
     * forces that the wings should deliver. The MMA consists of a matrix, that 
     * has to be inversed to calculate the right forces per wing. 
    */
   DataStore::PIDDataTotal input =m_PID_data-> GetPIDData();
   DataStore::RealData input2 =m_complementary_data-> GetComplementaryData();
   DataStore::AngleWings output;
   
   float velocity = 5;
    int i, j;
    float matrix_MMA[3][3] = {
        {1, 1, 1},
        {1.54, 1.54, -2.83},
        {-0.37, 0.37, 0},
    }; 
    
    float inverse_matrix_MMA[3][3];
    float determinant = 0;
 
    // finding determinant:
	for(i = 0; i < 3; i++)
		determinant = determinant + (matrix_MMA[0][i] * (matrix_MMA[1][(i+1)%3] * matrix_MMA[2][(i+2)%3] - matrix_MMA[1][(i+2)%3] * matrix_MMA[2][(i+1)%3]));
	
     std::cout<<"\n\nInverse of matrix is: \n";
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++)
			std::cout<<((matrix_MMA[(j+1)%3][(i+1)%3] * matrix_MMA[(j+2)%3][(i+2)%3]) - (matrix_MMA[(j+1)%3][(i+2)%3] * matrix_MMA[(j+2)%3][(i+1)%3]))/ determinant<<"\t";
		std::cout<<"\n";
	}
     //calculate inverse matrix and save values []][] = [row][colomn]
     inverse_matrix_MMA[0][0] = ((matrix_MMA[(0+1)%3][(0+1)%3] * matrix_MMA[(0+2)%3][(0+2)%3]) - (matrix_MMA[(0+1)%3][(0+2)%3] * matrix_MMA[(0+2)%3][(0+1)%3]))/ determinant;
        //std::cout << (inverse_matrix_MMA[0][0]) << "\t";
     inverse_matrix_MMA[0][1] = ((matrix_MMA[(1+1)%3][(0+1)%3] * matrix_MMA[(1+2)%3][(0+2)%3]) - (matrix_MMA[(1+1)%3][(0+2)%3] * matrix_MMA[(1+2)%3][(0+1)%3]))/ determinant;
     inverse_matrix_MMA[0][2] = ((matrix_MMA[(2+1)%3][(0+1)%3] * matrix_MMA[(2+2)%3][(0+2)%3]) - (matrix_MMA[(2+1)%3][(0+2)%3] * matrix_MMA[(2+2)%3][(0+1)%3]))/ determinant;   
     inverse_matrix_MMA[1][0] = ((matrix_MMA[(0+1)%3][(1+1)%3] * matrix_MMA[(0+2)%3][(1+2)%3]) - (matrix_MMA[(0+1)%3][(1+2)%3] * matrix_MMA[(0+2)%3][(1+1)%3]))/ determinant;
     inverse_matrix_MMA[1][1] = ((matrix_MMA[(1+1)%3][(1+1)%3] * matrix_MMA[(1+2)%3][(1+2)%3]) - (matrix_MMA[(1+1)%3][(1+2)%3] * matrix_MMA[(1+2)%3][(1+1)%3]))/ determinant;
     inverse_matrix_MMA[1][2] = ((matrix_MMA[(2+1)%3][(1+1)%3] * matrix_MMA[(2+2)%3][(1+2)%3]) - (matrix_MMA[(2+1)%3][(1+2)%3] * matrix_MMA[(2+2)%3][(1+1)%3]))/ determinant;
     inverse_matrix_MMA[2][0] = ((matrix_MMA[(0+1)%3][(2+1)%3] * matrix_MMA[(0+2)%3][(2+2)%3]) - (matrix_MMA[(0+1)%3][(2+2)%3] * matrix_MMA[(0+2)%3][(2+1)%3]))/ determinant;
     inverse_matrix_MMA[2][1] = ((matrix_MMA[(1+1)%3][(2+1)%3] * matrix_MMA[(1+2)%3][(2+2)%3]) - (matrix_MMA[(1+1)%3][(2+2)%3] * matrix_MMA[(1+2)%3][(2+1)%3]))/ determinant;
     inverse_matrix_MMA[2][2] = ((matrix_MMA[(2+1)%3][(2+1)%3] * matrix_MMA[(2+2)%3][(2+2)%3]) - (matrix_MMA[(2+1)%3][(2+2)%3] * matrix_MMA[(2+2)%3][(2+1)%3]))/ determinant;
        //std::cout << (inverse_matrix_MMA[1][1]) << "\t";
     
     
     float left_force = inverse_matrix_MMA[0][0] * input.Force_height + inverse_matrix_MMA[0][1] * input.Force_pitch + inverse_matrix_MMA[0][2] * input.Force_roll;
     float right_force = inverse_matrix_MMA[1][0] * input.Force_height + inverse_matrix_MMA[1][1] * input.Force_pitch + inverse_matrix_MMA[1][2] * input.Force_roll;
     float back_force = inverse_matrix_MMA[2][0] * input.Force_height + inverse_matrix_MMA[2][1] * input.Force_pitch + inverse_matrix_MMA[2][2] * input.Force_roll;
     
     /* Now we know the forces that each wing should generate to fly, we should 
      * also calculate the angle that the wings should have to generate this 
      * force. This is done with the equation for lift: L=0.5*rho*v^2*Cl;  
      */
     const float kLeftSurface = 0.5*(35832.62+9379.39+15937.11+43774.74) * pow (10 , -6);   //m2
     const float kRightSurface = 0.5*(35832.62+9379.39+15937.11+43774.74) * pow (10, -6);       
     const float kBackSurface = 0.5*(37297+37930+10794+10794) * pow (10, -6);
     const float kDensity = 1025; //kg/m3 density salt water
     const int kLiftSlope = 5;
     const float kZeroLiftAngle = -0.05236;      //radians
     
     //test to check the surface std::cout << (kLeftSurface) << '\t';
     
    
     //devide the force by (0.5*density*surface*velocity) to get the lift coefficient 
     float left_lift_coefficient = left_force / (0.5 * kDensity * kLeftSurface * velocity) ; 
     float right_lift_coefficient = right_force / (0.5 * kDensity * kRightSurface  * velocity) ;
     float back_lift_coefficient = back_force / (0.5 * kDensity * kBackSurface * velocity) ;
    
     float left_angle_total = left_lift_coefficient / kLiftSlope;
     float right_angle_total = right_lift_coefficient / kLiftSlope;
     float back_angle_total = back_lift_coefficient / kLiftSlope;
      
     //calculate the final wing angles
     output.Wing_left = left_angle_total - input2.Real_pitch + kZeroLiftAngle;
     output.Wing_right = right_angle_total - input2.Real_pitch + kZeroLiftAngle;
     output.Wing_back  = back_angle_total - input2.Real_pitch + kZeroLiftAngle;
     
     printf("%f,%f,%f",output.Wing_left, output.Wing_right,output.Wing_back); 
     
     m_FtoW_data->PutWingData(&output);
     return ;
     /*Now we can calculate the angle that the maxon motor should make in such 
      * a way that the wing is making the right angle.   
      */
       
     
}

