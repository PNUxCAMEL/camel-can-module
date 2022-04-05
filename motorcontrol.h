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

// author@ Jaehyeong Park
/*
    TODO: 1. hex2rad, hex2rad/sec
          2. position limit 
          3. pd control loop
          4. command class
          5. EMC switch
          6. multiple motorId is needed
*/

class motorcontrol {
public:
    motorcontrol(char* canName, u_int32_t motorId, std::string canName_temp, std::string bitRate){
        std::string command3= "sudo ip link set "+canName_temp+"up type can bitrate" + bitRate; // TODO: should be modified.
        const char *c3 = command3.c_str();
        system(c3);
        initCanInterface(canName);
        mMotorID = motorId;
    }

    void initCanInterface(const char *CanName);
    void turnOnMotor();
    void turnOffMotor();
    void canSend(const u_int8_t *data);
    void canRead();
    void getEncoder();
    void setTorque(int Torque);
    int getSock(){return mSock;}
    can_frame getFrame(){return mFrame;}

private:
    struct can_frame mFrame;
    const char *mCanName;
    int mSock;
    int mSendedCommand;
    u_int32_t mMotorID;
    u_int32_t mCanID;
};

void motorcontrol::initCanInterface(const char *ifname)
{
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
    strcpy(ifr.ifr_name, mCanName );
    int ret = ioctl(mSock,SIOCGIFINDEX, &ifr);
    if (ret == -1) {
        perror("Fail to get can interface index -");
        return;
    }
    printf("Success to get can interface index: %d\n", ifr.ifr_ifindex);

    //CAN socket 바인딩
    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    ret = bind(mSock, (struct sockaddr *)&addr, sizeof(addr));
    if(ret == -1) {
        perror("Fail to bind can socket -");
        return;
    }
    printf("Success to bind can socket\n");
}

void motorcontrol::turnOnMotor()
{
    u_int8_t motorON_data[8] = { 0x88, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00 };
    canSend(motorON_data);
}

void motorcontrol::turnOffMotor()
{
    u_int8_t motorON_data[8] = { 0x80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00 };
    canSend(motorON_data);
}

void motorcontrol::canSend(const u_int8_t *data) // TODO : motorId should be specified.
{
    u_int32_t tempid = mMotorID & 0x1fffffff;
    mFrame.can_id = tempid;
    memcpy(mFrame.data, data, sizeof(data));
    mFrame.can_dlc = sizeof(data); 

    
    //전송
    int tx_bytes = write(mSock, &mFrame, sizeof(mFrame));
    if(tx_bytes == -1){
        perror("Fail to transmit can frame -");
        return;
    }
    // std::cout << "success to transmit can frame " << tx_bytes << "is transmited" << std::endl;

    mSendedCommand = mFrame.data[0];
}

void motorcontrol::canRead()
{
    int rx_bytes = read(mSock, &mFrame, sizeof(mFrame));
    //feedback msg
    // TODO : Should be changed to better method.
    while(mFrame.data[0] != mSendedCommand)
    {
        rx_bytes = read(mSock, &mFrame, sizeof(mFrame));
    }
    printf("%d %d %d %d %d %d %d %d \n",mFrame.data[0],mFrame.data[1],mFrame.data[2],mFrame.data[3],mFrame.data[4],mFrame.data[5],mFrame.data[6],mFrame.data[7] );
}

/*

    read PID data command (0x30)
    reply DATA[2] = anglePidKp
    reply DATA[3] = anglePidKi
    reply DATA[4] = speedPidKp
    reply DATA[5] = speedPidKi
    reply DATA[6] = iqPidKp
    reply DATA[7] = iqPidKi
    */
   

    
    //Write PID to RAM command (0x31)
    
    
    //Write PID to ROM command (0x32)
    
    
    //Read acceleration data command (0x33)
    
    
    //Write acceleration data to RAM command (0x34)
    
    
    //Read encoder data command (0x90)
void motorcontrol::getEncoder()
{
    /* 
    1. encoder data 처리 필요
    */
    u_int8_t requestEncoder[8] = { 0X90, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00 };
    canSend(requestEncoder);
    canRead();
}

    //Write encoder offset command (0x91)


    //Write current position to ROM as motor zero command (0x19)


    //Read multi turns angle command (0x92)


    //Read single circle angle command (0x94)


    //Read motor status 1 and error flag commands (0x9A)


    //Clear motor error flag command (0x9B)


    //Read motor status 2 (0x9C)


    //Read motor status 3 (0x9D)


    //Motor off command (0x80)


    //Motor stop command (0x81)


    //Motor running command (0x88)



    //Torque closed-loop command (0xA1)
void motorcontrol::setTorque(int Torque)
{
    /* 
    1. 따로 데이터 변환 해줄 필요 있음
    2. 모터 회전 방향 지정해줘야함
    */

    u_int8_t torque_data[8] = { 0Xa1, 0X00, 0X00, 0X00, Torque, 0X00, 0X00, 0X00 };
    int iteration = 0;
    canSend(torque_data);
    int rx_bytes = read(mSock, &mFrame, sizeof(mFrame));
    //feedback msg
    while(mFrame.data[0] != 0Xa1)
    {
        rx_bytes = read(mSock, &mFrame, sizeof(mFrame));
    }

    // printf("%d %d %d %d %d %d %d %d \n",mFrame.data[0],mFrame.data[1],mFrame.data[2],mFrame.data[3],mFrame.data[4],mFrame.data[5],mFrame.data[6],mFrame.data[7] );
}

    //Speed closed-loop command(0xA2)


    // Position closed-loop command1 (0xA3)


    // Position closed-loop command2 (0xA4)


    // Position closed-loop command3 (0xA5)


    // Position closed-loop command4 (0xA6)


