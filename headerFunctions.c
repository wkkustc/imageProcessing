/*
File: headerFunctions.c
Author: Daniel Gonzalez
Date: 11/13/09
Descr: gets a full name
make -f make_test.mk 
*/


#include    <stdio.h>
#include    <stdlib.h>
#include    "headerFunctions.h"


bmp_image test;

//professa! code
byte **alloc_2d_array(int width, int height)
{
    int i;
    byte **a = (byte **)malloc(width*sizeof(byte *));

    for(i = 0;i<width;i++)
        a[i] = (byte *)malloc(height * sizeof(byte *));
    return a;
}
//end more info on code is at the bottom 


/*
My bug was that I defined my 2d arrays of colors as "char" rather than as "unsigned char". The unsigned char data type will store integers in unsigned format and the char values will be in the range 0-255. Exactly what I need. So, here's how I fixed this in my code.

typedef unsigned char byte;

typedef struct {
int width;
int height;
byte **blue;
byte **green;
byte **red;
} bmp_image;

byte **alloc_2d_array(int rows, int cols) {
int i;
byte **a = (byte **)malloc(rows * sizeof(byte *));
for (i = 0; i < rows; i++) a[i] = (byte *)malloc(cols * sizeof(byte));
return a;
}
*/
