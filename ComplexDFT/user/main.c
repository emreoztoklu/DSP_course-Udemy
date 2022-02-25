/*
    Author: Emre ÖZTOKLU
    Date  : 02.2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*DEFINES */
#define SIZE_LENGHT  501
#define PI		     3.141592653589

/*data types*/
extern double  _501pts_20Hz_sig_rex[SIZE_LENGHT];   // in time domain
extern double  _501pts_20Hz_sig_imx[SIZE_LENGHT];   // in time domain


double *rex_ptr = (double*) &_501pts_20Hz_sig_rex;
double *imx_ptr = (double*) &_501pts_20Hz_sig_imx;

double Output_rex[SIZE_LENGHT];             // in freq domain
double Output_imx[SIZE_LENGHT];             // in freq domain


/*function prototypes*/
void complex_dft(double* sig_src_time_domain_rex, double* sig_src_time_domain_imx, double* sig_src_freq_domain_rex, double* sig_src_freq_domain_imx, size_t sig_lenght);


int main(){

    FILE *input_rex_fptr, *input_imx_fptr, *output_rex_fptr, *output_imx_fptr;

    complex_dft((double*) rex_ptr,
                (double*) imx_ptr,
                (double*) Output_rex,
                (double*) Output_imx,
                (size_t ) SIZE_LENGHT);

    input_rex_fptr   = fopen(".\\data\\input_rex.dat",  "w");
    input_imx_fptr   = fopen(".\\data\\input_imx.dat",  "w");
    output_rex_fptr  = fopen(".\\data\\output_rex.dat", "w");
    output_imx_fptr  = fopen(".\\data\\output_imx.dat", "w");


    for(int i = 0; i < SIZE_LENGHT; i++){
        fprintf(input_rex_fptr, "\n%f", rex_ptr[i]);
        fprintf(input_imx_fptr, "\n%f", imx_ptr[i]);
        fprintf(output_rex_fptr,"\n%f", Output_rex[i]);
        fprintf(output_imx_fptr,"\n%f", Output_imx[i]);
    }

    fclose(input_rex_fptr);
    fclose(input_imx_fptr);
    fclose(output_rex_fptr);
    fclose(output_imx_fptr);

    return 0;
}

void complex_dft(double* sig_src_time_domain_rex, double* sig_src_time_domain_imx, double* sig_src_freq_domain_rex, double* sig_src_freq_domain_imx, size_t sig_lenght){

    double SR, SI;

    for(int k = 0; k < (sig_lenght -1); k++){    // (sig_lenght -1)  ==> N-1
        for (int i = 0; i <(sig_lenght -1); i++){
            SR = cos(2 * PI * k * i/sig_lenght);
            SI =-sin(2 * PI * k * i/sig_lenght);

            sig_src_freq_domain_rex[k] += (sig_src_time_domain_rex[i] * SR - sig_src_time_domain_imx[i] * SI );
            sig_src_freq_domain_imx[k] += (sig_src_time_domain_imx[i] * SI - sig_src_time_domain_imx[i] * SR );
        }
    }
}































