// ============================================================================
// 
//       Filename:  headerFunctions.h
// 
//    Description:  This contains the forward declarations of the 
//                  headerFunctions.c
// 
//        Version:  1.0
//        Created:  11/12/2009 08:38:20 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Jose V. Trigueros (), j.v.trigueros@gmail.com
//        Company:  
// 
// ============================================================================

#ifndef HEADERFUNCTIONS_H
#define HEADERFUNCTIONS_H


//----------------------------------------------------------------------
//  Global Variable Delarations
//----------------------------------------------------------------------
typedef unsigned char byte;


// ===  STRUCT    =============================================================
//         Name:  headerInfo
//  Description:  This contains only the header information we need about the 
//                BMP image we are currently reading.
// ============================================================================
typedef struct
{
    char type[2];       // Stores the first 2 bytes to see if the image is BMP
    int sizeOf;         // Stores the size of the image in bytes (incl header)
    int width;
    int height;
}headerInfo;


// ===  FUNCTION  =============================================================
//         Name:  displayHeaderInfo
//  Description:  Just prints out the header info to check if it aquired the 
//                right data.
// ============================================================================
void displayHeaderInfo (headerInfo *info );

// ===  FUNCTION  =============================================================
//         Name:  readBMPHeader()
//  Description:  Reads the header info of the BMP, which constitutes to the 
//                first 54 bytes of the program. It returns a char buffer with
//                the header bytes.
// ============================================================================
unsigned char *readBMPHeader(unsigned char *fileBuffer);

// ===  FUNCTION  =============================================================
//         Name:  displayBMPHeader
//  Description:  This will display the header information that was gotten by 
//                using readBMPHeader.
// ============================================================================
void displayBMPHeader (unsigned char *headerBuffer, int size );

// ===  FUNCTION  =============================================================
//         Name:  extractBMPHeaderInfo
//  Description:  This will extract header information and for now it'll just 
//                print it out, but the plan is that this info should be put
//                into a struct. 11/11/2009 11:54:23 PM
// ============================================================================
void extractBMPHeaderInfo ( unsigned char * headerBuffer, headerInfo *info);

// ===  FUNCTION  =============================================================
//         Name:  setHeaderDimensions
//  Description:  Change the width and the height after rotating image or doing
//                any other operation.
// ============================================================================
void setHeaderDimensions ( unsigned char * headerBuffer, int newWidth, int newHeight );

// ===  FUNCTION  =============================================================
//         Name:  displayBMPHeaderInfo
//  Description:  This will display header information and will do nothing more
// ============================================================================
void displayBMPHeaderInfo ( unsigned char * headerBuffer);

#endif/*HEADERFUNCTIONS_H */
