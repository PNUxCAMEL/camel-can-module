#include "motorcontrol.h"

int main() {
    std::string canName_temp = "can8";
    std::string bitRate = "1000000";
    char *canName = "can8";
    int motor1ID = 0x141;

    motorcontrol mt(canName, canName_temp, bitRate);
    if (mt.getSock() < 0) { return -1; }
    mt.turnOnMotor(motor1ID);
    sleep(5);
    std::cout << "motor is turned on" << std::endl;
    std::cout << "current position : " << std::endl;
//    mt.getEncoder(motor1ID);
    mt.getMultiturnAngle(motor1ID);
    //    mt.setTorque(motor1ID, 0xFF);
//    mt.setVelocity(motor1ID, 0XFF);

    double deg2rad = 3.141592 / 180.0;
    double desiredPosition = 0.0 * deg2rad;
//    double desiredPosition = 540.0 * deg2rad;

    mt.setPosition1(motor1ID, desiredPosition);
    sleep(3);
    std::cout << "final position : " << std::endl;
//    mt.getEncoder(motor1ID);
    mt.getMultiturnAngle(motor1ID);

    mt.turnOffMotor(motor1ID);

    return 0;
}