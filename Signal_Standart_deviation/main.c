/*
Created by : Emre ÖZTOKLU

Topic: DSP_Project

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIG_LENGTH  320
extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];

/*data types*/
double g_mean;
double g_variance;
double g_std_deviation;

/*function prototypes*/
double calc_signal_mean(double *sig_src_arr, size_t sig_lenght);
double calc_signal_variance(double *sig_src_arr, double sig_mean, size_t sig_length);
double calc_signal_std(double sig_variance);


int main(){
    g_mean = calc_signal_mean(InputSignal_f32_1kHz_15kHz, SIG_LENGTH);
    g_variance = calc_signal_variance(InputSignal_f32_1kHz_15kHz, g_mean, SIG_LENGTH);
    g_std_deviation =calc_signal_std(g_variance);

    printf("\n\nMean    = %f", g_mean);
    printf("\nVariance  = %f", g_variance);
    printf("\nStandard deviation = %f \n\n", g_std_deviation);

     //Mean = 0.037112
     //Variance = 0.620159
     //Standard deviation = 0.787502

    return 0;
}


double calc_signal_mean(double *sig_src_arr, size_t sig_lenght){
    double _mean = 0.0f;
    for (int i = 0 ; i < sig_lenght ; i++)
        _mean += *(sig_src_arr + i);
   return _mean /=(double)(sig_lenght);
}

double calc_signal_variance(double *sig_src_arr, double sig_mean, size_t sig_length){
    double _variance = 0.0f;
    for(int i = 0; i < sig_length ; i++)
        _variance += pow( (*(sig_src_arr + i) - sig_mean), 2 );
   return _variance /= (sig_length -1);
}

double calc_signal_std(double sig_variance){
    double _std = 0.0f;
    return _std = sqrt(sig_variance);
}
