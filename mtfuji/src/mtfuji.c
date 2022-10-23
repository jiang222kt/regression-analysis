#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "optimize.h"
#include "func1.h"

// data.csv内のデータ数最大値
#define NUM 32

int comp_alt(const void *x0, const void *x1)
{
    const Sample *p0 = (Sample *)x0;
    const Sample *p1 = (Sample *)x1;
    // "return p0->alt - p1->alt" dose not work! 
    // since p->alt is type of int!
    return p0->alt >= p1->alt ? 1: -1;
}

int main(const int argc, const char **argv)
{
    
    // 引数の個数が1の時だけ、alpha に第1引数を採用し、それ以外は0.01
    const double alpha = (argc == 2) ? atof(argv[1]) : 0.01;
    
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

    if((fp = fopen("../data.csv", "r")) == NULL){
        fprintf(stderr, "error: can't open %s\n", "data.csv");
        exit(EXIT_FAILURE);
    }

    char name[64];
    float alt;
    float temp;
    int ret;
    int i = 0;
    char *tmp;

    while (fgets(buf, bufsize, fp) != NULL ){
        ret = sscanf(buf, "%[^,],%f,%f\n", name, &alt, &temp);
        if (ret != 3) {
            fprintf(stderr, "sscanf error\n");
            exit(EXIT_FAILURE);            
        }
        tmp = (char *)malloc(64*sizeof(char));  // need error check
        if (tmp == NULL){
	        fprintf(stderr,"malloc error");
	        exit (EXIT_FAILURE);
        }
        strcpy(tmp, name);
        sample[i].loc = tmp;
        sample[i].alt = alt;
        sample[i].temp = temp;
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
	    printf("%2d: %-15s, %0.2f\t, %0.2f\n",i, sample[i].loc, sample[i].alt, sample[i].temp);
    }
    printf(" ==End of Data==\n");
    
    const int iter = optimize(alpha, dim, x, sample, num, f_gradient, f_value);
    
    printf("number of iterations = %d\n", iter);
    
    printf(" y = %.2fx + %.2f\n", x[0], x[1]);

    printf(" The temperature of Mt.Fuji (%.3fkm) is about %.3f degree(centigrade).\n", 3.776, x[0]*(3776.0 / 1000)  + x[1]);
    
    for(int i = 0; i < num; i++){
        free(sample[i].loc);
    }

    return 0;
}
