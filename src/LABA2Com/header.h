
#ifndef LABA2COM_HEADER_H
#define LABA2COM_HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define _CRT_SECURE_NO_WARNINGS
typedef struct Node{
    char* word;
    int frequencies;
    struct Node* next;
}Node;

int isLetter(char symbol);
int wordStart(const char* string, int start);
int wordFinish(const char* string, int finish);
int  wordLength(const char* string, int word);
int amountWords(const char* string);
Node* initNode();
char* getWord(const char* string, int indStart);
void meetingFrequencies(const char* string, Node* head);
Node** compressionDifference(Node* head, int* maxCompress);
<<<<<<< HEAD
void replaceWords(FILE* f2, FILE* f3, Node* wordMax, Node* wordMin);
void cycle1(FILE* f3, Node* wordMax, Node* wordMin, char* word, char* buffer, int i);
=======
void replaceWords(FILE* f2, FILE* f3, const Node* wordMax, const Node* wordMin);

>>>>>>> 255a3d4bf78f4eb1b128ad652f86268c03dd5986
#endif //LABA2COM_HEADER_H
