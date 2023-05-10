#include "header.h"

int main() {

    treeNode* node;
    node = NULL;
    FILE* dataBase;
    fopen_s(&dataBase, "C:\\LAB4SEM2\\data.txt", "r");

    if(!dataBase){
        printf("this is invalid file");
        exit(0);
    }

    node = readData(dataBase);
    fclose(dataBase);

    menu(node);

    if (fopen_s(&dataBase, "C:\\LAB4SEM2\\data.txt", "w") != 0) {
        printf("Failed to open the file");
        exit(0);
    }

    LoadTheDataBase(dataBase, node);
    fclose(dataBase);
    freeTreeNode(node);
    return 0;
}

