#define _CRT_SECURE_NO_WARNINGS             // it says fopen is deprecated

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*DEFINES */
#define SIG_LENGHT  640
#define PI		    3.141592653589

/*data types*/
extern double InputSignal_f32_1kHz_15kHz[320];  //#define SIG_LENGHT  320
extern double _640_points_ecg_[SIG_LENGHT];            //#define SIG_LENGHT  640

double Output_ReX   [SIG_LENGHT/2];
double Output_ImX   [SIG_LENGHT/2];
double Output_MAG   [SIG_LENGHT/2];
double Output_IDFT  [SIG_LENGHT];

//double *InputSignal_ptr = (double*)&InputSignal_f32_1kHz_15kHz;
double *InputSignal_ptr = (double*)&_640_points_ecg_;


/*function prototypes*/
void    calc_sig_dft        (double* sig_src_arr,  double* sig_dest_rex_arr, double* sig_dest_imx_arr, size_t sig_lenght);
void    sig_calc_idft       (double* idft_out_arr, double* sig_src_rex_arr,  double* sig_src_imx_arr,  size_t idft_lenght);
void    get_dft_output_mag  (double* sig_dest_mag_arr);



int main(){

    FILE *fptr1, *fptr2, *fptr3, *fptr4, *fptr5;

    calc_sig_dft((double*)InputSignal_ptr, (double*)Output_ReX, (double*)Output_ImX, (size_t) SIG_LENGHT);
    get_dft_output_mag((double*)Output_MAG);
    sig_calc_idft((double*)Output_IDFT, (double*)Output_ReX, (double*)Output_ImX, (size_t) SIG_LENGHT);


    fptr1 = fopen(".\\data\\input_signal.dat", "w");
    fptr2 = fopen(".\\data\\output_rex.dat"  , "w");
    fptr3 = fopen(".\\data\\output_imx.dat"  , "w");
    fptr4 = fopen(".\\data\\output_mag.dat"  , "w");
    fptr5 = fopen(".\\data\\output_idft.dat"  , "w");


    for(int i = 0; i < SIG_LENGHT; i++){
        fprintf(fptr1, "\n%f",InputSignal_ptr[i]);
        fprintf(fptr5, "\n%f",Output_IDFT[i]);
    }

    for(int i = 0; i < (SIG_LENGHT/2); i++) {
        fprintf(fptr2, "\n%f",Output_ReX[i]);
        fprintf(fptr3, "\n%f",Output_ImX[i]);
        fprintf(fptr4, "\n%f",Output_MAG[i]);
    }

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);
    fclose(fptr4);


    return 0;
}

/*Discrete Fourier Transform  of Signal*/
void calc_sig_dft(double *sig_src_arr, double *sig_dest_rex_arr, double *sig_dest_imx_arr, size_t sig_lenght){
    int i , j, k;
    /* ReX - ImX  arrays. And these each array's
       lenght will be half of source array

       1. first step is clean the arrays. Initialize by null value ( you may use also memset )
       2. take DFT*/
    for ( j = 0 ; (j < sig_lenght / 2); j++){
        sig_dest_rex_arr[j] = 0;
        sig_dest_imx_arr[j] = 0;
    }

    for ( k = 0 ; k < (sig_lenght / 2); k++){
        for( i = 0; i < (sig_lenght); i++){
            sig_dest_rex_arr[k] += sig_src_arr[i] * cos(2 * PI * k * i / sig_lenght);
            sig_dest_imx_arr[k] -= sig_src_arr[i] * sin(2 * PI * k * i / sig_lenght);
        }
    }
}


/*
    DFT output signal's Magnitude
    Identifying the frequencies present in the DFT plot
*/
void get_dft_output_mag(double* sig_dest_mag_arr){
    int k;
    for(k = 0; k < SIG_LENGHT/2; k++){
        sig_dest_mag_arr[k] = sqrt(pow(Output_ReX[k],2)+ pow(Output_ImX[k],2));

    }
}



/*Inverse Discrete Fourier Transform*/
void sig_calc_idft(double* idft_out_arr, double* sig_src_rex_arr, double* sig_src_imx_arr, size_t idft_lenght) {
   int i, k;

    for(i = 0; i < idft_lenght ; i++ )
        idft_out_arr[i] = 0;            //initial zero idf_out_arr


    for(k = 0; k < (idft_lenght/2); k++){
        sig_src_rex_arr[k] =  sig_src_rex_arr[k] / (idft_lenght/2);
        sig_src_imx_arr[k] = -sig_src_imx_arr[k] / (idft_lenght/2);
    }
    sig_src_rex_arr[0] =  sig_src_rex_arr[0]/2;
    sig_src_imx_arr[0] = -(sig_src_imx_arr[0]/2);


    for(k = 0; k < (idft_lenght/2) ; k++){
        for(i = 0; i < idft_lenght; i++){
            idft_out_arr[i] += sig_src_rex_arr[k] * cos(2 * PI * k * i/ idft_lenght);
            idft_out_arr[i] += sig_src_imx_arr[k] * sin(2 * PI * k * i/ idft_lenght);
        }
    }
}
