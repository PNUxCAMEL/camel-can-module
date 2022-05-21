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

    void initCanInterface(const char *CanName);

    void stopMotor(int motorID);

    void turnOnMotor(int motorID);

    void turnOffMotor(int motorID);

    void canSend(const u_int8_t *data, int motorID);

    void canRead();

    void getEncoder(int motorID);

    float getMultiturnAngularPosition(int motorID);

    void setTorque(int Torque, int motorID);

    void setVelocity(int Velocity, int motorID);

    void setPosition1(int motorID, double position);

    void setPosition2(int motorID, double desiredPosition_rad, int maxSpeed_dps);

    int getSock() { return mSock; }

    can_frame getFrame() { return mFrame; }

private:
    struct can_frame mFrame;
    const char *mCanName;
    int mSock;
    int mSendedCommand;
    int mGearRatio = 6;
    u_int32_t mCanID;
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









// 1. Read Position loop KP data command (0x30)
// 2. Read Position lop Ki data command (0x31)
// 3. Read Speed loop KP data command (0x32)
// 4. Read Speed loop Ki data command (0x33)
// 5. Read Current loop KP data command (0x34)
// 6. Read Current loop Ki data command (0x35)
// 7. Write Position loop KP data to RAM command (0x36)
// 8. Write Position loop Ki data to RAM command (0x37)
// 9. Write Speed loop KP data to RAM command (0x38)
// 10. Write Speed loop Ki data to RAM command (0x39)
// 11. Write Current loop KP data to RAM command (0x3A)
// 12. Write Current loop Ki data to RAM command (0x3B)
// 13. Write Position loop KP data to ROM command (0x3C)
// 14. Write Position loop Ki data to ROM command (0x3D)
// 15. Write Speed loop KP data to ROM command (0x3E)
// 16. Write Speed loop Ki data to ROM command (0x3F)
// 17. Write Current loop KP data to ROM command (0x40)
// 18. Write Current loop Ki data to ROM command (0x41)
// 19. Read acceleration data command (0x42)
// 20. Write acceleration data to RAM command (0x43)
// 21. Read multiturn encoder position command (0x60)
// 22. Read multiturn encoder original position command (0x61)
// 23. Read multiturn encoder offset command (0x62)
// 24. Write multiturn encoder values to ROM as motor zero command (0x63)
// 25. Write multiturn encoder current position to ROM as motor zero command (0x64)

// 26. Read encoder data command (0x90)
//TODO
void CanMotorX6_Hwayoung::getEncoder(int motorID) {
    /*
    1. encoder data 처리 필요
    */
    u_int8_t requestEncoder[8] = {0X90, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00};
    canSend(requestEncoder, motorID);
    canRead();
    printf("%d %d %d %d %d %d %d %d \n", mFrame.data[0], mFrame.data[1], mFrame.data[2], mFrame.data[3], mFrame.data[4],
           mFrame.data[5], mFrame.data[6], mFrame.data[7]);
}

// 27. Write encoder values to ROM as motor zero command (0x91)
// 28. Write current position to ROM as motor zero command (0x19)
// 29. Read multiturn turns angle command (0x92)
//TODO
float CanMotorX6_Hwayoung::getMultiturnAngularPosition(int motorID) {
    u_int8_t requestEncoder[8] = {0X92, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00};
    canSend(requestEncoder, motorID);
    canRead();
    float degree = (
                           mFrame.data[4] +
                           mFrame.data[5] * 256.0 +
                           mFrame.data[6] * 256.0 * 256.0 +
                           mFrame.data[7] * 256.0 * 256.0 * 256.0) * 0.01 / mGearRatio;
    if (mFrame.data[7] > 127) {
        degree += - 256.0 * 256.0 * 256.0 * 256.0 * 0.01 / mGearRatio;
    }
    return degree;
}

// 30. Read single circle ange command (0x94)
// 31. Read motor status 1 and error flag commands (0x9A)
// 32. Read motor status 2 (0x9C)
// 33. Read motor status 3 (0x9D)

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

    /*
    1. 따로 데이터 변환 해줄 필요 있음
    2. 모터 회전 방향 지정해줘야함
    */
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
}

// 38. Speed closed-loop command (0xA2)
//TODO
void CanMotorX6_Hwayoung::setVelocity(int motorID, int velocity) {
    //0.01dps/LSB
    u_int8_t velocity_data[8] = {0Xa2, 0X00, 0X00, 0X00, 0x00, velocity, 0X00, 0X00};
    int iteration = 0;
    canSend(velocity_data, motorID);
    canRead();
}

// 39. Position closed-loop command 1 (0xA3)
//TODO
void CanMotorX6_Hwayoung::setPosition1(int motorID, double desiredPosition_rad) {
    //0.01rad/LSB
    double rad2deg = 180 / 3.141592;
    double position_Deg = desiredPosition_rad * rad2deg * 100 * mGearRatio;
    int position_int = (int) round(position_Deg);

    u_int8_t pos0;
    u_int8_t pos1;
    u_int8_t pos2;
    u_int8_t pos3;


    int temp = position_int;
    pos0 = temp % 256;
    temp = temp / 256;
    pos1 = temp % 256;
    temp = temp / 256;
    pos2 = temp % 256;
    temp = temp / 256;
    pos3 = temp % 256;

    u_int8_t velocity_data[8] = {0Xa3, 0X00, 0X00, 0X00, pos0, pos1, pos2, pos3};
    int iteration = 0;
    canSend(velocity_data, motorID);
    canRead();
}

// 40. Position closed-loop command 2 (0xA4)
//TODO
void CanMotorX6_Hwayoung::setPosition2(int motorID, double desiredPosition_rad, int maxSpeed_dps) {
    //0.01rad/LSB
    double rad2deg = 180 / 3.141592;
    double position_Deg = desiredPosition_rad * rad2deg * 100 * mGearRatio;
    int position_int = (int) round(position_Deg);

    u_int8_t pos0;
    u_int8_t pos1;
    u_int8_t pos2;
    u_int8_t pos3;

    u_int8_t maxSpeed0;
    u_int8_t maxSpeed1;

    int temp = position_int;
    pos0 = temp % 256;
    temp = temp / 256;
    pos1 = temp % 256;
    temp = temp / 256;
    pos2 = temp % 256;
    temp = temp / 256;
    pos3 = temp % 256;

    temp = maxSpeed_dps;
    maxSpeed0 = temp % 256;
    temp = temp / 256;
    maxSpeed1 = temp % 256;

    u_int8_t velocity_data[8] = {0Xa4, 0X00, maxSpeed0, maxSpeed1, pos0, pos1, pos2, pos3};
    int iteration = 0;
    canSend(velocity_data, motorID);
    canRead();
}
// 41. Position closed-loop command 3 (0xA5)
// 42. Position closed-loop command 4 (0xA6)
// 43. Multiturn incremental position control command (0xA7)
// 44. Multiturn incremental position control command (0xA8)
// 45. read running mode (0x70)
// 46. read power value (0x71)
// 47. read Battery voltage (0x72)
// 48. TF command (0x73)
// 49. System reset command (0x76)
// 50. Brake opening command (0x77)
// 51. Brake close command (0x78)
// 52. CAN ID setting and reading (0x79)









#endif //CAMEL_CAN_MODULE_CANMOTORX6_HWAYOUNG_H
