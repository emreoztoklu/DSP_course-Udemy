/*
Created by : Emre ÖZTOKLU

Topic: DSP_Project _ "Convolution"

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIG_LENGTH      320
#define IMP_RSP_LENGHT  29

extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
extern double  Impulse_response[IMP_RSP_LENGHT];

/*data types*/
double Output_signal[ SIG_LENGTH + IMP_RSP_LENGHT ];


/*function prototypes*/
void convolution(double *sig_src_arr, double *sig_dest_arr, double *impulse_response_arr, size_t sig_src_lenght, size_t impulse_response_lenght);



int main(){

    FILE *input_sig_fptr, *imp_rsp_fptr, *output_sig_fptr;


    convolution((double *)InputSignal_f32_1kHz_15kHz, (double *)Output_signal, (double *)Impulse_response, (size_t)SIG_LENGTH, (size_t)IMP_RSP_LENGHT);


    input_sig_fptr  = fopen("input_signal.dat", "w");
    imp_rsp_fptr    = fopen("impulse_response.dat", "w");
    output_sig_fptr = fopen("output_signal.dat", "w");

    /*Write in file Input_signal*/

    for(int i = 0; i < SIG_LENGTH ; i++)
        fprintf(input_sig_fptr, "\n%f", *(InputSignal_f32_1kHz_15kHz + i));
    fclose(input_sig_fptr);

    /*Write in file Impulse_response*/

    for(int i = 0; i < IMP_RSP_LENGHT ; i++)
        fprintf(imp_rsp_fptr, "\n%f", *(Impulse_response + i));
    fclose(imp_rsp_fptr);

    /*Write in file Output_signal*/

    for(int i = 0; i < SIG_LENGTH + IMP_RSP_LENGHT ; i++)
        fprintf(output_sig_fptr, "\n%f", *(Output_signal + i));
    fclose(output_sig_fptr);




    return 0;
}




void convolution(double *sig_src_arr, double *sig_dest_arr, double *impulse_response_arr, size_t sig_src_lenght, size_t impulse_response_lenght){

    int i , j;

    for(i = 0; i < (sig_src_lenght + impulse_response_lenght) ; i++){
        sig_dest_arr[i] = 0;
    }

    for (i = 0; i < sig_src_lenght ; i++){

        for(j = 0; j < impulse_response_lenght; j++){

            sig_dest_arr[i+j] = sig_dest_arr[i+j] + sig_src_arr[i] * impulse_response_arr[j];
        }
    }
}

