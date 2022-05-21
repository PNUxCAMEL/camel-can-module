//
// Created by jaehoon on 22. 5. 21.
//
#include "CanMotorX8ProV2.h"

std::string canName_temp = "can0";
std::string bitRate = "1000000";
char *canName = "can0";
CanMotorX8ProV2 canX8pro(canName, canName_temp, bitRate);
int motor1ID = 0x141;

/**
 * Before you use this code, You have to set your RMD X8-pro motor in offset position.
 * After use this code, you have to reboot the motor.
 * Also, frequent use of this code makes your chip's lifespan shorter than before.
 */

int main()
{
    canX8pro.readEncoder(motor1ID);
    std::cout<<"current encoder value : "<<canX8pro.getEncoder()<<std::endl;
    sleep(1);
    canX8pro.optionSetMotorOffsetToCurrentPosition(motor1ID);
    std::cout<<"Now, the motor offset is being set to the current position."<<std::endl;
    sleep(3);
    std::cout<<"It's done!"<<std::endl;
    sleep(1);
    canX8pro.readEncoder(motor1ID);
    std::cout<<"current encoder value : "<<canX8pro.getEncoder()<<std::endl;
}