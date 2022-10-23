#include <stdio.h>
// 必要に応じてヘッダファイルを追加する
#include "func.h"

// daylight = a*rain + b*temp +c*wind + d (4 dimension)
int f_dimension()
{
    return 4;
}

double f_value(const double x[], const Sample s[], const int N)
{
    float result = 0;
    for(int i = 0; i < N; i++){
        result += (s[i].daylight - x[0]*s[i].rain - x[1]*s[i].temp - x[2]*s[i].wind - x[3]) * 
            (s[i].daylight - x[0]*s[i].rain - x[1]*s[i].temp - x[2]*s[i].wind - x[3]);
    }
    return result;
}

void f_gradient(const double x[], const Sample s[], const int N, double g[])
{
    for(int i = 0; i < N; i++){
        g[i] = 0;
    }

    for(int i = 0; i < N; i++){
      g[0] += 2 * s[i].rain * (x[0] * s[i].rain + x[1] * s[i].temp + x[2] * s[i].wind  - s[i].daylight);
      g[1] += 2 * s[i].temp * (x[0] * s[i].rain + x[1] * s[i].temp + x[2] * s[i].wind  - s[i].daylight);
      g[2] += 2 * s[i].wind * (x[0] * s[i].rain + x[1] * s[i].temp + x[2] * s[i].wind  - s[i].daylight);
      g[3] += 2 * (x[0] * s[i].rain + x[1] * s[i].temp + x[2] * s[i].wind  - s[i].daylight);
    }
}

