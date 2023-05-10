
#ifndef LAB3SEMBMP_HEADER_H
#define LAB3SEMBMP_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
void WriteInBMP(BMPHeader header,  BMPInfoHeader infoHeader, FILE* BMP, unsigned char* imageData, int imageSize);
void BmpToGrayBlack(unsigned char* imageData, int imageSize);
void menu(unsigned char* imageData,int imageSize, FILE* BMP, BMPInfoHeader infoHeader, BMPHeader header);
void gammaCorrection(unsigned char* imageData, int imageSize, double gamma);
void gammaParam(double* gamma, char* string, double low, double high);
void validationParam(char* string, int* param, int low, int high);
void medianFilter(unsigned char *imageData, BMPInfoHeader *infoHeader);
void cycles(int x, int y, BMPInfoHeader* infoHeader, unsigned char* imageData, const unsigned char* buffer);
#endif //LAB3SEMBMP_HEADER_H
