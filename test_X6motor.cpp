#include "CanMotorX6.h"
#include <chrono> //time check

int main() {
    // TODO : errors in torque control mode
    std::string canName_temp = "can8";
    std::string bitRate = "1000000";
    char *canName = "can8";
    int motor1ID = 0x141;

    double deg2rad = 3.141592 / 180.0;
    float motor1AngularPosition = 0;

    int Kp = 1.0;
    float desiredPosition = 90.0;
    float currentPosition = 0;
    int torque = Kp * (desiredPosition - currentPosition);

    CanMotorX6 canX6(canName, canName_temp, bitRate);
    if (canX6.getSock() < 0) { return -1; }
    canX6.turnOnMotor(motor1ID);
    sleep(5);
    std::cout << "motor is turned on" << std::endl;

    std::cout << "P control in single motor." << std::endl;
    while(true)
    {
        motor1AngularPosition = canX6.getMultiturnAngularPosition(motor1ID);
        currentPosition = motor1AngularPosition;
        torque = Kp * (desiredPosition - currentPosition);
        std::cout << "angular position : "<<motor1AngularPosition << std::endl;

        if(torque > 18)
            {
                torque = 18;
            }
        else if(torque < -18)
            {
                torque = -18;
            }

        std::cout << "input torque : " << torque <<std::endl;
        canX6.setTorque(motor1ID, torque);
        usleep(1000);
        if (abs(desiredPosition - currentPosition) < 1.0) {break ;}
    }

//    for (int i =0 ; i< 10000 ; i++){
//        // system time
//        auto begin = std::chrono::high_resolution_clock::now();
//        motor1AngularPosition = canX6.getMultiturnAngularPosition(motor1ID);
//        // system time
//        auto end = std::chrono::high_resolution_clock::now();
//        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//        std::cout << i << "angular position : "<<motor1AngularPosition << " Time measured: "<< elapsed.count() * 1e-9 <<"seconds" <<std::endl;


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

    motor1AngularPosition = canX6.getMultiturnAngularPosition(motor1ID);
    std::cout << "angular position : "<<motor1AngularPosition << std::endl;

//    canX6.turnOffMotor(motor1ID);
    canX6.stopMotor(motor1ID);

    return 0;
}