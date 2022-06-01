#include "CanMotorX8ProV2.h"
#include "test_X8motor.h"
#include <chrono> //time check

std::string canName_temp = "can0";
std::string bitRate = "1000000";
char *canName = "can0";
CanMotorX8ProV2 canX8pro(canName, canName_temp, bitRate);
int motor1ID = 0x142;
double motor1AngularPosition = 0;
double motor1AngularVelocity = 0;
int torque_int = 0;
double torque = 0.0;
double torque1 = 0;
double torqueLimit = 5;

int main() {
    if (canX8pro.getSock() < 0) { return -1; }
    int iteration = 0;
    canX8pro.turnOnMotor(motor1ID);
    torque_int = 300;
    canX8pro.setTorqueCurrent(motor1ID, torque_int);
    while (true) {
        iteration++;
//        canX8pro.setTorqueCurrent(motor1ID, torque_int);
        std::cout << "Angular position 1[deg] : " << canX8pro.getAngularPosition() * canX8pro.rad2deg << std::endl;
        usleep(1000);
        if (iteration == 50000) {
            break;
        }
    }
    canX8pro.turnOffMotor(motor1ID);

//    canX8pro.turnOnMotor(motor1ID);

//    int Kp = 30;
//    int Kd = 2.5;
//    float desiredVelocity = 0.0;
//    float desiredPosition = 180.0 * deg2rad;
//    testPDcontrol(Kp, Kd, desiredPosition, desiredVelocity);

//    canX8pro.turnOffMotor(motor1ID);
//    canX8pro.stopMotor(motor1ID);

    return 0;
}

void testPDcontrol(double Kp, double Kd, float desiredPosition, float desiredVelocity) {
    float positionError = 0.0;
    float velocityError = 0.0;
    int iteration = 0;

    while (true) {
        iteration++;
        canX8pro.readMultiturnAngularPosition(motor1ID);
        motor1AngularPosition = canX8pro.getAngularPosition();
        canX8pro.readMotorStatus2(motor1ID);
        motor1AngularVelocity = canX8pro.getAngularVelocity();

        positionError = desiredPosition - motor1AngularPosition;
        velocityError = desiredVelocity - motor1AngularVelocity;

        torque = Kp * positionError + Kd * velocityError;

        if (torque > torqueLimit) {
            torque = torqueLimit;
        } else if (torque < -torqueLimit) {
            torque = -torqueLimit;
        }

        std::cout << "input torque : " << torque << std::endl;
        std::cout << "angular position : " << motor1AngularPosition * canX8pro.rad2deg << std::endl;
        if (abs(positionError) < 0.01) {
            std::cout << "success to converge!" << std::endl;
            break;
        }
        if (iteration > 1000) {
            std::cout << "failed to converge" << std::endl;
            break;
        }
        canX8pro.setTorque(motor1ID, torque);
        usleep(1000);
    }
    canX8pro.readEncoder(motor1ID);
//    int encoderValue = canX8pro.getEncoder();
//    std::cout<< "Encoder Value : " << encoderValue << std::endl;
    std::cout << "total iteration : " << iteration << std::endl;
}