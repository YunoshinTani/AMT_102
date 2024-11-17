/**
 * @file AMT_102.hpp
 * @author 谷 優之心 (yunoshin.tani.0819@gmail.com)
 * @brief インクリメンタル型エンコーダーの "AMT 102" から値を取得する
 * @version 1.2
 * @date 2024-11-10
 * @copyright Copyright (c) 2024
 */

#ifndef AMT_102_H
#define AMT_102_H

#include <mbed.h>

/**
 * @brief インクリメンタル型エンコーダー「AMT 102」の制御
 * @note コンストラクタを呼び出した時点で、割り込み処理が開始されます
 */
class AMT_102
{
public:
    /**
     * @brief コンストラクタ
     * @param A_PHASE_PIN A相のピン
     * @param B_PHASE_PIN B相のピン
     * @return なし
     * @note これを呼び出した時点で、割り込み処理が開始されます
     */
    AMT_102(PinName A_PHASE_PIN, PinName B_PHASE_PIN);

    /**
     * @brief エンコーダーのパルス数を0にリセットします
     * @param なし
     * @return なし
     * @note カウントを0にするだけです
     */
    void reset();

    /**
     * @brief エンコーダーの値を読む
     * @param なし
     * @return エンコーダーから読んだパルス数
     * @warning エンコーダーの分解能によって値は変わる
     * @note 1回転が分解能と同じ値になる
     */
    int64_t read_pulse();

    /**
     * @brief 回転した合計の角度を読む
     * @param PPR エンコーダーの分解能
     * @return 回転した合計の角度
     * @note (右回しで+,左回しで-) (変域はない)
     */
    double read_angle(uint32_t PPR);

    /**
     * @brief 回転数を読む
     * @param PPR エンコーダーの分解能
     * @return 回転数(何回転したか)
     * @note (右で増える、左で減る)
     */
    double read_rotation(uint32_t PPR);

    /**
     * @brief 回転した角度を読む
     * @param PPR エンコーダーの分解能
     * @return 回転した角度
     * @note (右で増える、左で減る、-になることはない) (0 < 360) 
     */
    double read_theta(uint32_t PPR);

    /**
     * @brief 角速度を読む
     * @param PPR エンコーダーの分解能
     * @return 角速度
     * @note 単位(度/ms)
     */
    double read_omega(uint32_t PPR);

    /**
     * @brief デバッグ用関数 エンコーダーの値をprintf
     * @param なし
     * @return なし
     * @note エンコーダーのテスト用に
     */
    void debug();

private:
    /**
     * @brief A相の信号の割り込み入力ピン
     */
    InterruptIn _A_PHASE;

    /**
     * @brief B相の信号の割り込み入力ピン
     */
    InterruptIn _B_PHASE;

    /**
     * @brief エンコーダーから取得した最終的な値
     */
    volatile int64_t total_pulse;

     /**
     * @brief エンコーダーから取得した最終的な値に変域(0<1回転)をつけた値
     */   
    volatile int64_t rotation_angle;

     /**
     * @brief タイマー開始時の角度
     */   
    double start_angle = 0;

     /**
     * @brief 100ms後の角度
     */   
    double end_angle = 0;

    /**
     * @brief A相の立ち上がり
     * @param なし
     * @return なし
     * @note ユーザーが使うことはない ピン割り込み時に実行
     */
    void a_rise();

    /**
     * @brief A相の立下がり
     * @param なし
     * @return なし
     * @note ユーザーが使うことはない ピン割り込み時に実行
     */
    void a_fall();
};

#endif // AMT_102_H