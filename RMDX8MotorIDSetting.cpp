//
// Created by jaehoon on 22. 6. 2.
//
#include "CanMotorX8ProV2.h"
#include <iostream>

std::string canName_temp = "can0";
std::string bitRate = "1000000";
char *canName = "can0";
CanMotorX8ProV2 canX8pro(canName, canName_temp, bitRate);
int motor1ID = 0x141;

int main(){
    u_int8_t setMotor = 0x03;
    std::cout<<"motor ID is now setting to "<<setMotor+140<<std::endl;
    sleep(1);
    canX8pro.setMotorID(motor1ID, setMotor);
    std::cout<<"motor ID is set!"<<std::endl;
};