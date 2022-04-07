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

    mt.setVelocity(motor1ID, 0XFF);
    sleep(2);
    mt.stopMotor(motor1ID);
    sleep(2);
    mt.setVelocity(motor1ID, 0xFF);

    std::cout << "get encoder hex value" << std::endl;

    for (int i = 0; i < 5; i++) {
        mt.getEncoder(motor1ID);
        usleep(1000);
    }
    sleep(2);


    mt.turnOffMotor(motor1ID);

    return 0;
}