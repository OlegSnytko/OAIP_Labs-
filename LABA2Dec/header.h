
#ifndef LABA2DEC_HEADER_H
#define LABA2DEC_HEADER_H

typedef struct Node{
    char* word;
    int frequencies;
    struct Node* next;
}Node;

int isLetter(char symbol);
int wordStart(char* string, int start);
int wordFinish(char* string, int finish);
int  wordLength(char* string, int word);
int amountWords(char* string);
Node* initNode();
void meetingFrequencies(char* string, Node* head);
Node** compressionDifference(Node* head, int* decompressMax);
void replaceWords(FILE* f2, FILE* f3, char* wordMax, char* wordMin);
void printList(Node* list);

int numberOfStringInFile(FILE* f);
long startStringInFile(FILE* f, int number);

#endif //LABA2DEC_HEADER_H
