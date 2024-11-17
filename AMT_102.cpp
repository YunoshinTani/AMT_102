/**
 * @file AMT_102.cpp
 * @author 谷 優之心 (yunoshin.tani.0819@gmail.com)
 * @brief インクリメンタルエンコーダーの "AMT 102" から値を取得する
 * @version 1.2
 * @date 2024-11-10
 * @copyright Copyright (c) 2024
 */

#include "AMT_102.hpp"

AMT_102::AMT_102(PinName A_PHASE_PIN, PinName B_PHASE_PIN) : _A_PHASE(A_PHASE_PIN) , _B_PHASE(B_PHASE_PIN)
{
    _A_PHASE.rise(callback(this, &AMT_102::a_rise));
    _A_PHASE.fall(callback(this, &AMT_102::a_fall));
    total_pulse = 0;
}

void AMT_102::a_rise() {
    if(_B_PHASE) {
        total_pulse += 1;
    } else {
        total_pulse -= 1;
    }
}

void AMT_102::a_fall() {
    if(_B_PHASE) {
        total_pulse -= 1;
    } else {
        total_pulse += 1;
    }
}

void AMT_102::reset(){
    total_pulse = 0;
}

int64_t AMT_102::read_pulse(){
    return total_pulse;
}

double AMT_102::read_angle(uint32_t PPR){

    return -1.0 * (double)total_pulse / (PPR * 2.0) * 360.0;
}

double AMT_102::read_rotation(uint32_t PPR){
    return (double)read_angle(PPR) / 360.0;
}

double AMT_102::read_theta(uint32_t PPR){
    if (total_pulse >= 0){
        rotation_angle = total_pulse % (PPR * 2);
        return (double)rotation_angle / (PPR * 2.0) * 360.0;
    }
    else{
        rotation_angle = -1 * total_pulse % (PPR * 2);
        return 360.0 - (double)rotation_angle / (PPR * 2.0) * 360.0;
    }
}

double AMT_102::read_omega(uint32_t PPR){
    start_angle = 0.0;
    end_angle = 0.0;

    start_angle = read_angle(PPR);
    ThisThread::sleep_for(10ms);
    end_angle = read_angle(PPR);

    return (end_angle - start_angle) / 10.0;
}

void AMT_102::debug(){
    printf("%lld\n",AMT_102::read_pulse());
}