#ifndef LAB4SEM2_HEADER_H
#define LAB4SEM2_HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
#define STRING 256
#define TIMELIMIT 6000
#define MUSICTIME 5000
#define NEWTIMELIM 4000
#define TIME404  2000

typedef struct treeNode{
    char* question;
    struct treeNode* right;
    struct treeNode* left;
}treeNode;

void guessObject(treeNode* node);

//API for working with the binary trees.
treeNode* createNode(char* input);
treeNode* readData(FILE* dataBase);
void printTree(treeNode* root);
void LoadTheDataBase(FILE* file, treeNode* node);

//Optimization functions.
void scanString(char** string);
void validationChoice(char* string, int* choice, int leftEdge, int rightEdge);
void freeTreeNode(treeNode* node);
void getLen(int length, char* object);
void freeNewObjects(char* answer, char* newObject, char* newAnswer, char* newQuestion);
void timeLoad();
//treeNode* getLifFromTree(treeNode* node);
void menu(treeNode* node);

#endif //LAB4SEM2_HEADER_H
