
#include "header.h"

int main() {
    int len = 0;
    int index = 0;
    printf("input number of car brands: ");
    scan(&len);
    CAR *cars;
    cars = (CAR *) calloc(len, sizeof(CAR));
    inputCar(cars, len);
    printingTheStructure(cars, len);
    printf("\n");
    menuFunction(cars, len);
    printf("\n");
    functionalityCheck("what structure to delete: ", &index, 0, 10);
    deleteStructure(&cars, &len, index);
    printingTheStructure(cars, len);
    menuFunction2(cars, len);
    return 0;
}
