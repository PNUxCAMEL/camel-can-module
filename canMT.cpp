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

struct test{
    int moterNum;
};

class canMT{
public:
    void setMotorID(u_int32_t motorID){mMotorID = motorID;}
    void setCanID(char canID){mCanID = canID;}
    void setCanMaxLength(int canMaxLength){mCanMaxLength = canMaxLength;}
    void setBitRate(int bitRate){mBitRate = bitRate;}
    
    // void setCanData(u_int8_t canData)(mCanData = canData;)

    u_int32_t getMotorID() const {return mMotorID;}
    char getCanID() const {return mCanID;}
    int getCanMaxLength() const {return mCanMaxLength;}
    // u_int8_t getCanData() const {return mCanData;}
    int getBitRate() const {return mBitRate;}
    const int getSocket() const {return mSocket;}
    
    void initialize();
    void initializeSocket();
    void initializeMotor();

    bool isSocketAvailable();
    // void read();


private:
    test Moter;
    // motor 갯수
    // 각 motorID
    // 각 data
    // 각 mCanMaxlength
    // 
    u_int32_t mMotorID;
    int mCanMaxLength;
    // u_int8_t mCanData[mCanMaxLength];

    // can에만 해당
    char mCanID;
    int mBitRate;
    int mSocket;

};

void canMT::initialize() 
{
    //CAN socket 생성
    initializeSocket();
    if(!isSocketAvailable()){std::cout<<"Socket is not available."<<std::endl; return -1;}

    
}

void canMT::initializeSocket(){

    mSocket = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if (mSocket == -1) {
        printf("Fail to create can socket for %s - %m \n", ifname);
        return -1;
    }
    printf("Success to create can socket for %s\n", ifname);

    //CAN 식별번호 획득
    struct ifreq ifr;
    strcpy(ifr.ifr_name, mCanID );
    if (ioctl(mSocket,SIOCGIFINDEX, &ifr) == -1) {
        perror("Fail to get can interface index -");
        return -1;
    }
    printf("Success to get can interface index: %d\n", ifr.ifr_ifindex);

    //CAN socket 바인딩
    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if(bind(mSocket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("Fail to bind can socket -");
        return -1;
    }
    printf("Success to bind can socket\n");
}

void canMT::initializeMotor(){

}

bool canMT::isSocketAvailable(){
    if (mSocket <0) {
        return false;
    }
    else {
        return true;
    }
}

void assginbitrate() const
{
    string command= "sudo ip link set" + mCanID + "up type can bitrate" + mBitRate;
    const char *c = command.c_str();
    system(c);
    
}

void send() const // changes : const, data_len is deleted
{
    
}