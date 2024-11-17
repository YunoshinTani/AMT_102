/**
 * @file example.cpp
 * @author 谷 優之心 (yunoshin.tani.0819@gmail.com)
 * @brief AMT_102.hpp の使用例
 * @version 1.2
 * @date 2024-11-10
 * @copyright Copyright (c) 2024
 */

#include <mbed.h>
#include "AMT_102.hpp"

#define PPR 1024

int main()
{
    AMT_102 encoder1(D4,D5);

    while (true)
    {
        // パルス
        printf("pulse:%lld  ", encoder1.read_pulse());
        // 角度
        printf("angle;%lf  ", encoder1.read_angle(PPR));
        // 回転数
        printf("rotation:%lf  ", encoder1.read_rotation(PPR));
        // 角度(0 < 360)
        printf("theta:%lf  ", encoder1.read_theta(PPR));

        printf("omega:%lf  ", encoder1.read_omega(PPR));

        printf("RPM:%lf  ", encoder1.read_RPM(PPR));

        printf("\n");

        // 3600度回転したらリセット
        if (encoder1.read_angle(PPR) > 3600){
            encoder1.reset();
        }
    }
}