#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "optimize.h"
#include "func.h"

// data.csv内のデータ数最大値
#define NUM 100

int comp_alt(const void *x0, const void *x1)
{
    const Sample *p0 = (Sample *)x0;
    const Sample *p1 = (Sample *)x1;
    // "return p0->alt - p1->alt" dose not work! 
    // since p->alt is type of int!
    return p0->rain >= p1->rain ? 1: -1;
}

int main(const int argc, const char **argv)
{
    
    // 引数の個数が1の時だけ、alpha に第1引数を採用し、それ以外は0.0001
    // alpha = 0.01 の場合は、収束しない
    const double alpha = (argc == 2) ? atof(argv[1]) : 0.0001;
    
    const int dim = f_dimension();
    
    double *x = malloc(dim * sizeof(double));
    for (int i = 0; i < dim; i++) {
	x[i] = 0;
    }
    
    printf("alpha = %f\n", alpha);

    // data.csv からデータを取得
    Sample sample[NUM];
    const size_t bufsize = 128;
    char buf[bufsize];
    FILE *fp;

    if((fp = fopen("../data-weather.csv", "r")) == NULL){
        fprintf(stderr, "error: can't open %s\n", "data.csv");
        exit(EXIT_FAILURE);
    }

    int year;
    float daylight, rain, temp, wind;
    int ret;
    int i = 0;

    while (fgets(buf, bufsize, fp) != NULL ){
        ret = sscanf(buf, "%d,%f,%f,%f,%f\n", &year, &daylight, &rain, &temp, &wind);
        if (ret != 5) {
            fprintf(stderr, "sscanf error\n");
            exit(EXIT_FAILURE);            
        }
        // norm のオーバフローを防ぐため、一部のデータをスケールダウンする
        sample[i].year = year;
        sample[i].daylight = daylight / 100.0;
        sample[i].rain = rain / 100.0;
        sample[i].temp = temp / 10;  
        sample[i].wind = wind; 
        i++;
    }

    fclose(fp);

    // num of data
    int num = i;  

        // before sort
    /*
    printf("== before ==\n");
    for (int i = 0 ; i < num ; i++){
	    printf("%d: %s\t, %0.2f, %0.2f\n",i, sample[i].loc, sample[i].alt, sample[i].temp);
    }
    */

    qsort(sample,num,sizeof(sample[0]),comp_alt);
    
    // after qsort
    printf(" ==Data sorted by [alt]==\n");
    for (int i = 0 ; i < num ; i++){
	    printf("%2d: %d, %0.2f, %.2f, %.2f, %.2f\n",i, sample[i].year, sample[i].daylight, sample[i].rain, sample[i].temp, sample[i].wind);
    }
    printf(" ==End of Data==\n");
    
    const int iter = optimize(alpha, dim, x, sample, num, f_gradient, f_value);
    
    printf("number of iterations = %d\n", iter);
    
    printf(" y = %.2fx1 + %.2fx2 + %.2fx3 + %.2f\n", x[0], x[1], x[2], x[3]);
    printf(" (y: daylight, x1: rain, x2: temp, x3: wind)\n");

    printf("Ex. The predicted daylight hour of August(%d) is about %.1f h.\n", 2019, 100*(x[0]*110/100.0+x[1]*28.4/10.0 + x[2]*3.2)); //2021年のrain, temp, windからdaylight hourを推定
    

    return 0;
}
