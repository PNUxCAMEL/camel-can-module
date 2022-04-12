#include "CanMotorX8Pro.h"
#include <chrono> //time check

int main() {
    // TODO : errors in torque control mode
    std::string canName_temp = "can8";
    std::string bitRate = "1000000";
    char *canName = "can8";
    int motor1ID = 0x141;
    float motor1AngularPosition = 0;
    float motor1AngularPosition_2 = 0;
    float motor1AngularVelocity = 0;
    int motor1Encoder = 0;
    CanMotorX8Pro canX8pro(canName, canName_temp, bitRate);
    if (canX8pro.getSock() < 0) { return -1; }
    canX8pro.turnOnMotor(motor1ID);
    sleep(5);
    std::cout << "motor is turned on" << std::endl;


    double deg2rad = 3.141592 / 180.0;
    double rad2deg = 180.0 / 3.141592;

//    float desiredPosition = 0.0 * deg2rad;
//    double desiredPosition = 180.0 * deg2rad;
//    canX8pro.setPosition1(motor1ID, desiredPosition);
//    auto begin = std::chrono::high_resolution_clock::now();
//    float cumulatedPosition = 0.0;
//    for (int i = 0; i < 5000; i++) {
//
//        canX8pro.readMultiturnAngularPosition(motor1ID);
//        motor1AngularPosition = canX8pro.getAngularPosition();
//
//        canX8pro.readMotorStatus2(motor1ID);
//        motor1AngularPosition_2 = canX8pro.getAngularPosition();
//        motor1AngularVelocity = canX8pro.getAngularVelocity();
////        cumulatedPosition += motor1AngularVelocity * 0.001;
//        std::cout << "angular position from read multiturn : " << motor1AngularPosition << std::endl;
//        std::cout << "angular position from read motor status : " << motor1AngularPosition_2 << std::endl;
//        std::cout << "angular velocity from read motor status : " << motor1AngularVelocity << std::endl;
//        usleep(1000);
//    }
//    auto end = std::chrono::high_resolution_clock::now();
//    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//    std::cout << " Time measured: "<< elapsed.count() * 1e-9 <<"seconds" <<std::endl;
//    std::cout << "cumulated position from angular velocity : " << cumulatedPosition * rad2deg << std::endl;

    int torque = 0;
    int torqueLimit = 40; //integer value
    int Kp = 30;
    int Kd = 2.5;
    float desiredVelocity = 0.0;
    float desiredPosition = 0 * deg2rad;
    float positionError = 0.0;
    float velocityError = 0.0;
    int iteration = 0;

    while(true)
    {
        iteration++;
        canX8pro.readMultiturnAngularPosition(motor1ID);
        motor1AngularPosition = canX8pro.getAngularPosition();
        canX8pro.readMotorStatus2(motor1ID);
        motor1AngularVelocity = canX8pro.getAngularVelocity();

        positionError = desiredPosition - motor1AngularPosition;
        velocityError = desiredVelocity - motor1AngularVelocity;

        torque = Kp * positionError + Kd * velocityError;

        if(torque > torqueLimit)
        {
            torque = torqueLimit;
        }
        else if(torque < -torqueLimit)
        {
            torque = -torqueLimit;
        }

        std::cout << "input torque : " << torque <<std::endl;
        std::cout << "angular position : " << motor1AngularPosition * rad2deg << std::endl;
        if (abs(positionError) < 0.01) {
            std::cout << "success to converge!" <<std::endl;
            break ;}
        if(iteration > 1000) {
            std::cout << "failed to converge" <<std::endl;
            break;
        }
        canX8pro.setTorque(motor1ID, torque);
        usleep(1000);
    }

    std::cout << "total iteration : " << iteration <<std::endl;

    canX8pro.turnOffMotor(motor1ID);
//    canX8pro.stopMotor(motor1ID);

    return 0;
}