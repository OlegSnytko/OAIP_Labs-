#include "header.h"

int main() {

    treeNode* node;
    node = NULL;
    FILE* dataBase;
    fopen_s(&dataBase, "C:\\OAIP_Labs-\\src\\LAB4SEM2\\data.txt", "r");
    if(!dataBase){
        printf("this is invalid file");
        exit(0);
    }

    node = readData(dataBase);
    fclose(dataBase);


    PlaySound(TEXT("start.wav"), NULL, SND_ASYNC | SND_FILENAME);
    timeLoad();
    Sleep(MUSICTIME);
    PlaySound(NULL, NULL, 0);

    printf("Answer the question in a root to start the game.(yes/no):\n\n");

    guessObject(node);
    //menu(node);

    if (fopen_s(&dataBase, "C:\\OAIP_Labs-\\src\\LAB4SEM2\\data.txt", "w") != 0) {
        printf("Failed to open the file");
        exit(0);
    }

    loadTheDataBase(dataBase, node);
    fclose(dataBase);
    freeTreeNode(node);
    return 0;
}

