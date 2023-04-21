
#ifndef LABA2COM_HEADER_H
#define LABA2COM_HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Node{
    char* word;
    int frequencies;
    struct Node* next;
}Node;

int isLetter(char symbol);
int wordStart(char* string, int start);
int wordFinish(const char* string, int finish);
int  wordLength(char* string, int word);
int amountWords(const char* string);
Node* initNode();
char* getWord(const char* string, int indStart);
void meetingFrequencies(char* string, Node* head);
Node** compressionDifference(Node* head, int* maxCompress);
void replaceWords(FILE* f2, FILE* f3, Node* wordMax, Node* wordMin);

#endif //LABA2COM_HEADER_H
