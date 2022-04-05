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

// author@ Jaehyeong Park
/*
    TODO: 1. hex2rad, hex2rad/sec
          2. position limit 
          3. pd control loop
          4. command class
          5. EMC switch
*/

#define CAN_MAX_LEN 8

using namespace std;

int InitCanInterface(const char *ifname)
{
    //CAN socket 생성
    int sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    cout << sock << endl;
    if (sock == -1) {
        printf("Fail to create can socket for %s - %m \n", ifname);
        return -1;
    }
    printf("Success to create can socket for %s\n", ifname);

    //CAN 식별번호 획득
    struct ifreq ifr;
    strcpy(ifr.ifr_name, ifname );
    int ret = ioctl(sock,SIOCGIFINDEX, &ifr);
    if (ret == -1) {
        perror("Fail to get can interface index -");
        return -1;
    }
    printf("Success to get can interface index: %d\n", ifr.ifr_ifindex);

    //CAN socket 바인딩
    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    ret = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    if(ret == -1) {
        perror("Fail to bind can socket -");
        return -1;
    }
    printf("Success to bind can socket\n");

    return sock;
}

int cansend(const int sock, const u_int32_t id, const u_int8_t *data, const size_t data_len)
{
    //frame 설정
    struct can_frame frame;
    //can_frame frame;
    u_int32_t tempid = id;
    tempid = id & 0x1fffffff;
    // tempid |= (1<<31); 이부분 삭제 되어야함
    frame.can_id = tempid;
    memcpy(frame.data, data, data_len);
    frame.can_dlc = data_len; 

    
    //전송
    int tx_bytes = write(sock, &frame, sizeof(frame));
    if(tx_bytes == -1){
        perror("Fail to transmit can frame -");
        return -1;
    }
    cout << "success to transmit can frame " << tx_bytes << "is transmited" << endl;
    return 0;
}

int canread(const int sock)
{
    struct can_frame frame ;
    //usleep(1);
    int rx_bytes = read(sock, &frame, sizeof(frame));
    if(rx_bytes <0) {
        perror("Fail to receive can frame -");
        return -1;
    } else if (rx_bytes < (int)sizeof(struct can_frame)) {
        printf("Incomplete can frame is received -rx_bytes: %d\n", rx_bytes);
        return -1;
    } else if (frame.can_dlc > 8) {
        printf("Invalid dlc : %u\n", frame.can_dlc);
        return -1;
    }

    if(((frame.can_id >> 29) & 1) == 1) {
        printf("Error frame is received\n");
    } else if (((frame.can_id >>30)& 1) == 1) {
        printf("RTR frame is received\n");
    } else {
        printf("%d %d %d %d %d %d %d %d \n",frame.data[0],frame.data[1],frame.data[2],frame.data[3],frame.data[4],frame.data[5],frame.data[6],frame.data[7] );
    }

   
    

    return 0;
}

int main()
{
    struct can_frame frame;
    u_int32_t MOTOR_ID = 0x141;
    string command3= "sudo ip link set can8 up type can bitrate 1000000";
    const char *c3 = command3.c_str();
    system(c3);
    
    int sock = InitCanInterface("can8");
    if (sock <0) {
        return -1;
    }

    u_int8_t can_data1[CAN_MAX_LEN] = { 0X88, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00 };
    cansend(sock, MOTOR_ID, can_data1, sizeof(can_data1));
    canread(sock);
    sleep(5);   // run 코드 넣고 쉬어주면 코드 잘 돌아감!
    // ======= init ======= //
    
    
    u_int8_t can_data2[CAN_MAX_LEN] = { 0Xa1, 0X00, 0X00, 0X00, 0Xff, 0X00, 0X00, 0X00 };
    cansend(sock, MOTOR_ID, can_data2, sizeof(can_data2));
    canread(sock);
    canread(sock);
    canread(sock);
    canread(sock);
    canread(sock);
    sleep(2);
    u_int8_t can_data4[CAN_MAX_LEN] = { 0X90, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00 };
    cansend(sock, MOTOR_ID, can_data4, sizeof(can_data4));
    canread(sock);
    canread(sock);
    canread(sock);

    sleep(5);
    u_int8_t can_data3[CAN_MAX_LEN] = { 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00 };
    cansend(sock, MOTOR_ID, can_data3, sizeof(can_data3));
    sleep(2);
    

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


    //Speed closed-loop command(0xA2)


    // Position closed-loop command1 (0xA3)


    // Position closed-loop command2 (0xA4)


    // Position closed-loop command3 (0xA5)


    // Position closed-loop command4 (0xA6)

    return 0;
}