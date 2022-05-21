//
// Created by jaehoon on 22. 4. 8..
//

#ifndef CAMEL_CAN_MODULE_CANMOTORX6_HWAYOUNG_H
#define CAMEL_CAN_MODULE_CANMOTORX6_HWAYOUNG_H

#include <iostream>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sstream>
#include <cmath>

// author@ Jaehyeong Park & Jaehoon An
/*
    TODO: 1. hex2rad, hex2rad/sec
          2. position limit
          3. pd control loop
          4. command class
          5. EMC switch
          6. multiple motorId is needed
          7. RMD X6 protocol check is needed. (V1? or V2?)
          8. output of the getAngle method should be changed to [rad] scale.
*/

class CanMotorX6_Hwayoung {
public:
    CanMotorX6_Hwayoung(char *canName, std::string canName_temp, std::string bitRate) {
        std::string command3 =
                "sudo ip link set " + canName_temp + " up type can bitrate " + bitRate; // TODO: should be modified.
        const char *c3 = command3.c_str();
        system(c3);
        initCanInterface(canName);
    }

    double rad2deg = 180.0 / 3.141592;
    double deg2rad = 3.141592 / 180.0;
    double enc2rad = 2 * 3.141592 / 65535;

    void initCanInterface(const char *CanName);

    void stopMotor(int motorID);

    void turnOnMotor(int motorID);

    void turnOffMotor(int motorID);

    void canSend(const u_int8_t *data, int motorID);

    void canRead();

    void readMultiturnAngularPosition(int motorID);

    void setTorque(int Torque, int motorID);

    int getEncoder() {return mEncoder;}

    double getAngularPosition() {return mAngularPosition_rad;}

    double getAngularVelocity() {return mAngularVelocity_rad;}

    int getSock() { return mSock; }

    can_frame getFrame() { return mFrame; }

private:
    struct can_frame mFrame;
    const char *mCanName;
    double mAngularPosition_rad;
    double mAngularVelocity_rad;
    int mSock;
    int mSendedCommand;
    int mGearRatio = 6;
    u_int32_t mCanID;
    int mEncoder = 0;
    int mEncoderMultiturnNum = 0;
    int mEncoder_temp = 0;
    int mEncoderPast = 0;
};

//socket 생성
void CanMotorX6_Hwayoung::initCanInterface(const char *ifname) {
    //CAN socket 생성
    mCanName = ifname;
    mSock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    std::cout << mSock << std::endl;
    if (mSock == -1) {
        printf("Fail to create can socket for %s - %m \n", mCanName);
        return;
    }
    printf("Success to create can socket for %s\n", mCanName);

    //CAN 식별번호 획득
    struct ifreq ifr;
    strcpy(ifr.ifr_name, mCanName);
    int ret = ioctl(mSock, SIOCGIFINDEX, &ifr);
    if (ret == -1) {
        perror("Fail to get can interface index -");
        return;
    }
    printf("Success to get can interface index: %d\n", ifr.ifr_ifindex);

    //CAN socket 바인딩
    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    ret = bind(mSock, (struct sockaddr *) &addr, sizeof(addr));
    if (ret == -1) {
        perror("Fail to bind can socket -");
        return;
    }
    printf("Success to bind can socket\n");
}

// Data 보내기
void CanMotorX6_Hwayoung::canSend(const u_int8_t *data, int motorID)
{
    u_int32_t tempid = motorID & 0x1fffffff;
    mFrame.can_id = tempid;
    memcpy(mFrame.data, data, sizeof(data));
    mFrame.can_dlc = sizeof(data);


    //전송
    int tx_bytes = write(mSock, &mFrame, sizeof(mFrame));
    if (tx_bytes == -1) {
        perror("Fail to transmit can frame -");
        return;
    }
    // std::cout << "success to transmit can frame " << tx_bytes << "is transmited" << std::endl;

    mSendedCommand = mFrame.data[0];
}

// Data 읽기
void CanMotorX6_Hwayoung::canRead() {
    int rx_bytes = read(mSock, &mFrame, sizeof(mFrame));
    //feedback msg
    // TODO : Should be changed to better method.
//    int iteration = 0;
//    while (mFrame.data[0] != mSendedCommand) {
//        iteration ++;
//        rx_bytes = read(mSock, &mFrame, sizeof(mFrame));
//        if(iteration > 100)
//        {
//            std::cout<<"failed to read data in while loop"<<std::endl;
//            break;
//        }
//    }
}



// 29. Read multiturn turns angle command (0x92)
//TODO : 0x92 Multiturn anglular position (closed)
void CanMotorX6_Hwayoung::readMultiturnAngularPosition(int motorID) {
    u_int8_t requestEncoder[8] = {0X92, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00};
    canSend(requestEncoder, motorID);
    canRead();
    mAngularPosition_rad = (
                                   mFrame.data[4] +
                                   mFrame.data[5] * 256.0 +
                                   mFrame.data[6] * 256.0 * 256.0 +
                                   mFrame.data[7] * 256.0 * 256.0 * 256.0) * 0.01 / mGearRatio * deg2rad;
    if (mFrame.data[7] > 127) {
        mAngularPosition_rad += - 256.0 * 256.0 * 256.0 * 256.0 * 0.01 / mGearRatio * deg2rad;
    }
}

// 34. Motor off command (0x80)
void CanMotorX6_Hwayoung::turnOffMotor(int motorID) {
    u_int8_t motorON_data[8] = {0x80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00};
    canSend(motorON_data, motorID);
    canRead();
}

// 35. Motor stop command (0x81)
void CanMotorX6_Hwayoung::stopMotor(int motorID) {
    u_int8_t motorStop_data[8] = {0x81, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00};
    canSend(motorStop_data, motorID);
    canRead();
}

// 36. Motor running command (0x88)
void CanMotorX6_Hwayoung::turnOnMotor(int motorID) {
    u_int8_t motorON_data[8] = {0x88, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00};
    canSend(motorON_data, motorID);
    canRead();
    sleep(5);
    std::cout << "motor " << motorID << " is turned on" << std::endl;
}

// 37. Torque closed-loop command (0xA1)
// torque_int : 0 ~ 4096 which matches to (-32A ~ 32A)
//TODO: test motor torque in real world experiment.
void CanMotorX6_Hwayoung::setTorque(int motorID, int torque_int) {
    int temp = torque_int;
    if (torque_int < 0) {
        temp += 2 * pow(2, 15);
    }

    u_int8_t torqueLowerData = temp % 256;
    temp = temp / 256;
    u_int8_t torqueUpperData = temp % 256;
    u_int8_t torque_data[8] = {0Xa1, 0X00, 0X00, 0X00, torqueLowerData, torqueUpperData, 0X00, 0X00};
    canSend(torque_data, motorID);
    canRead();

    mAngularVelocity_rad = (mFrame.data[4] + mFrame.data[5] * 256) * deg2rad;

    mEncoderPast = mEncoder_temp;
    mEncoder_temp = mFrame.data[6] + mFrame.data[7] * 256;
    if((mEncoder_temp < 10000) && (mEncoderPast > 50000))
    {
        mEncoderMultiturnNum += 1;
    }
    else if((mEncoder_temp > 50000) && (mEncoderPast < 10000))
    {
        mEncoderMultiturnNum -= 1;
    }
    else
    {
        mEncoder = mEncoder_temp + 65535 * mEncoderMultiturnNum;
        mAngularPosition_rad = mEncoder * enc2rad / mGearRatio;
    }
}

#endif //CAMEL_CAN_MODULE_CANMOTORX6_HWAYOUNG_H