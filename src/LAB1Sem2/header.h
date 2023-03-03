
#ifndef SEM2LAB1CLION_HEADER_H
#define SEM2LAB1CLION_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    black, white, yellow,
} color;

typedef struct {
    char *brand;
    char *country;
    int year;
    int amountOfModels;
    color color;
} CAR;

void inputCar(CAR* cars, int len);

int strLength(const char* str);

void printingTheStructure(CAR* cars, int len);

void scan(int* symbol);

void scanMass(char** mass);

void functionalityCheck(char* string, int* param, int low, int high);

void quickSortYear(CAR* cars, int left, int right);

void quickSortAmountOfModels(CAR* cars, int left, int right);

void menuFunction(CAR* cars, int len);

void deleteStructure(CAR** cars, int *len, int index);

void bubbleSortForTwoFieldsRight(CAR* cars, int len);

void bubbleSortForTwoFieldsLeft(CAR* cars, int len);

void menuFunction2(CAR* cars, int len);

#endif //SEM2LAB1CLION_HEADER_H
