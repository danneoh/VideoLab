/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

/* Create a new image entry */
IENTRY *CreateImageEntry(void)
{
	IENTRY *entry = (IENTRY *)malloc(sizeof(IENTRY));
	if(!entry)
	{
		return NULL;
	}/*fi*/
	
	entry->RGBImage = NULL;
	entry->YUVImage = NULL;
	entry->List = NULL;
	entry->Next = NULL;
	entry->Prev = NULL;
	
	return entry;
}/*end of CreateImageEntry*/

/* Delete image entry (and image objects)*/
void DeleteImageEntry(IENTRY *entry)
{
	assert(entry);	
	if(entry->RGBImage != NULL)
	{
	DeleteImage(entry->RGBImage);
	}/*fi*/
	else if(entry->YUVImage != NULL)
	{	
	DeleteYUVImage(entry->YUVImage);
	}/*fi esle*/
	free(entry);		
}/*End of DeleteImageEntry*/

/* Create a new image list */
ILIST *CreateImageList(void)
{
	ILIST *list = (ILIST *)malloc(sizeof(ILIST));
	if(!list)
	{
		return NULL;	
	}/*fi*/
	list->length = 0;
	list->First = NULL;
	list->Last = NULL;	
	
	return list;	
}/*end if CreateImageList*/	

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
	IENTRY *e;
	IENTRY *n;
		
	assert(list);
	e = list->First;
	while(e)
	{
		n = e->Next;
		DeleteImageEntry(e);
		e = n;
	}/*while*/
	free(list);	
}/*end of DeleteImageList*/

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
	IENTRY *e = NULL;
	assert(list);
	assert(RGBimage);	
	e = CreateImageEntry();
	e->RGBImage = RGBimage;

	if(list->Last)
	{
		e->List = list;
		e->Next = NULL;
		e->Prev = list->Last;
		list->Last->Next = e;
		list->Last = e;
	}/*if*/
	else
	{
		e->List = list;
		e->Next = NULL;
		e->Prev = NULL;
		list->First = e;
		list->Last = e;
	}/*else*/
	(list->length)++;
}/*end of AppendRGBImage*/

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
	IENTRY *e = NULL;
        assert(list);
        assert(YUVimage);
	e = CreateImageEntry(); 
        if(list->Last)
        {
                e->List = list;
		e->Next = NULL;
                e->Prev = list->Last;
                list->Last->Next = e;
                list->Last = e;
        }/*if*/
        else
        {
                e->List = list;
		e->Next = NULL;
                e->Prev = NULL;
                list->First = e;
                list->Last = e;
        }/*else*/
	e->YUVImage = YUVimage;	
	(list->length)++;
}/*End of AppendYUVImage*/

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
	unsigned int newFrameNum = 0;
	unsigned int counter = 0;
	IENTRY *curr = NULL; /* current entry in the list */
	IENTRY *prev = NULL; /* previous kept entry in the list */
	IENTRY *next = NULL; /* next entry in the list */

	assert(list);
	assert(factor > 0);

	curr = list->First;

	while (curr != NULL) {
		next = curr->Next;

		if (counter % factor == 0) {
			newFrameNum ++;

			curr->Prev = prev;
			if (prev != NULL) {
				prev->Next = curr;
			}
			prev = curr;
		} else {
			if (curr->RGBImage != NULL) {
				DeleteImage(curr->RGBImage);
			}

			if (curr->YUVImage != NULL) {
				DeleteYUVImage(curr->YUVImage);
			}

			curr->List = NULL;
			curr->Next = NULL;
			curr->Prev = NULL;
			curr->RGBImage = NULL;
			curr->YUVImage = NULL;
			free(curr);
		}

		curr = next;
		counter ++;
	}

	list->Last = prev;
	if (prev != NULL) {
		prev->Next = NULL;
	}
	list->length = newFrameNum;
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
	IENTRY *pcurr = list->First;
	IENTRY *placeholder;
	while(pcurr != NULL)
	{
		placeholder = pcurr->Prev;
		
		pcurr->Prev = pcurr->Next;
		
		pcurr->Next = placeholder;
		
		pcurr = pcurr->Prev;
	}/*while*/

	placeholder = placeholder->Prev;
	list->Last = list->First;
	list->First = placeholder;		
}/*end of ReverseImageList*/























/* EOF */
