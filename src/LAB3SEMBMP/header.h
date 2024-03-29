

#ifndef LAB3SEMBMP_HEADER_H
#define LAB3SEMBMP_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct {
    unsigned char type[2];
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
} BMPHeader;

typedef struct {
    unsigned int size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    int xPixelsPerMeter;
    int yPixelsPerMeter;
    unsigned int colorsUsed;
    unsigned int importantColors;
} BMPInfoHeader;

void IsBmp(BMPHeader header);
void Is24Pixel(BMPInfoHeader infoHeader);
void BmpToNegative( unsigned char* imageData, int imageSize);
void WriteInBMP(BMPHeader header,  BMPInfoHeader infoHeader, FILE* BMP, const unsigned char* imageData, int imageSize);
void BmpToGrayBlack(unsigned char* imageData, int imageSize);
void menu(const unsigned char* imageData,int imageSize, FILE* BMP, BMPInfoHeader infoHeader, BMPHeader header);
void menu(unsigned char* imageData,int imageSize, FILE* BMP, BMPInfoHeader infoHeader, BMPHeader header);
void gammaParam(double* gamma, char* string, double low, double high);
void validationParam(char* string, int* param, int low, int high);
<<<<<<< HEAD
void medianFilter(unsigned char *imageData, BMPInfoHeader *infoHeader);
void cycles(int x, int y, BMPInfoHeader* infoHeader, unsigned char* imageData, const unsigned char* buffer);
=======
void medianFilter(unsigned char *imageData, const BMPInfoHeader *infoHeader);
void cycles(int x, int y, const BMPInfoHeader* infoHeader, unsigned char* imageData, const unsigned char* buffer);
>>>>>>> 255a3d4bf78f4eb1b128ad652f86268c03dd5986
#endif //LAB3SEMBMP_HEADER_H

