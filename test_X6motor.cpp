#include "CanMotorX6_Hwayoung.h"
#include "CanMotorX8ProV2.h"
#include <chrono> //time check

int main() {
    // TODO : errors in torque control mode
    std::string canName_temp = "can0";
    std::string bitRate = "1000000";
    char *canName = "can0";
    int motor1ID = 0x141;

    double deg2rad = 3.141592 / 180.0;
    float motor1AngularPosition = 0;
    CanMotorX6_Hwayoung canX6(canName, canName_temp, bitRate);
    canX6.turnOnMotor(motor1ID);
    int torque_int = -20;
    canX6.setTorque(motor1ID, torque_int);
    int iteration = 0;
//    while(true)
//    {
//        iteration++;
//        if(iteration == 1000)
//        {break;}
//        canX6.readMultiturnAngularPosition(motor1ID);
//        std::cout<<"current posiiton : "<<canX6.getAngularPosition()<<std::endl;
//        usleep(1000);
//    }
//    sleep(10);
//    canX6.turnOffMotor(motor1ID);

//    int Kp = 50.0;
//    float desiredPosition = 0.0;
//    float currentPosition = 0;
//    int torque = Kp * (desiredPosition - currentPosition);
//    int torqueLimit = 25;

//    if (canX6.getSock() < 0) { return -1; }
//    canX6.turnOnMotor(motor1ID);
//    sleep(5);
//    std::cout << "motor is turned on" << std::endl;
//
//    std::cout << "P control in single motor." << std::endl;
//    while(true)
//    {
//        motor1AngularPosition = canX6.getMultiturnAngularPosition(motor1ID);
//        currentPosition = motor1AngularPosition;
//        torque = Kp * (desiredPosition - currentPosition);
//        std::cout << "angular position : "<<motor1AngularPosition << std::endl;
//
//        if(torque > torqueLimit)
//            {
//                torque = torqueLimit;
//            }
//        else if(torque < -torqueLimit)
//            {
//                torque = -torqueLimit;
//            }
//
//        std::cout << "input torque : " << torque <<std::endl;
//
//        if (abs(desiredPosition - currentPosition) < 0.01) {break ;}
//        canX6.setTorque(motor1ID, torque);
//        usleep(1000);
//    }

//    for (int i =0 ; i< 10000 ; i++){
//        // system time
//        auto begin = std::chrono::high_resolution_clock::now();
//        motor1AngularPosition = canX6.getMultiturnAngularPosition(motor1ID);
//        // system time
//        auto end = std::chrono::high_resolution_clock::now();
//        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//        std::cout << i << "angular position : "<<motor1AngularPosition << " Time measured: "<< elapsed.count() * 1e-9 <<"seconds" <<std::endl;
//
//
//        motor1AngularPosition = canX6.getMultiturnAngularPosition(motor1ID);
//        std::cout << "angular position : "<<motor1AngularPosition << std::endl;
//        inputTorque = Kp * (desiredPosition - motor1AngularPosition);
//        if(inputTorque > 20)
//        {
//            inputTorque = 20;
//        }
//        else if(inputTorque < -20)
//        {
//            inputTorque = -20;
//        }
//        canX6.setTorque(motor1ID, inputTorque);
//        usleep(1000);
//    }
//    sleep(20);
//    canX6.getEncoder(motor1ID);
//    motor1AngularPosition = canX6.getMultiturnAngularPosition(motor1ID);
//    std::cout << "angular position : "<<motor1AngularPosition << std::endl;
//    canX6.turnOffMotor(motor1ID);
    canX6.stopMotor(motor1ID);

}