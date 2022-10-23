#pragma once
#include "func.h"

int optimize(const double alpha, const int dim, double x[], Sample sample[], int N, 
	     void (*calc_grad)(const double [], const Sample [], const int , double []),
         double (*calc_value)(const double [], const Sample [], const int));

