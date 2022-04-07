//
// Created by jaehoon on 22. 4. 7..
//
#include <iostream>
#include <sstream>
#include <cmath>

int main(){

    double gearRatio = 9.0;
    double position = 3.141592 * gearRatio;
    double rad2deg = 180 / 3.141592;
    double position_Deg = position * rad2deg * 100;
    int position_int = (int) round(position_Deg);
    std::cout<<position_int<<std::endl;
    int pos_0;
    int pos_1;
    int pos_2;
    int pos_3;

    std::stringstream ss;
    std::string s;

    ss << std::hex << position_int;
    s = ss.str();
    std::cout << s << std::endl;
    int temp = std::stoi(s);

//    00 02 78 d0 => d0 78 02 00 : 13*16
//    pos_0 = temp%100;
//    pos_1 = (temp/100)%100;
//    pos_2 = (temp/10000)%100;
//    pos_3 = (temp/1000000)%100;

    pos_0 = position_int%256;
    pos_1 = ((int)(position_int/256))%(256);
    pos_2 = ((int)(position_int/(256^2)))%(256);
    pos_3 = ((int)(position_int/(256^3)))%(256);
    std::cout << 100 / 120 << std::endl;

    std::cout << "place" << std::endl;
    temp = position_int;
    std::cout << temp % 256 << std::endl;
    temp = temp/256;
    std::cout << temp % 256 << std::endl;
    temp = temp/256;
    std::cout << temp % 256<< std::endl;
    temp = temp/256;
    std::cout << temp % 256<< std::endl;

    std::cout << 0xd0 <<std::endl;
    std::cout << 0x78 <<std::endl;
    std::cout << 0x02 <<std::endl;
    std::cout << 0x00 <<std::endl;

//    std::cout << pos_0 << std::endl;
//    std::cout << pos_1 << std::endl;
//    std::cout << pos_2 << std::endl;
//    std::cout << pos_3 << std::endl;
}
