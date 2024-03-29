#include "header.h"


void IsBmp(BMPHeader header) {
    if (header.type[0] != 'B' || header.type[1] != 'M') {
        printf("File is not BMP.\n");
    }
}

void Is24Pixel(BMPInfoHeader infoHeader) {
    if (infoHeader.bitsPerPixel != 24) {
        printf("Image must be 24 bits per pixel.\n");
    }
}

<<<<<<< HEAD

/*
void validationFile(FILE* BMP, char* outFilename, unsigned char* mass) {
    if (!BMP) {
        printf("Failed to create file %s\n", outFilename);
        free(mass);
        return;
    }
}

void allocateMemValid(unsigned const char* medianFilteredBMP) {
    if (!medianFilteredBMP) {
        printf("Memory allocation failed.\n");
        return;
    }
}
*/

=======
>>>>>>> 255a3d4bf78f4eb1b128ad652f86268c03dd5986
void validationParam(char* string, int* param, int low, int high){
    printf("%s", string);
    while(scanf_s("%d", param)!= 1 || getchar()!= '\n' || *param < low || *param > high){
        printf("error, incorrect input of parameter.");
        rewind(stdin);
        printf("%s", string);
        printf("\n1. Convert to negative.\n");
        printf("2. Convert to Black and Gray.\n");
        printf("3. Apply Gamma correction.\n");
        printf("4. Apply median filtering.\n");
        printf("5. Quit.\n");
    }
}

void WriteInBMP(BMPHeader header, BMPInfoHeader infoHeader, FILE* BMP, const unsigned char *imageData, int imageSize) {
    if (BMP == NULL) {
        printf("Error: BMP file pointer is NULL.\n");
        return;
    }

    fwrite(&header.type, sizeof(header.type), 1, BMP);
    fwrite(&header.size, sizeof(header.size), 1, BMP);
    fwrite(&header.reserved1, sizeof(header.reserved1), 1, BMP);
    fwrite(&header.reserved2, sizeof(header.reserved2), 1, BMP);
    fwrite(&header.offset, sizeof(header.offset), 1, BMP);
    fwrite(&infoHeader, sizeof(BMPInfoHeader), 1, BMP);
    fwrite(imageData, sizeof(unsigned char), imageSize, BMP);

}

void BmpToNegative(unsigned char *imageData, int imageSize) {

    for (int i = 0; i < imageSize; i ++) {
        imageData[i] = 255 - imageData[i];
    }
}

void BmpToGrayBlack(unsigned char *imageData, int imageSize) {

    for (int i = 0; i < imageSize; i +=3) {
        unsigned char gray = (unsigned char) ((float) imageData[i] * 0.3 + (float) imageData[i + 1] * 0.5 + (float) imageData[i + 2] * 0.1);
        imageData[i] = gray;
        imageData[i+1] = gray;
        imageData[i+2]= gray;
    }
}

void gammaCorrection(unsigned char* imageData, int imageSize, double gamma){
    for(int i = 0; i < imageSize; i++){
       imageData[i] = (unsigned char)(255 * pow(imageData[i] / 255.0, gamma));
    }
}

void gammaParam(double* gamma, char* string, double low, double high){

    printf("%s", string);
    while(scanf_s("%lf", gamma)!= 1 || *gamma < low || *gamma > high){
        printf("error, incorrect input of parameter.");
        rewind(stdin);
        printf("%s", string);
    }

}

void menu(const unsigned char* imageData,int imageSize, FILE* BMP, BMPInfoHeader infoHeader, BMPHeader header) {

    while (1) {
        double gamma;
        int choice = 0;
        printf("\n1. Convert to negative.\n");
        printf("2. Convert to Black and Gray.\n");
        printf("3. Apply Gamma correction.\n");
        printf("4. Apply median filtering.\n");
        printf("5. Quit.\n");
        validationParam("choose the option:\n", &choice, 1, 5);

        if (choice == 1) {

            unsigned char *negativeImageData = (unsigned char *) malloc(sizeof(unsigned char) * imageSize);
            memcpy(negativeImageData, imageData, sizeof(unsigned char) * imageSize);

            BmpToNegative(negativeImageData, imageSize);

            char outFilename[100] = "negative.bmp";
            fopen_s(&BMP ,outFilename, "wb");

            WriteInBMP(header, infoHeader, BMP, negativeImageData, imageSize);

            printf("Image saved as %s\n", outFilename);
            fclose(BMP);
            free(negativeImageData);

        } else if (choice == 2) {

            unsigned char *grayImageData = (unsigned char *) malloc(sizeof(unsigned char) * imageSize);
            memcpy(grayImageData, imageData, sizeof(unsigned char) * imageSize);

            BmpToGrayBlack(grayImageData, imageSize);

            char outFilename[100] = "blackGray.bmp";
            fopen_s(&BMP ,outFilename, "wb");

            WriteInBMP(header, infoHeader, BMP, grayImageData, imageSize);

            printf("Image saved as %s\n", outFilename);
            fclose(BMP);
            free(grayImageData);

        } else if (choice == 3) {

            gammaParam(&gamma, "choose the value of gamma parameter (from 0.5 to 2.2): \0", 0.5, 2.2);

            unsigned char *gammaCorrectionBMP = (unsigned char *) malloc(sizeof(unsigned char) * imageSize);
            memcpy(gammaCorrectionBMP, imageData, sizeof(unsigned char) * imageSize);

            gammaCorrection(gammaCorrectionBMP, imageSize, gamma);

            char outFilename[100] = "gammaCorrected.bmp";
            fopen_s(&BMP ,outFilename, "wb");

            WriteInBMP(header, infoHeader, BMP, gammaCorrectionBMP, imageSize);

            printf("Image saved as %s\n", outFilename);
            fclose(BMP);
            free(gammaCorrectionBMP);

        } else if (choice == 4) {

            unsigned char* medianFiltered = (unsigned char*) malloc(sizeof (unsigned char) * imageSize);
            memcpy(medianFiltered, imageData, sizeof (unsigned char) * imageSize);

            medianFilter(medianFiltered, &infoHeader);

            char outFilename[100] = "medianFiltered.bmp";
            fopen_s(&BMP ,outFilename, "wb");

            WriteInBMP(header, infoHeader, BMP, medianFiltered, imageSize);

            printf("Image saved as %s\n", outFilename);
            fclose(BMP);
            free(medianFiltered);

        }
        else if (choice == 5) {
            break;
        }
    }
}

void medianFilter(unsigned char *imageData, BMPInfoHeader *infoHeader) {

        int width = infoHeader->width;
        int height = infoHeader->height;
        int bytesPerPixel = infoHeader->bitsPerPixel / 8;

        unsigned char *buffer = (unsigned char *) malloc(sizeof(unsigned char) * width * height * bytesPerPixel);
        memcpy(buffer, imageData, sizeof(unsigned char) * width * height * bytesPerPixel);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
               cycles(x, y, infoHeader, imageData, buffer);
            }
        }
        free(buffer);
}
<<<<<<< HEAD

    void cycles(int x, int y, BMPInfoHeader* infoHeader, unsigned char* imageData, const unsigned char* buffer){

        int width = infoHeader->width;
        int height = infoHeader->height;
        int bytesPerPixel = infoHeader->bitsPerPixel / 8;

        int sumRed = 0, sumGreen = 0, sumBlue = 0, count = 0;
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                int yy = y + dy;
                int xx = x + dx;
                if (yy >= 0 && yy < height && xx >= 0 && xx < width) {
                    int index = ((yy * width) + xx) * bytesPerPixel;
                    sumRed += buffer[index];
                    sumGreen += buffer[index + 1];
                    sumBlue += buffer[index + 2];
                    count++;
                }
            }
        }
        int index = ((y * width) + x) * bytesPerPixel;
        imageData[index] = (unsigned char)(sumRed / count);
        imageData[index + 1] = (unsigned char)(sumGreen / count);
        imageData[index + 2] = (unsigned char)(sumBlue / count);
}


=======
>>>>>>> 255a3d4bf78f4eb1b128ad652f86268c03dd5986

    void cycles(int x, int y, const BMPInfoHeader* infoHeader, unsigned char* imageData, const unsigned char* buffer){

        int width = infoHeader->width;
        int height = infoHeader->height;
        int bytesPerPixel = infoHeader->bitsPerPixel / 8;

        int sumRed = 0;
        int sumGreen = 0;
        int sumBlue = 0;
        int count = 0;
        
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                int yy = y + dy;
                int xx = x + dx;
                if (yy >= 0 && yy < height && xx >= 0 && xx < width) {
                    int index = ((yy * width) + xx) * bytesPerPixel;
                    sumRed += buffer[index];
                    sumGreen += buffer[index + 1];
                    sumBlue += buffer[index + 2];
                    count++;
                }
            }
        }
        int index = ((y * width) + x) * bytesPerPixel;
        imageData[index] = (unsigned char)(sumRed / count);
        imageData[index + 1] = (unsigned char)(sumGreen / count);
        imageData[index + 2] = (unsigned char)(sumBlue / count);
}
