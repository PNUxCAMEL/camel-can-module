#include "CanMotorX6_Hwayoung.h"
#include "CanMotorX8ProV2.h"
#include <chrono> //time check

int main() {
    // TODO : errors in torque control mode
    std::string canName_temp = "can8";
    std::string bitRate = "1000000";
    char *canName = "can8";
    int motor1ID = 0x141;
    int iteration = 0;
    CanMotorX6_Hwayoung canX6(canName, canName_temp, bitRate);

    canX6.turnOnMotor(motor1ID);
    int torque_int = -2000;
    canX6.setTorque(motor1ID, torque_int);
    while(true)
    {
        iteration++;
        canX6.setTorque(motor1ID, torque_int);
        usleep(1000);
        if(iteration == 5000) {break ;}
//        std::cout<<"1. Angular position[deg] : "<<canX6.getAngularPosition() * canX6.rad2deg<<std::endl;
//        canX6.readMultiturnAngularPosition(motor1ID);
//        std::cout<<"2. Angular position[deg] : "<<canX6.getAngularPosition() * canX6.rad2deg<<std::endl;
    }

    canX6.turnOffMotor(motor1ID);

}