/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
	MOVIE *NewMovie;
	NewMovie = (MOVIE *)malloc(sizeof(MOVIE));
	ILIST *NewList = CreateImageList();
	if(!NewMovie)	
	{
		return NULL;
	}/*if*/
	NewMovie->Frames = NewList;
	return NewMovie; 
}/*end of create movie*/

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	assert(movie);
	DeleteImageList(movie->Frames);
	free(movie);
}/*End of DeleteMovie*/

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
	int Y, U, V, C, D, E, R, G ,B;
	assert(movie);
	
	IENTRY *image = movie->Frames->First;

	int Width = image->YUVImage->W;
	int Height = image->YUVImage->H;

	while(image != NULL)
	{
		IMAGE *NewRGB = CreateImage(Width, Height);
		image->RGBImage = NewRGB;

		for(int x = 0; x < Width; x++)
		{
			for(int y = 0; y < Height; y++)
			{
				Y = GetPixelY(image->YUVImage, x, y);
				U = GetPixelU(image->YUVImage, x, y);	
				V = GetPixelV(image->YUVImage, x, y);
	
				C = Y - 16;
				D = U - 128;
				E = V - 128;
	
				R = clip((( 289 * C + 409 * E + 128) >> 8));
				G = clip((( 289 * C - 100 * D - 208 * E + 128) >> 8));
				B = clip((( 289 * C + 516 * D + 128) >> 8));
			
				SetPixelR(NewRGB, x, y, R);
				SetPixelG(NewRGB, x, y, G);
				SetPixelB(NewRGB, x, y, B);
			}/*for y*/
		}/*for x*/
		image = image->Next;
	}/*while*/
	free(image);
}/*end of YUV2RGBMovie*/

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
	int Y, U, V, R, G, B;
	assert(movie);
	
	IENTRY *image = movie->Frames->First;
	int Width = image->RGBImage->W;
	int Height = image->RGBImage->H;
	
	while(image != NULL)
	{
		image->YUVImage = CreateYUVImage(Width, Height);
		for(int x = 0; x < Width; x++)
		{
			for(int y = 0; y < Height; y++)
			{
				R = GetPixelR(image->RGBImage, x, y);	
				G = GetPixelG(image->RGBImage, x, y);
				B = GetPixelB(image->RGBImage, x, y);

				Y = clip((( 66 * R + 129 * G + 25 * B + 128) >> 8) + 16);
				U = clip(((-38 * R - 74 * G + 112 * B + 128) >> 8) + 128);
				V = clip(((112 * R - 94 * G - 18 * B + 128) >> 8) + 128);
	
				SetPixelY(image->YUVImage, x, y, Y);
				SetPixelU(image->YUVImage, x, y, U);
				SetPixelV(image->YUVImage, x, y, V);
			}/*for yi*/
		}/*for x*/
		DeleteImage(image->RGBImage);
		image->RGBImage = NULL;
		image = image->Next;
	}/*while*/
}/*end of RGB2YUV*/


int MovieLength(const MOVIE *movie)
{
	return movie->Frames->length;	
}/*end of MovieLength*/

int MovieHeight(const MOVIE *movie)
{
	return ImageHeight(movie->Frames->First->RGBImage);
}/*end of MovieHeight*/

int MovieWidth(const MOVIE *movie)
{
	return ImageWidth(movie->Frames->First->RGBImage);
}/*end of MovieWidth*/

int clip(int x)
{
	if(x < 0)
	{
		x = 0;
	}/*if*/
	if(x > 255)
	{
		x = 255;
	}/*if*/
	else if(x >= 0 && x <= 255)
	{
		x = x;
	}/*elseif*/
	return x;
}/*end of clip*/



/* EOF */
