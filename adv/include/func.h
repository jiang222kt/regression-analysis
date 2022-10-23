// adding longitude and latitude to the sample data
typedef struct {
    char *loc;   // location name
    double alt;  // altitude (km)
    double temp; // temperature (centigrade)
    double lgt;  // longitude
    double lat;  // latitude
} Sample;

#pragma once
int f_dimension();
double f_value(const double x[], const Sample s[], const int N);
void f_gradient(const double x[], const Sample s[], const int N, double g[]);