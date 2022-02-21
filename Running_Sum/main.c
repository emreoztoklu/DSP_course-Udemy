/*
Created by : Emre ÖZTOKLU

Topic: DSP_Project _ "Running Sum"

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIG_LENGTH      320

extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];


/*data types*/
double Output_signal[SIG_LENGTH];


/*function prototypes*/
void calc_running_sum ( double *sig_src_arr, double *sig_dest_arr, size_t sig_lenght);


int main(){

    FILE *input_sig_fptr, *output_sig_fptr;

    calc_running_sum ( (double*)InputSignal_f32_1kHz_15kHz, (double*)Output_signal,(size_t)SIG_LENGTH);

    input_sig_fptr  = fopen("input_signal.dat", "w");
    output_sig_fptr = fopen("output_signal.dat", "w");

    /*Write in file Input_signal*/
    for(int i = 0; i < SIG_LENGTH ; i++)
        fprintf(input_sig_fptr, "\n%f", *(InputSignal_f32_1kHz_15kHz + i));
    fclose(input_sig_fptr);


    /*Write in file Output_signal*/
    for(int i = 0; i < SIG_LENGTH ; i++)
        fprintf(output_sig_fptr, "\n%f", *(Output_signal + i));
    fclose(output_sig_fptr);


    return 0;
}


void calc_running_sum ( double *sig_src_arr, double *sig_dest_arr, size_t sig_lenght){

    for(int i = 0; i < sig_lenght ; i++){

        sig_dest_arr[i] = sig_dest_arr[i-1] + sig_src_arr[i];
    }
}

