#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

char *const colorToStr[] = {"black", "white", "yellow"};

void scan(int *symbol) {
    while (scanf_s("%d", symbol) != 1 || symbol <= 0 || getchar() != '\n') {
        printf("Wrong input. Try again: ");
        rewind(stdin);
    }
}

int strLength(const char *str) {
    int len = 0;
    while (*(str + len) != '\0')
        len++;
    return len;
}

void scanMass(char **mass) {
    *mass = (char *) malloc(1 * sizeof(char));
    for (int i = 0;; i++) {
        (*mass)[i] = (char) getchar();
        *mass = (char *) realloc(*mass, sizeof(char) * (i + 2));
        if ((*mass)[i] == '\n') {
            (*mass)[i] = '\0';
            break;
        }
    }
}

void inputCar(CAR *cars, int len) {
    char *brand;
    char *country;
    for (int i = 0; i < len; i++) {
        printf("input the country of the car: \n");
        scanMass(&country);
        printf("input brand of the car: \n");
        scanMass(&brand);
        printf("input year of realise: ");
        scan(&cars[i].year);
        printf("input the num of different models: ");
        scan(&cars[i].amountOfModels);
        while (1) {
            char string[100];
            printf("Input color: ");
            scanf_s("%s", &string);
            if (strcmp(string, "white") == 0) cars[i].color = white;
            else if (strcmp(string, "black") == 0) cars[i].color = black;
            else if (strcmp(string, "yellow") == 0) cars[i].color = yellow;
            else {
                continue;
            }
            break;
        }
        cars[i].brand = (char*)calloc(strLength(brand), sizeof(char));
        cars[i].brand = brand;
        cars[i].country = (char*)calloc(strLength(country), sizeof(char));
        cars[i].country = country;
        if (i != len - 1) {
            printf("next car:\n");
            rewind(stdin);
        }
    }
}

void printingTheStructure(CAR *cars, int len) {
    for (int i = 0; i < len; i++) {
        printf("Manufacturer country: %s.\t Year of appearance: %d.\t Name of the brand: %s.\t Num of different models: %d\t Color of the car: %s\n",
               cars[i].country, cars[i].year, cars[i].brand, cars[i].amountOfModels, colorToStr[cars[i].color]);
        printf("\n");
    }
}

void functionalityCheck(char *string, int *param, int low, int high) {
    printf("%s", string);
    while (scanf_s("%d", param) != 1  || *param < low || *param > high) {
        rewind(stdin);
        printf("%s", string);
        printf("Try again: ");
    }
}

void quickSortYear(CAR *cars, int left, int right) {
    int i = left;
    int j = right;
    CAR gap = cars[(left + right) / 2];
    do {
        while (cars[i].year < gap.year) {
            i++;
        }
        while (cars[j].year > gap.year) {
            j--;
        }
        if (i <= j) {
            CAR temp = cars[i];
            cars[i] = cars[j];
            cars[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);
    if (i < right) {
        quickSortYear(cars, i, right);
    }
    if (j > left) {
        quickSortYear(cars, left, j);
    }
}

void quickSortAmountOfModels(CAR *cars, int left, int right) {
    int i = left;
    int j = right;
    CAR gap = cars[(left + right) / 2];
    do {
        while (cars[i].amountOfModels < gap.amountOfModels) {
            i++;
        }
        while (cars[j].amountOfModels > gap.amountOfModels) {
            j--;
        }
        if (i <= j) {
            CAR temp = cars[i];
            cars[i] = cars[j];
            cars[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);
    if (i < right) {
        quickSortAmountOfModels(cars, i, right);
    }
    if (j > left) {
        quickSortAmountOfModels(cars, left, j);
    }
}

void menuFunction(CAR *cars, int len) {
    int choice = 0;
    for (;;) {
        functionalityCheck(
                "do you wanna sort with one 0f two parameters? 0 - by year, 1 - by num of models: ",
                &choice, 0, 2);
        if (choice == 0) {
            quickSortYear(cars, 0, len);
            printf("\n");
            printingTheStructure(cars, len);
        }
        if (choice == 1) {
            printf("\n");
            quickSortAmountOfModels(cars, 0, len);
            printf("\n");
            printingTheStructure(cars, len);
        }
        functionalityCheck("0 - to continue, 1 - to break: ", &choice, 0, 1);
        if (choice == 1) break;
        if (choice == 0) continue;
    }
}

void deleteStructure(CAR **cars, int *len, int index) {
    for (int i = index; i < *len; i++) {
        (*cars)[i] = (*cars)[i + 1];
    }
    *cars = (CAR *) realloc(*cars, --(*len) * sizeof(CAR));
}


void bubbleSortForTwoFieldsRight(CAR *cars, int len) {
    for (int i = 1; i < len; i++) {
        for (int j = 0; j < len - 1; j++) {
            if (cars[j].year > cars[j + 1].year) {
                CAR temp = cars[j];
                cars[j] = cars[j + 1];
                cars[j + 1] = temp;
            } else if ((cars[j].year == cars[j + 1].year) && (cars[j].amountOfModels > cars[j + 1].amountOfModels)) {
                CAR temp = cars[j];
                cars[j] = cars[j + 1];
                cars[j + 1] = temp;
            } else if ((cars[j].amountOfModels == cars[j + 1].amountOfModels) && (cars[j].year > cars[j + 1].year)) {
                CAR temp = cars[j];
                cars[j] = cars[j + 1];
                cars[j + 1] = temp;
            }
        }
    }
}

void bubbleSortForTwoFieldsLeft(CAR *cars, int len) {
    for (int i = 1; i < len; i++) {
        for (int j = 0; j < len - 1; j++) {
            if (cars[j].year < cars[j + 1].year) {
                CAR temp = cars[j];
                cars[j] = cars[j + 1];
                cars[j + 1] = temp;
            } else if ((cars[j].year == cars[j + 1].year) && (cars[j].amountOfModels < cars[j + 1].amountOfModels)) {
                CAR temp = cars[j];
                cars[j] = cars[j + 1];
                cars[j + 1] = temp;
            } else if ((cars[j].amountOfModels == cars[j + 1].amountOfModels) && (cars[j].year < cars[j + 1].year)) {
                CAR temp = cars[j];
                cars[j] = cars[j + 1];
                cars[j + 1] = temp;
            }
        }
    }
}

void menuFunction2(CAR *cars, int len) {
    int x = 0; 
    int choice = 0;
    for (;;) {
        functionalityCheck("do you wanna to continue the task? 0 - yes, 1 - no:(SORT BY 2 PARAM): ", &x, 0, 1);
        if (x == 1) break;
        if (x == 0) {
            functionalityCheck("Now choose how to sort. 2 - by descending<, 3 - by increasing>: ", &choice, 2, 3);
            if (choice == 2) {
                bubbleSortForTwoFieldsLeft(cars, len);
                printingTheStructure(cars, len);
            }
            if (choice == 3) {
                bubbleSortForTwoFieldsRight(cars, len);
                printingTheStructure(cars, len);
            }
        }
    }
}
