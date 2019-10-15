/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2018                     */
/*                                                                   */
/* Author: Jordan Bonecutter                                         */
/*                                                                   */
/* IterativeFilter.c: file for iterative filters                     */
/*                                                                   */
/*********************************************************************/
#include <assert.h>
#include "IterativeFilter.h"
#include "DIPs.h"
#include "Image.h"
MOVIE *doIterativeFilter(IMAGE *image, iterableFilter filter, float start, float end, float change)
{	
	MOVIE *Nmovie = CreateMovie();
	assert(image);
	assert(filter);
	IMAGE *itemp = image;	
	if(start < end)
	{
		while(start < end)
		{
			if(filter == HueRotate)	
			{
				itemp = filter(CopyImage(image), start);
			}
			else if(filter == Saturate)
			{
				itemp = filter(CopyImage(image), start*100);
			}
			start += change;
			AppendRGBImage(Nmovie->Frames, itemp);	
		}/*while*/
	}/*fi*/
	else if(start > end)
	{
		while(start > end)
		{
			if(filter == HueRotate)
			{
				itemp = filter(CopyImage(image), start);
			}
			else if(filter == Saturate)
			{
				itemp = filter(CopyImage(image), start*100);
			}
			start -= change;
			AppendRGBImage(Nmovie->Frames, itemp);
		}/*while*/
	}	
	return Nmovie;
}	
