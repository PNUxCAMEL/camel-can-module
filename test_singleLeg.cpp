#include "SingleLegCAN.h"

std::string canName_temp = "can0";
std::string bitRate = "1000000";
char *canName = "can0";
SingleLegCAN can(canName, canName_temp, bitRate);
int motor1ID = 0x141;
int motor2ID = 0x142;
double motor1AngularPosition = 0;
double motor1AngularVelocity = 0;
double motor2AngularPosition = 0;
double motor2AngularVelocity = 0;
double torque = 0;
double torque1 = 0;
double torque2 = 0;
double torqueLimit = 5;

int main() {
    if (can.getSock() < 0) { return -1; }
    int iteration = 0;
    can.turnOnMotor(motor1ID);
    can.turnOnMotor(motor2ID);


    while (true) {
        iteration++;
        can.setTorque(motor1ID, 0.0);
        can.setTorque(motor2ID, 0.0);
        std::cout << "Angular position [rad] : " << can.getAngularPosition1() <<"  "<< can.getAngularPosition2()<< std::endl;
//        std::cout << "Angular position [deg] : " << can.getAngularPosition1() * can.rad2deg <<"  "<< can.getAngularPosition2() * can.rad2deg<< std::endl;
        usleep(1000);
        if (iteration == 5000) {
            break;
        }
    }
    can.turnOffMotor(motor1ID);
    can.turnOffMotor(motor2ID);

    return 0;
}