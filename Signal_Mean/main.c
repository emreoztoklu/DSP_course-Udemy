#include <stdio.h>
#include <stdlib.h>

#define SIG_LENGTH  320
extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];


double calc_signal_mean(double *sig_src_arr, size_t sig_lenght);
double g_mean;

int main(){


    g_mean = calc_signal_mean(InputSignal_f32_1kHz_15kHz, SIG_LENGTH);

    printf("\n\nMean = %f \n\n\n", g_mean);

    // Output is  Mean = 0.037112


    return 0;
}


double calc_signal_mean(double *sig_src_arr, size_t sig_lenght){

    double _mean = 0.0f;

    for (int i = 0 ; i < sig_lenght ; i++){
        _mean += *(sig_src_arr + i);
    }

    _mean /=(double)(sig_lenght);

    return _mean;

}
