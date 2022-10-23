#include <stdio.h>
// 必要に応じてヘッダファイルを追加する
#include "func.h"

// temp = a*alt + b*lgt +c*lat + d (4 dimension)
int f_dimension()
{
    return 4;
}

double f_value(const double x[], const Sample s[], const int N)
{
    float result = 0;
    for(int i = 0; i < N; i++){
        result += (s[i].temp - x[0]*s[i].alt - x[1]*s[i].lgt - x[2]*s[i].lat - x[3]) * 
            (s[i].temp - x[0]*s[i].alt - x[1]*s[i].lgt - x[2]*s[i].lat - x[3]);
    }
    return result;
}

void f_gradient(const double x[], const Sample s[], const int N, double g[])
{
    for(int i = 0; i < N; i++){
        g[i] = 0;
    }

    for(int i = 0; i < N; i++){
      g[0] += 2 * s[i].alt * (x[0] * s[i].alt + x[1] * s[i].lgt + x[2] * s[i].lat  - s[i].temp);
      g[1] += 2 * s[i].lgt * (x[0] * s[i].alt + x[1] * s[i].lgt + x[2] * s[i].lat  - s[i].temp);
      g[2] += 2 * s[i].lat * (x[0] * s[i].alt + x[1] * s[i].lgt + x[2] * s[i].lat  - s[i].temp);
      g[3] += 2 * (x[0] * s[i].alt + x[1] * s[i].lgt + x[2] * s[i].lat  - s[i].temp);
    }
}

