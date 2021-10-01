#include "seamcarving.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void calc_energy(struct rgb_img *im, struct rgb_img **grad)
{
    create_img(grad, im->height, im->width); 

    int rx_plus, gx_plus, bx_plus, rx_minus, gx_minus, bx_minus;
    int ry_plus, gy_plus, by_plus, ry_minus, gy_minus, by_minus;
    int rx_diff, gx_diff, bx_diff, ry_diff, gy_diff, by_diff;

    size_t height = im->height;
    size_t width = im->width;
    double pixel_energy;

    
    (*grad)->height = height;
    (*grad)->width = width;


    for (int y = 1; y < height - 1; y++)
    {
        for (int x = 1; x < width - 1; x++)
        {

            //(y, x + 1)
            rx_plus = (int)get_pixel(im, y, x + 1, 0);
            gx_plus = (int)get_pixel(im, y, x + 1, 1);
            bx_plus = (int)get_pixel(im, y, x + 1, 2);

            //(y, x - 1)
            rx_minus = (int)get_pixel(im, y, x - 1, 0);
            gx_minus = (int)get_pixel(im, y, x - 1, 1);
            bx_minus = (int)get_pixel(im, y, x - 1, 2);

            //(y + 1, x)
            ry_plus = (int)get_pixel(im, y + 1, x, 0);
            gy_plus = (int)get_pixel(im, y + 1, x, 1);
            by_plus = (int)get_pixel(im, y + 1, x, 2);

            //(y - 1, x)
            ry_minus = (int)get_pixel(im, y - 1, x, 0);
            gy_minus = (int)get_pixel(im, y - 1, x, 1);
            by_minus = (int)get_pixel(im, y - 1, x, 2);

            //calculate rgb differences
            rx_diff = rx_plus - rx_minus;
            gx_diff = gx_plus - gx_minus;
            bx_diff = bx_plus - bx_minus;

            ry_diff = ry_plus - ry_minus;
            gy_diff = gy_plus - gy_minus;
            by_diff = by_plus - by_minus;

            //calculate energy for a pixel
            pixel_energy = sqrt(rx_diff * rx_diff + gx_diff * gx_diff + bx_diff * bx_diff + ry_diff * ry_diff + gy_diff * gy_diff + by_diff * by_diff);

            //set raster value of struct *grad
            uint8_t energy = (uint8_t)(pixel_energy / 10);
            set_pixel(*grad, y, x, energy, energy, energy);
        }
    }

    //edge cases: x = 0
    for (int y = 1; y < height - 1; y++)
    {
        //(y, x + 1)
        rx_plus = (int)get_pixel(im, y, 1, 0);
        gx_plus = (int)get_pixel(im, y, 1, 1);
        bx_plus = (int)get_pixel(im, y, 1, 2);

        //(y, x - 1)
        rx_minus = (int)get_pixel(im, y, width - 1, 0);
        gx_minus = (int)get_pixel(im, y, width - 1, 1);
        bx_minus = (int)get_pixel(im, y, width - 1, 2);

        //(y + 1, x)
        ry_plus = (int)get_pixel(im, y + 1, 0, 0);
        gy_plus = (int)get_pixel(im, y + 1, 0, 1);
        by_plus = (int)get_pixel(im, y + 1, 0, 2);

        //(y - 1, x)
        ry_minus = (int)get_pixel(im, y - 1, 0, 0);
        gy_minus = (int)get_pixel(im, y - 1, 0, 1);
        by_minus = (int)get_pixel(im, y - 1, 0, 2);

        //calculate rgb differences
        rx_diff = rx_plus - rx_minus;
        gx_diff = gx_plus - gx_minus;
        bx_diff = bx_plus - bx_minus;

        ry_diff = ry_plus - ry_minus;
        gy_diff = gy_plus - gy_minus;
        by_diff = by_plus - by_minus;

        //calculate energy for a pixel
        pixel_energy = sqrt(rx_diff * rx_diff + gx_diff * gx_diff + bx_diff * bx_diff + ry_diff * ry_diff + gy_diff * gy_diff + by_diff * by_diff);

        //set raster value of struct *grad
        uint8_t energy = (uint8_t)(pixel_energy / 10);
        set_pixel(*grad, y, 0, energy, energy, energy);
    }

    //x = width - 1
    for (int y = 1; y < height - 1; y++)
    {
        //(y, x + 1)
        rx_plus = (int)get_pixel(im, y, 0, 0);
        gx_plus = (int)get_pixel(im, y, 0, 1);
        bx_plus = (int)get_pixel(im, y, 0, 2);

        //(y, x - 1)
        rx_minus = (int)get_pixel(im, y, width - 2, 0);
        gx_minus = (int)get_pixel(im, y, width - 2, 1);
        bx_minus = (int)get_pixel(im, y, width - 2, 2);

        //(y + 1, x)
        ry_plus = (int)get_pixel(im, y + 1, width - 1, 0);
        gy_plus = (int)get_pixel(im, y + 1, width - 1, 1);
        by_plus = (int)get_pixel(im, y + 1, width - 1, 2);

        //(y - 1, x)
        ry_minus = (int)get_pixel(im, y - 1, width - 1, 0);
        gy_minus = (int)get_pixel(im, y - 1, width - 1, 1);
        by_minus = (int)get_pixel(im, y - 1, width - 1, 2);

        //calculate rgb differences
        rx_diff = rx_plus - rx_minus;
        gx_diff = gx_plus - gx_minus;
        bx_diff = bx_plus - bx_minus;

        ry_diff = ry_plus - ry_minus;
        gy_diff = gy_plus - gy_minus;
        by_diff = by_plus - by_minus;

        //calculate energy for a pixel
        pixel_energy = sqrt(rx_diff * rx_diff + gx_diff * gx_diff + bx_diff * bx_diff + ry_diff * ry_diff + gy_diff * gy_diff + by_diff * by_diff);

        //set raster value of struct *grad
        uint8_t energy = (uint8_t)(pixel_energy / 10);
        set_pixel(*grad, y, width - 1, energy, energy, energy);
    }

    //y = 0
    for (int x = 1; x < width - 1; x++)
    {
        //(y, x + 1)
        rx_plus = (int)get_pixel(im, 0, x + 1, 0);
        gx_plus = (int)get_pixel(im, 0, x + 1, 1);
        bx_plus = (int)get_pixel(im, 0, x + 1, 2);

        //(y, x - 1)
        rx_minus = (int)get_pixel(im, 0, x - 1, 0);
        gx_minus = (int)get_pixel(im, 0, x - 1, 1);
        bx_minus = (int)get_pixel(im, 0, x - 1, 2);

        //(y + 1, x)
        ry_plus = (int)get_pixel(im, 1, x, 0);
        gy_plus = (int)get_pixel(im, 1, x, 1);
        by_plus = (int)get_pixel(im, 1, x, 2);

        //(y - 1, x)
        ry_minus = (int)get_pixel(im, height - 1, x, 0);
        gy_minus = (int)get_pixel(im, height - 1, x, 1);
        by_minus = (int)get_pixel(im, height - 1, x, 2);

        //calculate rgb differences
        rx_diff = rx_plus - rx_minus;
        gx_diff = gx_plus - gx_minus;
        bx_diff = bx_plus - bx_minus;

        ry_diff = ry_plus - ry_minus;
        gy_diff = gy_plus - gy_minus;
        by_diff = by_plus - by_minus;

        //calculate energy for a pixel
        pixel_energy = sqrt(rx_diff * rx_diff + gx_diff * gx_diff + bx_diff * bx_diff + ry_diff * ry_diff + gy_diff * gy_diff + by_diff * by_diff);

        //set raster value of struct *grad
        uint8_t energy = (uint8_t)(pixel_energy / 10);
        set_pixel(*grad, 0, x, energy, energy, energy);
    }

    //y = height - 1
    for (int x = 1; x < width - 1; x++)
    {
        //(y, x + 1)
        rx_plus = (int)get_pixel(im, height - 1, x + 1, 0);
        gx_plus = (int)get_pixel(im, height - 1, x + 1, 1);
        bx_plus = (int)get_pixel(im, height - 1, x + 1, 2);

        //(y, x - 1)
        rx_minus = (int)get_pixel(im, height - 1, x - 1, 0);
        gx_minus = (int)get_pixel(im, height - 1, x - 1, 1);
        bx_minus = (int)get_pixel(im, height - 1, x - 1, 2);

        //(y + 1, x)
        ry_plus = (int)get_pixel(im, 0, x, 0);
        gy_plus = (int)get_pixel(im, 0, x, 1);
        by_plus = (int)get_pixel(im, 0, x, 2);

        //(y - 1, x)
        ry_minus = (int)get_pixel(im, height - 2, x, 0);
        gy_minus = (int)get_pixel(im, height - 2, x, 1);
        by_minus = (int)get_pixel(im, height - 2, x, 2);

        //calculate rgb differences
        rx_diff = rx_plus - rx_minus;
        gx_diff = gx_plus - gx_minus;
        bx_diff = bx_plus - bx_minus;

        ry_diff = ry_plus - ry_minus;
        gy_diff = gy_plus - gy_minus;
        by_diff = by_plus - by_minus;

        //calculate energy for a pixel
        pixel_energy = sqrt(rx_diff * rx_diff + gx_diff * gx_diff + bx_diff * bx_diff + ry_diff * ry_diff + gy_diff * gy_diff + by_diff * by_diff);

        //set raster value of struct *grad
        uint8_t energy = (uint8_t)(pixel_energy / 10);
        set_pixel(*grad, height - 1, x, energy, energy, energy);
    }

    //Corner (0,0)
    //(y, x + 1)
    rx_plus = (int)get_pixel(im, 0, 1, 0);
    gx_plus = (int)get_pixel(im, 0, 1, 1);
    bx_plus = (int)get_pixel(im, 0, 1, 2);

    //(y, x - 1)
    rx_minus = (int)get_pixel(im, 0, width - 1, 0);
    gx_minus = (int)get_pixel(im, 0, width - 1, 1);
    bx_minus = (int)get_pixel(im, 0, width - 1, 2);

    //(y + 1, x)
    ry_plus = (int)get_pixel(im, 1, 0, 0);
    gy_plus = (int)get_pixel(im, 1, 0, 1);
    by_plus = (int)get_pixel(im, 1, 0, 2);

    //(y - 1, x)
    ry_minus = (int)get_pixel(im, height - 1, 0, 0);
    gy_minus = (int)get_pixel(im, height - 1, 0, 1);
    by_minus = (int)get_pixel(im, height - 1, 0, 2);

    //calculate rgb differences
    rx_diff = rx_plus - rx_minus;
    gx_diff = gx_plus - gx_minus;
    bx_diff = bx_plus - bx_minus;

    ry_diff = ry_plus - ry_minus;
    gy_diff = gy_plus - gy_minus;
    by_diff = by_plus - by_minus;

    //calculate energy for a pixel
    pixel_energy = sqrt(rx_diff * rx_diff + gx_diff * gx_diff + bx_diff * bx_diff + ry_diff * ry_diff + gy_diff * gy_diff + by_diff * by_diff);

    //set raster value of struct *grad
    uint8_t energy = (uint8_t)(pixel_energy / 10);
    set_pixel(*grad, 0, 0, energy, energy, energy);

    //Corner (0, width-1)
    //(y, x + 1)
    rx_plus = (int)get_pixel(im, 0, 0, 0);
    gx_plus = (int)get_pixel(im, 0, 0, 1);
    bx_plus = (int)get_pixel(im, 0, 0, 2);

    //(y, x - 1)
    rx_minus = (int)get_pixel(im, 0, width - 2, 0);
    gx_minus = (int)get_pixel(im, 0, width - 2, 1);
    bx_minus = (int)get_pixel(im, 0, width - 2, 2);

    //(y + 1, x)
    ry_plus = (int)get_pixel(im, 1, width - 1, 0);
    gy_plus = (int)get_pixel(im, 1, width - 1, 1);
    by_plus = (int)get_pixel(im, 1, width - 1, 2);

    //(y - 1, x)
    ry_minus = (int)get_pixel(im, height - 1, width - 1, 0);
    gy_minus = (int)get_pixel(im, height - 1, width - 1, 1);
    by_minus = (int)get_pixel(im, height - 1, width - 1, 2);

    //calculate rgb differences
    rx_diff = rx_plus - rx_minus;
    gx_diff = gx_plus - gx_minus;
    bx_diff = bx_plus - bx_minus;

    ry_diff = ry_plus - ry_minus;
    gy_diff = gy_plus - gy_minus;
    by_diff = by_plus - by_minus;

    //calculate energy for a pixel
    pixel_energy = sqrt(rx_diff * rx_diff + gx_diff * gx_diff + bx_diff * bx_diff + ry_diff * ry_diff + gy_diff * gy_diff + by_diff * by_diff);

    //set raster value of struct *grad
    energy = (uint8_t)(pixel_energy / 10);
    set_pixel(*grad, 0, width - 1, energy, energy, energy);

    //corner (height - 1, 0)
    //(y, x + 1)
    rx_plus = (int)get_pixel(im, height - 1, 1, 0);
    gx_plus = (int)get_pixel(im, height - 1, 1, 1);
    bx_plus = (int)get_pixel(im, height - 1, 1, 2);

    //(y, x - 1)
    rx_minus = (int)get_pixel(im, height - 1, width - 1, 0);
    gx_minus = (int)get_pixel(im, height - 1, width - 1, 1);
    bx_minus = (int)get_pixel(im, height - 1, width - 1, 2);

    //(y + 1, x)
    ry_plus = (int)get_pixel(im, 0, 0, 0);
    gy_plus = (int)get_pixel(im, 0, 0, 1);
    by_plus = (int)get_pixel(im, 0, 0, 2);

    //(y - 1, x)
    ry_minus = (int)get_pixel(im, height - 2, 0, 0);
    gy_minus = (int)get_pixel(im, height - 2, 0, 1);
    by_minus = (int)get_pixel(im, height - 2, 0, 2);

    //calculate rgb differences
    rx_diff = rx_plus - rx_minus;
    gx_diff = gx_plus - gx_minus;
    bx_diff = bx_plus - bx_minus;

    ry_diff = ry_plus - ry_minus;
    gy_diff = gy_plus - gy_minus;
    by_diff = by_plus - by_minus;

    //calculate energy for a pixel
    pixel_energy = sqrt(rx_diff * rx_diff + gx_diff * gx_diff + bx_diff * bx_diff + ry_diff * ry_diff + gy_diff * gy_diff + by_diff * by_diff);

    //set raster value of struct *grad
    energy = (uint8_t)(pixel_energy / 10);
    set_pixel(*grad, height - 1, 0, energy, energy, energy);

    //corner (height - 1, width - 1)
    //(y, x + 1)
    rx_plus = (int)get_pixel(im, height - 1, 0, 0);
    gx_plus = (int)get_pixel(im, height - 1, 0, 1);
    bx_plus = (int)get_pixel(im, height - 1, 0, 2);

    //(y, x - 1)
    rx_minus = (int)get_pixel(im, height - 1, width - 2, 0);
    gx_minus = (int)get_pixel(im, height - 1, width - 2, 1);
    bx_minus = (int)get_pixel(im, height - 1, width - 2, 2);

    //(y + 1, x)
    ry_plus = (int)get_pixel(im, 0, width - 1, 0);
    gy_plus = (int)get_pixel(im, 0, width - 1, 1);
    by_plus = (int)get_pixel(im, 0, width - 1, 2);

    //(y - 1, x)
    ry_minus = (int)get_pixel(im, height - 2, width - 1, 0);
    gy_minus = (int)get_pixel(im, height - 2, width - 1, 1);
    by_minus = (int)get_pixel(im, height - 2, width - 1, 2);

    //calculate rgb differences
    rx_diff = rx_plus - rx_minus;
    gx_diff = gx_plus - gx_minus;
    bx_diff = bx_plus - bx_minus;

    ry_diff = ry_plus - ry_minus;
    gy_diff = gy_plus - gy_minus;
    by_diff = by_plus - by_minus;

    //calculate energy for a pixel
    pixel_energy = sqrt(rx_diff * rx_diff + gx_diff * gx_diff + bx_diff * bx_diff + ry_diff * ry_diff + gy_diff * gy_diff + by_diff * by_diff);

    //set raster value of struct *grad
    energy = (uint8_t)(pixel_energy / 10);
    set_pixel(*grad, height - 1, width - 1, energy, energy, energy);
}


double min2(double input1, double input2)
{
    if(input1 > input2){
        return input2;
    }
    return input1;
}

double min3(double inp1, double inp2, double inp3)
{
    if((inp1 <= inp2) && (inp1 <= inp3)){
        return inp1;
    }
    else if((inp2 <= inp1) && (inp2 <= inp3)){
        return inp2;
    }
    return inp3;
}



// void dynamic_seam1(struct rgb_img *grad, double **best_arr)
// {
    // for(int i = 0; i < ((grad->width) * (grad->height)); i++){
    //     printf("%f ", (double)(grad->raster)[i*3]);
    // }
//     int width = grad->width;
//     int height = grad->height;
//     *best_arr = (double *)malloc((sizeof(double)) * width * height);
//     for(int i = 0; i < width; i++){
//         best_arr[i] = ((grad->raster)[i]);
//         printf("%d ", best_arr[i]);
//     }
//     for(int k = 1; k < height; k++){
//         (*best_arr)[k * (width)] = (grad->raster)[k * (width)] + 
//         min2((*best_arr)[(k-1) * width], (*best_arr)[((k-1) * width) + 1]);
        
//         (*best_arr)[((k+1) * width) - 1] = (grad->raster)[((k+1) * width) - 1] 
//         + min2((*best_arr)[(k * width) - 1], (*best_arr)[(k * width) - 2]);

//         for (int j = 1; j < (width - 1); j++){
//             (*best_arr)[(k * width) + j] = (grad->raster)[(k * width) + j] +
//             min3((*best_arr)[(k * width) + j - width - 1],
//             (*best_arr)[(k * width) + j - width],
//             (*best_arr)[(k * width) + j - width + 1]);
//         }
//     }
// }


void dynamic_seam(struct rgb_img *grad, double **best_arr)
{
    int width = grad->width;
    int height = grad->height;
    *best_arr = (double *)malloc(sizeof(double) * width * height);
    for(int i = 0; i < width; i++){
        (*best_arr)[i] = (double)(grad->raster)[3*i];
        // printf("%f ", (*best_arr)[i]);
    }
    for(int k = 1; k < height; k++){
        (*best_arr)[k * width] = (grad->raster)[k * width * 3] +
        min2((*best_arr)[(k-1) * width], (*best_arr)[((k-1) * (width)) + 1]);
        
        (*best_arr)[((k+1) * width) - 1] = (grad->raster)[((k+1) * width * 3) - 1] +
        min2((*best_arr)[(k * width) - 1], (*best_arr)[(k * width) - 2]);

        for (int j = 1; j < (width - 1); j++){
            (*best_arr)[(k * width) + j] = (grad->raster)[(k * width * 3) + (j * 3)] +
            min3((*best_arr)[(k * width) + j - width - 1], (*best_arr)[(k * width) + j - width],
            (*best_arr)[(k * width) + j - width + 1]);
        }
    }
    // // uncomment to see table of min values
    // for(int p = 0; p < height; p++){
    //     for(int q = 0; q < width; q++){
    //         printf("%f ", (*best_arr)[(p * width) + q]);
    //     }
    //     printf("\n");
    // }
}



void recover_path(double *best, int height, int width, int **path)
{
    *path = (int *)malloc(sizeof(int) * height);
    double min_val = best[(height * width) - width];
    int min_index = 0;
    for(int j = 1; j < width; j++){
        if(best[(height * width) - width + j] < min_val){
            min_val = best[(height * width) - width + j];
            min_index = j;
        }
    }
    (*path)[height-1] = min_index;

    for(int i = (height-1); i > 0; i--){
        if((*path)[i] == 0){
            if(best[(i * width) - width] < best[(i * width) - width + 1]){
                (*path)[i-1] = 0;
            }
            else{
                (*path)[i-1] = 1;
            }
        }
        else if((*path)[i] == (width - 1)){
            if(best[(i * width) - 1] < best[(i * width) - 2]){
                (*path)[i-1] = width - 1;
            }
            else{
                (*path)[i-1] = width - 2;
            }
        }
        else{
            int holder = (*path)[i];
            if((best[((i-1) * width) + holder - 1] <= best[((i-1) * width) + holder]) && 
            (best[((i-1) * width) + holder - 1] <= best[((i-1) * width) + holder + 1])){
                (*path)[i-1] = holder - 1;
            }
            else if((best[((i-1) * width) + holder] <= best[((i-1) * width) + holder - 1]) && 
            (best[((i-1) * width) + holder] <= best[((i-1) * width) + holder + 1])){
                (*path)[i-1] = holder;
            }
            else{
                (*path)[i-1] = holder + 1;
            }
        }
    }
    // uncomment to see the path of least energy
    // for(int t = 0; t < height; t++){
    // printf("%d ", (*path)[t]);
    // }
}



void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path)
{
    //Create dest struct 
    size_t dest_height = src->height;
    size_t dest_width = src->width - 1;
    create_img(dest, dest_height, dest_width);

    uint8_t r, g, b;

    for (int y = 0; y < src->height; y++)
    {
        for (int x = 0; x < src->width; x++)
        {
            //skipping element in path 
            if ((src->width)*y + x == (src->width)*y + path[y]){
                //k = x+1 to skip pixel (y, x)
                for (int k = x + 1; k < src->width; k++){
                    r = get_pixel(src, y, k, 0);
                    g = get_pixel(src, y, k, 1);
                    b = get_pixel(src, y, k, 2);

                    //copy rgb info to dest at pixel x 
                    set_pixel(*dest, y, x, r, g, b); 

                    //increment x along with k
                    x++; 
                }
                //break out of loop because row of pixels is finished
                break; 
            }

            //read in rgb info from src
            r = get_pixel(src, y, x, 0);
            g = get_pixel(src, y, x, 1);
            b = get_pixel(src, y, x, 2);

            //copy rgb info to dest
            set_pixel(*dest, y, x, r, g, b); 
        }
    }
}



