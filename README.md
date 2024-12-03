# サンプルコード
```cpp
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
```