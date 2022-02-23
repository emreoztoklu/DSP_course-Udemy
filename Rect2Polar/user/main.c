#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*DEFINES */
#define SIZE_LENGHT  320
#define PI		     3.141592653589

/*data types*/
extern double _320_pts_ecg_REX[SIZE_LENGHT];
extern double _320_pts_ecg_IMX[SIZE_LENGHT];

double *rex_ptr = (double*) &_320_pts_ecg_REX;
double *imx_ptr = (double*) &_320_pts_ecg_IMX;

double Output_magnitude[SIZE_LENGHT];
double Output_phase[SIZE_LENGHT];


/*function prototypes*/
void rect_to_polar_conversion(double* sig_src_rex_arr, double* sig_src_imx_arr, double* sig_out_mag_arr, double* sig_out_phase_arr, size_t sig_lenght);


int main(){

    FILE *input_rex_fptr, *input_imx_fptr, *output_mag_fptr, *output_ph_fptr;

    rect_to_polar_conversion((double*) rex_ptr,
                             (double*) imx_ptr,
                             (double*) Output_magnitude,
                             (double*) Output_phase,
                             (size_t ) SIZE_LENGHT);

    input_rex_fptr  = fopen(".\\data\\input_rex.dat", "w");
    input_imx_fptr  = fopen(".\\data\\input_imx.dat", "w");
    output_mag_fptr = fopen(".\\data\\output_mag.dat","w");
    output_ph_fptr  = fopen(".\\data\\output_ph.dat", "w");


    for(int i = 0; i < SIZE_LENGHT; i++){
        fprintf(input_rex_fptr,"\n%f", rex_ptr[i]);
        fprintf(input_imx_fptr,"\n%f", imx_ptr[i]);
        fprintf(output_mag_fptr,"\n%f", Output_magnitude[i]);
        fprintf(output_ph_fptr,"\n%f",  Output_phase[i]);
    }

    fclose(input_rex_fptr);
    fclose(input_imx_fptr);
    fclose(output_mag_fptr);
    fclose(output_ph_fptr);

    return 0;
}


void rect_to_polar_conversion(double* sig_src_rex_arr, double * sig_src_imx_arr, double* sig_out_mag_arr, double* sig_out_phase_arr, size_t sig_lenght){
    int k;
    for (k = 0; k < sig_lenght ; k++){

        sig_out_mag_arr[k] = sqrt(powf(sig_src_rex_arr[k], 2) + powf(sig_src_imx_arr[k], 2));

        /*Special case 1: if real value calculation is zero then */
        if(sig_src_rex_arr[k] == 0){
            sig_src_rex_arr[k] = pow(10, -20);
            sig_out_phase_arr[k] = atan(sig_src_imx_arr[k]/sig_src_rex_arr[k]);
        }

        /*Special case 2: both values under 0 then phase - PI*/
        if((sig_src_rex_arr[k] < 0) && (sig_src_imx_arr[k] < 0)){
            sig_out_phase_arr[k] = sig_out_phase_arr[k] - PI;
        }

        /*Special case 3: Imx values over 0 then phase + PI*/
        if((sig_src_rex_arr[k] < 0) && (sig_src_imx_arr[k] >= 0)){
            sig_out_phase_arr[k] = sig_out_phase_arr[k] + PI;
        }
    }
}
