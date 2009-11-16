// ============================================================================
// 
//       Filename:  imageIO.c
// 
//    Description:  This will have all the functions that deals with input and
//                  output of the BMP.
// 
//        Version:  1.0
//        Created:  11/11/2009 01:19:01 AM
//       Revision:  none
//       Compiler:  gcc
// 
//         Author:  Jose V. Trigueros (), j.v.trigueros@gmail.com
//        Company:  
// 
// ============================================================================

 
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    "imageIO.h"
#include    "headerFunctions.h"


// ===  FUNCTION  =============================================================
//         Name:  arrayInit()
//  Description:  This function will set the value of a given array
// ============================================================================
void arrayInit ( unsigned char * header, unsigned char *section, int currentLoc, int numberOfBytesToRead )
{
    int i = 0;
    for(;i < numberOfBytesToRead; i++)
    {
        section[i] = header[currentLoc + i];
    }
}        // -----  end of function arrayInit  -----

// ===  FUNCTION  =============================================================
//         Name:  readImage
//  Description:  Reads the image and detects if it's actually there, it might
//                return an error because it the image is non-existent. Then
//                it returns the file pointer.
// ============================================================================
FILE *readImage(char *filename)
{
    FILE *fp = fopen(filename,"rb");

    // Test to see if the image was read properly
    if ( fp == NULL ) 
    {
        fputs("File was not read properly.\n", stderr);
        exit(1);
    }

    return fp;
}

// ===  FUNCTION  =============================================================
//         Name:  createImageBuffer(FILE*)
//  Description:  This will create an image buffer and return an array with all
//                that data.
// ============================================================================
unsigned char *createImageBuffer(FILE *image)
{
    // Local Vars
    long fileSize;
    unsigned char* imageBuffer;
    size_t check;

    // Obtain the file size
    fseek( image, 0, SEEK_END);
    fileSize = ftell(image);
    rewind(image);
    
    // Create space for header
    imageBuffer = malloc(fileSize);
    check = fread( imageBuffer, sizeof(imageBuffer[0]), fileSize,image);

    // If what we read is not the same size fileSize then something is wrong
    if( (int)check != (int)fileSize)
    {
        fputs("createImageBuffer: The file was not read properly\n", stderr);
        exit(2);
    }

    return imageBuffer;
}

// ===  FUNCTION  =============================================================
//         Name:  readBMP()
//  Description:  Reads the header info of the BMP, which constitutes to the 
//                first 54 bytes of the program. 
//                This returns an array with the header data.
// ============================================================================
unsigned char *readBMPHeader(unsigned char *fileBuffer)
{
    const int SIZEOFHEADER = 54;

    // Create headerBuffer to return
    unsigned char *headerBuffer = malloc(SIZEOFHEADER); 

    int i = 0;
    for(; i < SIZEOFHEADER; i++)
    {
        headerBuffer[i] = fileBuffer[i];
    }

    return headerBuffer;
}        // -----  end of function readBMPHeader  -----


// ===  FUNCTION  =============================================================
//         Name:  extractBMPHeaderInfo
//  Description:  This will extract header information and for now it'll just 
//                print it out, but the plan is that this info should be put
//                into a struct. 11/11/2009 11:54:23 PM
// ============================================================================
void extractBMPHeaderInfo ( unsigned char * headerBuffer, headerInfo *info )
{
    // We use this variable to determine the size of the bits we want to shift
    // by, in this case it is a WORD or 4 bits.
    const int WORD = 4;

    printf("=== Header Info ====\n");
    // This variable will show the location of where we are looking in the array
    int location = 0;
    unsigned char *temp = malloc(WORD);
        

    // Determines correct BMP type
    info->type[0] = headerBuffer[location];
    info->type[1] = headerBuffer[location + 1];
    printf("File type: %c%c\n", headerBuffer[location], headerBuffer[location + 1]);
    location += 2;

    // Displays size of BMP in bytes
    printf("File size: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    arrayInit(headerBuffer,temp,location,WORD);
    info->sizeOf = concatenateBits(temp,WORD);
    printf("File size: %d\n", info->sizeOf);
    location +=4; 

    // Displays application specific data
    printf("Application Specific: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    location +=4;


    // Displays header offset
    printf("Header Offset: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    arrayInit(headerBuffer,temp,location,WORD);
    printf("Header Offset: %d\n", concatenateBits(temp,WORD));
    location +=4;
    
    // Displays byte remaining after this point   
    printf("Bytes Remaining: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    arrayInit(headerBuffer,temp,location,WORD);
    printf("Bytes Remaining: %d\n", concatenateBits(temp,WORD));
    location +=4;

    // Width in pixels
    printf("Width: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    arrayInit(headerBuffer,temp,location,WORD);
    info->width = concatenateBits(temp,WORD);
    printf("Width: %d\n", info->width);
    location +=4;
    
    // Height in pixels
    printf("Height: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    arrayInit(headerBuffer,temp,location,WORD);
    info->height = concatenateBits(temp,WORD);
    printf("Height: %d\n", info->height);
    location +=4;

    // We can ignore the next 12 bytes so we just add 12 to the location.
    //----------------------------------------------------------------------
    //  This is what the 12 bytes contain:
    //  2: Number of color planes being used.
    //  2: The number of bits/pixel.
    //  4: BI_RGB, No compression used
    //  4: The size of the raw BMP data (after this header)
    //----------------------------------------------------------------------
    location += 4*3;

    // Horizontal resolution in pixels/meter
    printf("Width resolution: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    arrayInit(headerBuffer,temp,location,WORD);
    printf("Width resolution: %d\n", concatenateBits(temp,WORD));
    location +=4;
    
    // Vertical resolution in pixels/meter 
    printf("Vertical resolution: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    arrayInit(headerBuffer,temp,location,WORD);
    printf("Vertical resolution: %d\n", concatenateBits(temp,WORD));
    location +=4;

    // We can ignore the next 8 bytes so we just add 8 to the location.
    //----------------------------------------------------------------------
    //  This is what the 8 bytes contain:
    //  4: Number of colors in the palette
    //  4: Means all colors are important
    //----------------------------------------------------------------------
    location += 4*2;

    // Release memory allocated for char* temp
    free(temp);
}        // -----  end of function extractBMPHeaderInfo  -----


// ===  FUNCTION  =============================================================
//         Name:  concatenateBits()
//  Description:  This function will concatenate bits so that we get the actual
//                number that we are working with.
// ============================================================================
unsigned int concatenateBits (unsigned char* bytes, int numberOfBytes)
{
    //TODO: Fix the extra shift.

    //----------------------------------------------------------------------
    //  This below code will just be for testing purposes to see if I can 
    //  actually just display these figures as hex
    //----------------------------------------------------------------------
//    printf("test:%x\n",bytes[numberOfBytes - 4]);          // Test PASSED

    // Create a bit buffer where we will concatenate the bits
    unsigned int bitBuffer = 0x00;

    bitBuffer = bitBuffer | bytes[numberOfBytes - 1];
    bitBuffer = bitBuffer << 8;


    // Concatenate the bits using a for loop
    int i = numberOfBytes - 1;
    for(;0 <= i ; i--)
    {
        bitBuffer = bitBuffer | bytes[i];   
        bitBuffer = bitBuffer << 8;
    }

    // Undo the extra 8bit shift from the for loop
    bitBuffer = bitBuffer >> 8;
    
    return bitBuffer;
}        // -----  end of function concatenateBits  -----


// TODO: Needs to be redefined or thrashed, useless ATM
// ===  FUNCTION  =============================================================
//         Name:  displayBMPHeader
//  Description:  This will display the header information that was gotten by 
//                using readBMPHeader.
// ============================================================================
void displayBMPHeader (unsigned char *headerBuffer, int size )
{
    int i = 0;
    for(; i < size ; i++)
        printf("%d: %c %x\n",i,headerBuffer[i], headerBuffer[i]);
//        printf("File type:%c%c\n",headerBuffer[1],headerBuffer[2]);
}        // -----  end of function displayBMPHeader  -----
