#include "header.h"


void scanString(char** string){
    *string = (char*)malloc(1 * sizeof (char ));
    for(int i = 0; ;i++){
        (*string)[i] = (char)getchar();
        *string = (char*)realloc(*string, (i + 2) * sizeof (char));
        if((*string)[i] == '\n'){
            (*string)[i] = '\0';
            break;
        }
    }
}


void printTree(treeNode* root){
    printf("%s", root->question);
    if (root->left != NULL) {
        printTree(root->left);
    }
    if (root->right != NULL) {
        printTree(root->right);
    }
}


treeNode* createNode(char* input){

    treeNode* node = (treeNode*) malloc(sizeof (treeNode));
    node->question = strdup(input);
    node->left = NULL;
    node->right = NULL;
    return node;

}


treeNode* readData(FILE* dataBase){
    char delimiter[STRING];
    fgets(delimiter, sizeof(delimiter), dataBase);
    if(delimiter[0] == '$') {
        return NULL;
    }
    treeNode* node = createNode(delimiter);
    node->left = readData(dataBase);
    node->right = readData(dataBase);

    return node;
}


void LoadTheDataBase(FILE* file, treeNode* node){
    if(node == NULL){
        fprintf(file, "$\n");
        return;
    }
    fprintf(file, "%s", node->question);
    LoadTheDataBase(file, node->left);
    LoadTheDataBase(file, node->right);

}


void freeTreeNode(treeNode* node){
    if(node == NULL){
        return;
    }
    freeTreeNode(node->left);
    freeTreeNode(node->right);
    free(node->question);
    free(node);
}


void validationChoice(char* string, int* choice, int leftEdge, int rightEdge){
    printf("%s", string);
    while(scanf_s("%d", choice)!= 1 || getchar()!= '\n' || *choice < leftEdge || *choice > rightEdge){
        printf("Invalid input, try again.\n");
        rewind(stdin);
        printf("%s", string);
    }
}


void getLen(int length, char* object){
    for (length = 0; object[length] != '\0'; length++);
    object = (char*) realloc(object, (length + 2) * sizeof(char));
    object[length] = '\n';
    object[length + 1] = '\0';
}


void freeNewObjects(char* answer, char* newObject, char* newAnswer, char* newQuestion){
    free(answer);
    free(newObject);
    free(newAnswer);
    free(newQuestion);
}


void guessObject(treeNode* node){
    char* answer = NULL;
    printf("%s", node->question);
    scanString(&answer);

    while (strcmp(answer, "yes") != 0 && strcmp(answer, "no") != 0){
        printf("\nInvalid input, try again.\n");
        PlaySound(TEXT("validation.wav"), NULL, SND_ASYNC | SND_FILENAME);
        Sleep(TIME404);
        PlaySound(NULL, NULL, 0);
        rewind(stdin);
        scanString(&answer);
    }
    if(strcmp(answer, "yes") == 0){
        if(node->left == NULL){

            printf("Yes!!!, that's right, you've guessed it!");
            PlaySound(TEXT("win.wav"), NULL, SND_ASYNC | SND_FILENAME);
            Sleep(TIMELIMIT);
            PlaySound(NULL, NULL, 0);
            exit(0);

        }
        else{
            guessObject(node->left);
        }
        free(answer);
    }

    else if(strcmp(answer, "no") == 0){
        if(node->right == NULL){
            int length = 0;

            printf("I give up, I don't know what you're thinking of.\n");

            PlaySound(TEXT("fail.wav"), NULL, SND_ASYNC | SND_FILENAME);
            Sleep(NEWTIMELIM);
            PlaySound(NULL, NULL, 0);

            printf("Who/What was the object you were thinking of?\n");
            char* newObject = NULL;
            scanString(&newObject);
            getLen(length, newObject);

            printf("Make the yes/no question that is distinctive %s from %s?\n", newObject, node->question);
            char* newQuestion = NULL;
            scanString(&newQuestion);
            getLen(length, newQuestion);

            printf("What is the answer to the question for %s? (yes/no)\n", newObject);
            char* newAnswer = NULL;
            scanString(&newAnswer);

            node->right = createNode(newQuestion);

            if(strcmp(newAnswer, "yes") == 0){
                node->right->left = createNode(newObject);
            }
            else{
                node->right->right = createNode(newObject);
            }
            freeNewObjects(answer, newObject, newAnswer, newQuestion);
        }
        else{
            free(answer);
            guessObject(node->right);
        }
    }
}


void timeLoad(){
    printf("\n\n");
    for (int i = 0; i <= TIMELIMIT; i += 3000) {
        printf("\r\t\t\t\t\t\t\t\t\t\tGAME LAUNCH.");
        fflush(stdout);
        Sleep(500);
        printf("\r\t\t\t\t\t\t\t\t\t\tGAME LAUNCH..");
        fflush(stdout);
        Sleep(500);
        printf("\r\t\t\t\t\t\t\t\t\t\tGAME LAUNCH...");
        fflush(stdout);
        Sleep(500);
    }
    printf("\n");
}


void guessFirstObj(char* question, char* obj){
    printf("%s", question);
    scanString(&obj);
}


void menu(treeNode* node){
        char* question;
        int choice = 0;
        printf("1) Start the guessing game.\n");
        printf("2) Quit.\n");
        validationChoice("Choose the option:\n", &choice, 1, 2);

        if (choice == 1) {
            timeLoad();
            PlaySound(TEXT("start.wav"), NULL, SND_ASYNC | SND_FILENAME);
            Sleep(MUSICTIME);
            PlaySound(NULL, NULL, 0);

            printf("Answer the question in a root to start the game.(yes/no):\n\n");
            guessFirstObj("Please, guess the Character from the Apex Legends:\n", question);
            guessObject(node);
        }
        else if (choice == 2) {
            exit(0);
        }
}





/*treeNode* getLifFromTree(treeNode* node){
    if(node == NULL){
        return NULL;
    }
    if(node->object != NULL){
        return node;
    }
    treeNode* getLeftLifRes = getLifFromTree(node->left);
    if(getLeftLifRes != NULL){
        return getLeftLifRes;
    }

    treeNode* getRightLifRes = getLifFromTree(node->right);
    if(getRightLifRes != NULL){
        return getRightLifRes;
    }
    return NULL;
}*/

