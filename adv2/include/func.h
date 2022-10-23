// Data from Japan Meteorological Agency (Tokyo, August)
typedef struct {
    int year;  
    double daylight; // daylight hours (h) 
    double rain;  // precipitation (mm)
    double temp;  // temperature (degree)
    double wind;  // wind speed (m/s)
} Sample;

#pragma once
int f_dimension();
double f_value(const double x[], const Sample s[], const int N);
void f_gradient(const double x[], const Sample s[], const int N, double g[]);