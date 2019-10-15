# Makefile for hw4, EECS22 Fall 2017 fall 
# Author: Huan Chen
# Modified by: Mihnea Chirila
# Modification: Ali Nickparsa 11/11/2018
# Date:   11/01/2017
CC     = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -Wall

OBJS = MovieLab.o MovieIO.o Movie.o IterativeFilter.o DIPs.o FileIO.o Image.o ImageList.o 
DEPS = Image.h FileIO.h DIPs.h 

DESIGN = MovieLab 
all: $(DESIGN)
MovieLab: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -lm -o MovieLab


MovieLab.o: MovieLab.c
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o
FileIO.o: FileIO.c FileIO.h Image.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o
DIPs.o: DIPs.c DIPs.h Image.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o
Image.o: Image.c Image.h
	$(CC) $(CFLAGS) Image.c -o Image.o
ImageList.o: ImageList.c ImageList.h
	$(CC) $(CFLAGS) ImageList.c -o ImageList.o
Movie.o: Movie.c Movie.h
	$(CC) $(CFLAGS) Movie.c -o Movie.o
MovieIO.o: MovieIO.c MovieIO.h
	$(CC) $(CFLAGS) MovieIO.c -o MovieIO.o
IterativeFilter.o: IterativeFilter.c IterativeFilter.h
	$(CC) $(CFLAGS) IterativeFilter.c -o IterativeFilter.o
clean:
	rm -f *.o *.a $(DESIGN) `find . -name '*.yuv' ! -name 'mouse.yuv' ! -name 'hue.yuv' ! -name 'reverse.yuv'`
