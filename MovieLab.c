/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/* Modified by Mihnea Chirila for EECS 22 Fall 2018                  */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include "MovieIO.h"
#include "IterativeFilter.h"


void PrintFunctionOptions()
{

printf("To generate a movie from an input image:\n");
printf("Example: ./MovieLab -i <file.ppm> -o <file.yuv> -start = <startVal> -end = <endVal> -step = <stepVal> -<filter>\n\n");
printf("-i <file.ppm>: import image\n");
printf("-o <file.yuv>: export movie\n");
printf("-start= <startVal>: set start parameter\n");
printf("-end= <endVal>: set end parameter\n");
printf("-step = <stepVal>: set step parameter\n");
printf("-hue: use hue filter\n");

printf("\n\n");

printf("To generate a movie from an input movie:\n");
printf("Example: ./MovieLab -m <file.yuv> -o <file.yuv> -f <frameNum> -s <WxH> -<filter>\n\n");
printf("-m <file.yuv>: import movie\n");
printf("-o <file.yuv>: export movie\n");
printf("-f <frameNum>: number of frames in the movie\n");
printf("-s <WidthxHeight>: size of a movie frame\n");
printf("-<filter>: you can put -reverse or -fast\n\n");
}/*End of PrintFunctionOptions*/

int main(int argc, char *argv[])
{
	int x = 0;
	unsigned int framenum = 0;
	char *rc = NULL;
	char *outrc = NULL;
	char *imageoutrc = NULL;
	int rvs = 0; 
	int fastf = 0; 
	int fac = 0;
	int iflag = 0;
	int mflag = 0;
	float start, end, step = 0.00;		
	unsigned int width, height = 0;
	IMAGE *nimage = NULL;
	iterableFilter filter = NULL;
	MOVIE *movie = NULL;
	MOVIE *nMovie = NULL;
	while(x < argc)
	{	
	 	/*Image 2 Movie*/ 
		if(0 == strcmp(argv[x], "-i"))
		{
			nimage = LoadImage(argv[x+1]);
			assert(nimage);
			if(nimage != NULL)
			{
				iflag = 1;
			}
		}/*fi*/
		
		if(0 == strcmp(argv[x], "-o"))
		{
			imageoutrc = argv[x+1];
		}/*fi*/
	
		if(0 == strcmp(argv[x], "-start="))
		{
			sscanf(argv[x+1], "%f", &start);	
		}/*fi*/
		
		if(0 == strcmp(argv[x], "-end="))
		{
			sscanf(argv[x+1], "%f", &end);
		}/*fi*/
		
		if(0 == strcmp(argv[x], "-step="))
		{
			sscanf(argv[x+1], "%f", &step);	
		}/*fi*/
	
		if(0 == strcmp(argv[x], "-hue"))
		{
			filter = &HueRotate;
		}/*fi*/
		if(0 == strcmp(argv[x], "-sat"))
		{
			filter = &Saturate;
		}
/*********************************************************************/
		/*Movie 2 Movie*/
		if(0 == strcmp(argv[x], "-m"))
		{	
			rc = argv[x+1];
			if(rc != NULL)
			{
				mflag = 1;
			}
		}/*fi*/	
		
		if(0 == strcmp(argv[x], "-o"))
		{
			outrc = argv[x+1];	
		}/*fi*/

		if(0 == strcmp(argv[x], "-f"))
		{
			sscanf(argv[x+1], "%d", &framenum);
		}/*fi*/

		if(0 == strcmp(argv[x], "-s"))
		{
			sscanf(argv[x+1], "%ux%u", &width, &height);	
		}/*fi*/
		
		if(0 == strcmp(argv[x], "-h"))
		{
			PrintFunctionOptions();
			x++;
			continue;
		}/*fi*/	

		if(0 == strcmp(argv[x], "-reverse"))
		{
			rvs = 1;
		}/*fi*/
		
		if(0 == strcmp(argv[x], "-fast"))
		{
			fastf = 1;
		}
		x++;	
	}/*elihw*/
		
		/*image 2 movie*/
		if(iflag == 1)
		{
			nMovie = doIterativeFilter(nimage, filter, start, end, step);
			RGB2YUVMovie(nMovie);
			SaveMovie(imageoutrc, nMovie);
			DeleteImage(nimage);
			DeleteMovie(nMovie);
		}

		/*movie 2 movie */
		if(mflag == 1)
		{
			//MOVIE *movie = NULL;
			movie = LoadMovie(rc, framenum, width, height);
			if(rvs == 1)
			{
				printf("Reverse Option Selected!\n");
				ReverseImageList(movie->Frames);
				printf("Reverse operation is done!\n");
			}	
		
			if(fastf == 1)
			{
				printf("Fast Foward Option Selected!\n");
				printf("How fast would you like to go?\n");
				scanf("%d", &fac);
				FastImageList(movie->Frames, fac);
				printf("Fast operation is done!\n");
			}
			SaveMovie(outrc, movie);
			DeleteMovie(movie);
		}
		
		
		return 0;
}/*End of Main*/

/* EOF */
