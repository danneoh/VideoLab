/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* DIPs.c: source file for DIP operations                            */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "DIPs.h"
#include "Constants.h"
#include <math.h>
#include <stdio.h>


void matrix_3_3multiplyVector_3(float vector[3], const float matrix[3][3])
{
    // Memory for result
    float result[3] = {0, 0, 0};

    // Perform multiplication
    result[0] = matrix[0][0]*vector[0] + matrix[0][1]*vector[1] + matrix[0][2]*vector[2];
    result[1] = matrix[1][0]*vector[0] + matrix[1][1]*vector[1] + matrix[1][2]*vector[2];
    result[2] = matrix[2][0]*vector[0] + matrix[2][1]*vector[1] + matrix[2][2]*vector[2];

    // Copy result into other stack's memory
    vector[0] = result[0];
    vector[1] = result[1];
    vector[2] = result[2];
}

#ifdef HUEROTATE_UNITTEST
static void pvec(float vec[3])
{
    printf("%f, %f, %f\n\n", vec[0], vec[1], vec[2]);
}
#endif

IMAGE *HueRotate(IMAGE *image, float angle)
{
	// Matrix to transform normalized
    // RGB color vector from the RGB
    // color space to the YIQ color space
    static const float RGBtoYIQMatrix[3][3] = {{0.299,  0.587,  0.114},
                                               {0.596, -0.274, -0.321},
                                               {0.211, -0.523,  0.311}};

    // Matrix to transform normalized
    // YIQ color vector from the YIQ
    // color space to the RGB color space
    static const float YIQtoRGBMatrix[3][3] = {{1.000,  0.956,  0.621},
                                               {1.000, -0.272, -0.647},
                                               {1.000, -1.107,  1.705}};

    const float cs = cos(angle), ss = sin(angle);

    // Matrix to perform a hue
    // rotation on a normalized
    // YIQ color vector
    const float XYPlaneVectorRotateMatrix[3][3] = {{1.000, 0.000, 0.000},
                                                   {0.000, cs, -ss},
                                                   {0.000, ss, cs}};

    // Image variables
    const unsigned int WIDTH = ImageWidth(image);
    const unsigned int HEIGHT = ImageHeight(image);
    float temp[3];

	for(unsigned int i = 0; i < WIDTH; i++)
    {
        for(unsigned int j = 0; j < HEIGHT; j++)
        {
            // Create a normalized RGB color
            // vector fro the current pixel
            // in the image
            temp[0] = (float)GetPixelR(image, i, j)/255;
            temp[1] = (float)GetPixelG(image, i, j)/255;
            temp[2] = (float)GetPixelB(image, i, j)/255;

            // Transform the RGB vector
            // to a YIQ vector
            matrix_3_3multiplyVector_3(temp, RGBtoYIQMatrix);

            // Perform the DIP
            matrix_3_3multiplyVector_3(temp, XYPlaneVectorRotateMatrix);

            // Transform back to RGB
            matrix_3_3multiplyVector_3(temp, YIQtoRGBMatrix);

            // Denormalize and store back into the image
            temp[0] = temp[0] * 255;
            temp[0] = temp[0] < 0 ? 0 : temp[0];
            temp[0] = temp[0] > 255 ? 255 : temp[0];
            temp[1] = temp[1] * 255;
            temp[1] = temp[1] < 0 ? 0 : temp[1];
            temp[1] = temp[1] > 255 ? 255 : temp[1];
            temp[2] = temp[2] * 255;
            temp[2] = temp[2] < 0 ? 0 : temp[2];
            temp[2] = temp[2] > 255 ? 255 : temp[2];
            SetPixelR(image, i, j, (unsigned char)(temp[0]));
            SetPixelG(image, i, j, (unsigned char)(temp[1]));
            SetPixelB(image, i, j, (unsigned char)(temp[2]));
        }// rof
    }// rof

    return image;
}
/*****************************************************************************************************************/
IMAGE *Saturate(IMAGE *image, float percent)
{
        assert(image);
        float tmpR, tmpG, tmpB;
        float Rt, Gt, Bt;
        int x, y;
        for(x = 0; x < ImageWidth(image); x++)
        {
                for(y = 0; y < ImageHeight(image); y++ )
                {
                        /*Get Greyscale*/
                        Rt = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
                        Gt = Rt;
                        Bt = Rt;

                        /*Find difference from original*/
                        Rt = GetPixelR(image, x, y) - Rt;
                        Gt = GetPixelG(image, x, y) - Gt;
                        Bt = GetPixelB(image, x, y) - Bt;

                        /*Add the difference multiplied by percentage*/
                        tmpR =  (GetPixelR(image, x, y) + (percent * Rt)/100.00);
                        tmpG =  (GetPixelG(image, x, y) + (percent * Gt)/100.00);
                        tmpB =  (GetPixelB(image, x, y) + (percent * Bt)/100.00);

                        if(tmpR < 0)
                        {
                                tmpR = 0;
                        }
                        if(tmpR > 255)
                        {
                                tmpR = 255;
                        }
                        if(tmpG < 0)
                        {
                                tmpG = 0;
                        }
                        if(tmpG > 255)
                        {
                                tmpG = 255;
                        }
                        if(tmpB < 0)
                        {
                                tmpB = 0;
                        }
                        if(tmpB > 255)
                        {
                                tmpB = 255;
                        }
                        SetPixelR(image, x, y, tmpR);
                        SetPixelG(image, x, y, tmpG);
                        SetPixelB(image, x, y, tmpB);

                }
	}
	return image;
}











/* EOF */
