
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
*  https://tr.wikipedia.org/wiki/Nyquist_frekans%C4%B1
*
*  Fsamp / 2 = Fnyq
*
* i.e   24kHz-----------0.5
*       10kHz-----------0.2 : (10/24)*0.5 = 0.2
*
*  -1    -0.5    0    0.5     1
*  -48   -24     0    24      48
*
*/

#define SAMPLE_FREQ              (48000)              // 48kHz
#define NYQUIST_FREQ             (24000)              // 48/2 = 24kHz is NYQUIST_FREQ
#define NORMALIZED_NYQUIST_FREQ  (0.5)

#define LW_CUTOFF_FREQ           (0.1 * 1000)          // 0.1 khz
#define UP_CUTOFF_FREQ           (5.28 * 1000)         // 5.2 kHz

/*DEFINES */
#define SIGNAL_LENGHT   (320)
#define KERNEL_LENGHT   (29)
#define M_PI             3.14159265358979323846        // pi


/*freq_data types*/
double lw_cutoff_freq = (LW_CUTOFF_FREQ / NYQUIST_FREQ) * NORMALIZED_NYQUIST_FREQ;
double up_cutoff_freq = (UP_CUTOFF_FREQ / NYQUIST_FREQ) * NORMALIZED_NYQUIST_FREQ;

/*data types*/
extern double InputSignal_f32_1kHz_15kHz[SIGNAL_LENGHT];
double *sig_src_ptr = (double*)&InputSignal_f32_1kHz_15kHz;

double OutputSignal[SIGNAL_LENGHT - KERNEL_LENGHT];
double OutputFilter[KERNEL_LENGHT];

double stat_lw_cutoff_buff[KERNEL_LENGHT];
double stat_up_cutoff_buff[KERNEL_LENGHT];


/*function prototypes*/
void bandpassWindowedSincfltr(double* lower_cutoff_state_buff, double* upper_cutoff_state_buff, double* fltr_kernel_dest_arr,
                              double lower_cutoff, double upper_cutoff, int filter_lenght,
                              double* sig_src_arr, double* sig_dest_arr, int input_sig_lenght);

int main(){

    FILE* fptr1, * fptr2, * fptr3;

    bandpassWindowedSincfltr((double*) &stat_lw_cutoff_buff,(double*) &stat_up_cutoff_buff, (double*) &OutputFilter,
                             (double ) lw_cutoff_freq,     (double ) up_cutoff_freq, (int) KERNEL_LENGHT,
                             (double*) &sig_src_ptr,       (double*) &OutputSignal,  (int) SIGNAL_LENGHT);


    fptr1 = fopen(".\\data\\input_signal.dat",  "w");
    fptr2 = fopen(".\\data\\output_signal.dat", "w");
    fptr3 = fopen(".\\data\\output_kernel.dat", "w");

    for(int i = 0; i < SIGNAL_LENGHT; i++){
        fprintf(fptr1, "\n%lf",  sig_src_ptr[i]);
        if(i > KERNEL_LENGHT)
            fprintf(fptr2, "\n%lf", OutputSignal[i]);
        if(i < KERNEL_LENGHT)
            fprintf(fptr3, "\n%lf", OutputFilter[i]);
    }

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);
    return 0;
}


void bandpassWindowedSincfltr(double* lower_cutoff_state_buff, double* upper_cutoff_state_buff, double* fltr_kernel_dest_arr,
                              double lower_cutoff, double upper_cutoff, int filter_lenght,
                              double* sig_src_arr, double* sig_dest_arr,int input_sig_lenght){
/**********************************************************************************/
// calculate first low-pass filter kernel   (lower_cutoff freq)
    for(int i = 0; i < filter_lenght; i++){
        if(i - filter_lenght/2 == 0){
            lower_cutoff_state_buff[i] = 2 * M_PI *lower_cutoff;        //top-off level
        }
        if(i - filter_lenght/2 != 0){
            lower_cutoff_state_buff[i] = sin(2*M_PI*lower_cutoff*(i-filter_lenght/2))/(i-filter_lenght/2);
            lower_cutoff_state_buff[i] *= (0.42 - 0.5*cos(2*M_PI*i/filter_lenght) + 0.08*cos(4*M_PI*i/filter_lenght));  // BlackMan Window function
        }
    }
/**********************************************************************************/
// calculate second low-pass filter kernel   (upper_cutoff freq)

    for(int i = 0; i < filter_lenght; i++){
        if(i - filter_lenght/2 == 0){
           upper_cutoff_state_buff[i] = 2 * M_PI * upper_cutoff;        //top-off level
        }
        if(i - filter_lenght/2 != 0){
            upper_cutoff_state_buff[i] = sin(2 * M_PI *upper_cutoff*(i-filter_lenght/2))/(i-filter_lenght/2);
            upper_cutoff_state_buff[i] *= (0.42 - 0.5*cos(2*M_PI*i/filter_lenght) + 0.08*cos(4*M_PI*i/filter_lenght));  // BlackMan Window function
        }
    }
/**********************************************************************************/
// change low-pass filter to a high-pass filter using Spectral Inversion

    for(int i = 0; i < filter_lenght ; i++){
       upper_cutoff_state_buff[i] = -(upper_cutoff_state_buff[i]);
    }
    upper_cutoff_state_buff[filter_lenght/2] += 1;
/**********************************************************************************/
//Add  low-pass filter kernel to high-pass filter kernel to form a band-reject filter kernel

    for(int i = 0; i < filter_lenght; i++){
        fltr_kernel_dest_arr[i] = lower_cutoff_state_buff[i] + upper_cutoff_state_buff[i];
    }
/**********************************************************************************/
//change band-reject filter into bandpass filter using spectral inversion

    for(int i = 0; i < filter_lenght; i++){
        fltr_kernel_dest_arr [i] = -fltr_kernel_dest_arr[i];
   }
   fltr_kernel_dest_arr[filter_lenght/2] +=1;
/**********************************************************************************/
//Convolve the input signal and filter kernel

    for(int j = filter_lenght; j < input_sig_lenght; j++){
        sig_dest_arr[j] = 0;
        for(int i = 0; i < filter_lenght; i++){
            sig_dest_arr[j] += sig_src_arr[j-i] * fltr_kernel_dest_arr[i];
        }
    }
}

