#include <stdio.h>
// 必要に応じてヘッダファイルを追加する
#include "func1.h"

int f_dimension()
{
    return 2;
}

double f_value(const double x[], const Sample s[], const int N)
{
    float result = 0;
    for(int i = 0; i < N; i++){
        result += (s[i].temp - x[0]*s[i].alt - x[1]) * (s[i].temp - x[0]*s[i].alt - x[1]);
    }
    return result;
}

void f_gradient(const double x[], const Sample s[], const int N, double g[])
{
    g[0] = 0;
    g[1] = 0;
    for(int i = 0; i < N; i++){
      g[0] += 2 * s[i].alt * (x[0] * s[i].alt + x[1] - s[i].temp);
      g[1] += 2 * (x[0] * s[i].alt + x[1] - s[i].temp);
    }
}

