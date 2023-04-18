

#include "header.h"
int main() {

    char fileName[100];
    printf("enter the name of file: ");
    scanf_s("%s", fileName);
    FILE* BMP = fopen(fileName, "rb");

    if(!(BMP)){
        printf("Error opening file.\n");
        return 0;
    }

    BMPHeader header;
    BMPInfoHeader infoHeader;
    fread(&header.type, sizeof(header.type), 1, BMP);
    fread(&header.size, sizeof(header.size), 1, BMP);
    fread(&header.reserved1, sizeof(header.reserved1), 1, BMP);
    fread(&header.reserved2, sizeof(header.reserved2), 1, BMP);
    fread(&header.offset, sizeof(header.offset), 1, BMP);
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, BMP);

    IsBmp(header);
    Is24Pixel(infoHeader);

    int rowSize = ((infoHeader.width * infoHeader.bitsPerPixel + 31) / 32) * 4;
    int imageSize = rowSize * infoHeader.height;

    unsigned char* imageData = (unsigned char*) malloc(imageSize * sizeof(unsigned char));
    fread(imageData, sizeof(unsigned char), imageSize, BMP);

    menu(imageData, imageSize, BMP, infoHeader, header);

    fclose(BMP);
    free(imageData);

    return 0;
}
