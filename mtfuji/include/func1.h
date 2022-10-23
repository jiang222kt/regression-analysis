typedef struct {
    char *loc;   // location name
    double alt;  // altitude (km)
    double temp; // temperature (centigrade)
} Sample;

#pragma once
int f_dimension();
double f_value(const double x[], const Sample s[], const int N);
void f_gradient(const double x[], const Sample s[], const int N, double g[]);