// ============================================================================
// 
//       Filename:  imageManip.h
// 
//    Description:  This will contain the forward declaration of imageManip.c
// 
//        Version:  1.0
//        Created:  11/16/2009 11:24:16 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Jose V. Trigueros (), j.v.trigueros@gmail.com
//        Company:  
// 
// ============================================================================

#ifndef IMAGEMANIP_H 
#define IMAGEMANIP_H


// ===  STRUCT    =============================================================
//         Name:  pixelData
//  Description:  This will hold the RGB data for each pixel is the BMP
// ============================================================================
typedef struct
{
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
}pixelData;


// ===  FUNCTION  =============================================================
//         Name:  createImageMatrix
//  Description:  This will create a matrix of pixelData storing the pixel
//                colour information in each cell.
// ============================================================================
pixelData **createImageMatrix ( unsigned char *imageData, int width, int height);


#endif /* IMAGEMANIP_H  */
