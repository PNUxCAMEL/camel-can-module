#include "CanMotorX8Pro.h"
#include <chrono> //time check

int main() {
    // TODO : errors in torque control mode
    std::string canName_temp = "can8";
    std::string bitRate = "1000000";
    char *canName = "can8";
    int motor1ID = 0x141;
    float motor1AngularPosition = 0;
    CanMotorX8Pro canX8pro(canName, canName_temp, bitRate);
    if (canX8pro.getSock() < 0) { return -1; }
    canX8pro.turnOnMotor(motor1ID);
    sleep(5);
    std::cout << "motor is turned on" << std::endl;
//    canX8pro.getEncoder(motor1ID);


    double deg2rad = 3.141592 / 180.0;
    double desiredPosition = 360.0 * deg2rad;
//    double desiredPosition = 360.0 * deg2rad;


    motor1AngularPosition = canX8pro.getMultiturnAnglularPosition(motor1ID);
    std::cout << "angular position : "<<motor1AngularPosition << std::endl;
    canX8pro.setTorque(motor1ID, -150);
//    canX8pro.setPosition1(motor1ID, desiredPosition);
//    canX8pro.setVelocity(motor1ID, 0XFF);
//    sleep(1);

    for (int i =0 ; i< 5000 ; i++){
//        // system time
//        auto begin = std::chrono::high_resolution_clock::now();
//        motor1AngularPosition = canX8pro.getMultiturnAnglularPosition(motor1ID);
//        // system time
//        auto end = std::chrono::high_resolution_clock::now();
//        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//        std::cout << i << "angular position : "<<motor1AngularPosition << " Time measured: "<< elapsed.count() * 1e-9 <<"seconds" <<std::endl;
//        motor1AngularPosition = canX8pro.getMultiturnAnglularPosition(motor1ID);
//        std::cout << "angular position : "<<motor1AngularPosition << std::endl;
        usleep(1000);
    }
//    sleep(20);
//    canX8pro.getEncoder(motor1ID);
    motor1AngularPosition = canX8pro.getMultiturnAngularPosition(motor1ID);
    std::cout << "angular position : "<<motor1AngularPosition << std::endl;

//    canX8pro.turnOffMotor(motor1ID);
    canX8pro.stopMotor(motor1ID);

    return 0;
}