#include "motorcontrol.h"

int main()
{
    std::string canName_temp = "can8";
    std::string bitRate = "1000000";
    char* canName = "can8";
    
    motorcontrol mt(canName, 0x141, canName_temp, bitRate);
    if (mt.getSock() <0) {return -1;}
    mt.turnOnMotor();
    sleep(5);

    mt.setTorque(0XFF);

    std::cout<<"get encoder hex value"<<std::endl;

    for (int i =0 ; i<5 ; i++)
    {
        mt.getEncoder();
        usleep(1000);
    }
    sleep(2);
    
    
    mt.turnOffMotor();
    
    return 0;
}