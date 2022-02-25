/*
    https://www.udemy.com/course/digital-signal-processing-dsp-from-ground-uptm-in-c/learn/lecture/12428846#overview
    Author : Emre ÖZTOKLU
    Date   : 03.2022
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/**@note Cutoff frequency is normalized and must be
* between 0 and 0.5 where 0.5 represents the nuyquisr freq.
*
* In this example the signal was sampled at 48kHz,
* therefore, the nyquist is 24 kHz
*
* i.e   24kHz-----------0.5
*       10kHz-----------0.2 : (10/24)*0.5 = 0.2
*/

/*DEFINES */
#define SIGNAL_LENGHT   320
#define KERNEL_LENGHT   29
#define M_PI		3.14159265358979323846

/**
KERNEL_LENGHT: from 0 to 29 Sample point will stay in zero
if you change this number then from 0 to your point will stay zero.
*/

/*data types*/
extern double InputSignal_f32_1kHz_15kHz[SIGNAL_LENGHT];

double OutputSignal[SIGNAL_LENGHT - KERNEL_LENGHT];
double OutputFilter[KERNEL_LENGHT];


double cutoff_freq = 0.2;


/*function prototypes*/
void lp_windowed_sinc_ftr(double* sig_src_arr, double* sig_dest_arr, double* fltr_kernel_dest_arr, double cutoff_freq, int filter_lenght, int input_sig_lenght);



int main(){
    FILE *fptr1, *fptr2, *fptr3;

    lp_windowed_sinc_ftr((double*) InputSignal_f32_1kHz_15kHz,
                         (double*) OutputSignal,
                         (double*) OutputFilter,
                         (double)  cutoff_freq,
                         (int)  KERNEL_LENGHT,
                         (int)  SIGNAL_LENGHT);

    fptr1 = fopen(".\\data\\output_signal.dat", "w");
    fptr2 = fopen(".\\data\\input_signal.dat",  "w");
    fptr3 = fopen(".\\data\\output_kernel.dat", "w");

    for(int i = 0; i < SIGNAL_LENGHT; i++){
        fprintf(fptr2, "\n%lf", InputSignal_f32_1kHz_15kHz[i]);
        if(i > KERNEL_LENGHT)
            fprintf(fptr1, "\n%lf", OutputSignal[i]);
        if(i < KERNEL_LENGHT)
            fprintf(fptr3, "\n%lf", OutputFilter[i]);
    }

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);
    return 0;
}


void lp_windowed_sinc_ftr(double* sig_src_arr, double* sig_dest_arr, double* fltr_kernel_dest_arr, double cutoff_freq, int filter_lenght, int input_sig_lenght){

// calculation the low-pass filter kernel

    for(int i =0; i < filter_lenght; i++){
        if(i - filter_lenght/2 == 0){
            fltr_kernel_dest_arr [i] = 2 * M_PI * cutoff_freq;
        }

        if(i - filter_lenght/2 != 0){
            fltr_kernel_dest_arr[i] = sin(2 * M_PI * cutoff_freq * (i - filter_lenght/2)) / (i - filter_lenght/2);
            fltr_kernel_dest_arr[i] *=(0.54 - 0.46 * cos(2 * M_PI * i / filter_lenght));                              // Hamming
        }
    }

// convolution the input signal and filter kernel

    for(int j = filter_lenght; j < input_sig_lenght ; j++){
        sig_dest_arr[j] = 0;
        for(int i = 0; i < filter_lenght; i++){
            sig_dest_arr[j] += sig_src_arr[j-i] * fltr_kernel_dest_arr[i];
        }
    }
}
