//
// Created by jaehoon on 22. 4. 7..
//
#include <iostream>
#include <sstream>
#include <cmath>
#include <math.h>

int main(){


    int num_int = -176;

    std::cout<<num_int<<std::endl;
    int pos_0;
    int pos_1;
    int pos_2;
    int pos_3;

    std::stringstream ss;
    std::string s;

    std::cout << "place" << std::endl;
    ss << std::hex << num_int;

    if(num_int < 0)
    {
        num_int += 2 * pow(2,15);
    }

    int temp = num_int;
    pos_0 = temp % 256;
    std::cout << pos_0 << std::endl;
    temp = temp/256;
    pos_1 = temp % 256;
    std::cout << pos_1 << std::endl;
    temp = temp/256;
    pos_2 = temp % 256;
    std::cout << pos_2 << std::endl;
    temp = temp/256;
    pos_3 = temp % 256;
    std::cout << pos_3 << std::endl;
}
