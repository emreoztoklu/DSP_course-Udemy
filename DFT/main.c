#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*DEFÝNES */
#define SIG_LENGHT  320
#define PI		    3.14159265358

/*data types*/
extern  double InputSignal_f32_1kHz_15kHz[SIG_LENGHT];

double Output_ReX[SIG_LENGHT/2];
double Output_ImX[SIG_LENGHT/2];


/*function prototypes*/
void calc_sig_dft(double *sig_src_arr, double *sig_dest_rex_arr, double *sig_dest_imx_arr, size_t sig_lenght);


int main(){

    FILE *fptr1, *fptr2,*fptr3;

    calc_sig_dft((double*)InputSignal_f32_1kHz_15kHz,
                 (double*)Output_ReX,
                 (double*)Output_ImX,
                 (size_t) SIG_LENGHT);


    fptr1 = fopen("input_signal.dat", "w");
    fptr2 = fopen("output_rex.dat", "w");
    fptr3 = fopen("output_imx.dat", "w");


    for(int i = 0; i < SIG_LENGHT; i++)
        fprintf(fptr1, "\n%f",InputSignal_f32_1kHz_15kHz[i]);

    for(int i = 0; i < (SIG_LENGHT/2); i++){
        fprintf(fptr2, "\n%f",Output_ReX[i]);
        fprintf(fptr3, "\n%f",Output_ImX[i]);

    }

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);

    return 0;
}


void calc_sig_dft(double *sig_src_arr, double *sig_dest_rex_arr, double *sig_dest_imx_arr, size_t sig_lenght){
    int i , j, k;
    /* ReX - ImX  arrays. And these each array's
       lenght will be half of source array

       1. first step is clean the arrays. Ýnitialize by null value ( you may use also memset )
       2. take DFT*/
    for ( j = 0 ; j < (sig_lenght / 2); j++){
        sig_dest_rex_arr[j] = 0;
        sig_dest_imx_arr[j] = 0;
    }

    for ( k = 0 ; k < (sig_lenght / 2); k++){
        for( i = 0; i < (sig_lenght); i++){
            sig_dest_rex_arr[k] =  sig_dest_rex_arr[k] +sig_src_arr[i] * cos(2 * PI * k * i / sig_lenght);
            sig_dest_imx_arr[k] =  sig_dest_imx_arr[k] -sig_src_arr[i] * sin(2 * PI * k * i / sig_lenght);
        }
    }
}
