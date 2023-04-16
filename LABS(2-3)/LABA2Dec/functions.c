
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

long startStringInFile(FILE* f, int number){
    char a = 'a';
    int count = 1;
    if (number == 1){
        return 0;
    }

    while(!feof(f)){
        a = (char)fgetc(f);
        if (a == '\n'){
            count++;
        }
        if (count == number){
            return ftell(f);
        }
    }
    rewind(f);
    return -1;
}

int numberOfStringInFile(FILE* f){
    char a;
    int count = 0;
    while(!feof(f)){
        a = (char)fgetc(f);
        if (a == '\n'){
            count++;
        }
    }
    rewind(f);
    return count;
}


int isLetter(char symbol){
    return ((symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z'));
}

int wordStart(char* string, int word) {
    int i;
    for (i = wordFinish(string, word); isLetter(string[i]); i--);
    return i + 1;
}

int wordFinish(char* string, int word){
    int count = 0;
    for(int i = 0; string[i] != '\0'; i++){
        if((isLetter(string[i]) == 1) && (isLetter(string[i + 1]) == 0)){
            count++;
            if(count == word){
                return i;
            }
        }
    }
    return -1;
}

int  wordLength(char* string, int word){
    int length;
    length = wordFinish(string, word) - wordStart(string, word);
    return length + 1;
}

int amountWords(char* string) {
    int count = 0;
    for(int i = 0; string[i] != '\0'; i++) {
        if((isLetter(string[i]) == 1) && (isLetter(string[i + 1]) == 0)){
            count++;
        }
    }
    return count;
}

Node* initNode(){
    Node* node = (Node*)malloc(sizeof(Node));
    node->word = "\0";
    node->frequencies = 0;
    node->next = NULL;
    return node;
}

char* getWord(char* string, int indStart){
    char* word = NULL;
    int length = 0;
    for (int i = indStart;; i++, length++){
        word = realloc(word, (length + 1) * sizeof(char));
        word[length] = string[i];
        if (!isLetter(word[length])){
            word[length] = '\0';
            break;
        }
    }
    return word;
}

/*int fileLength(FILE* f){
    rewind(f);
    int length = 0;
    char a;
    while (1){
        a = fgetc(f);
        length++;
        if (a >= '0' && a <= '9'){
            break;
        }
    }
    return length;
}*/

void meetingFrequencies(char* string, Node* head){
    Node* temp;
    int count;
    char* buffer = NULL;
    for(int m = 1; m <= amountWords(string); m++) {
        count = 0;
        buffer = (char*) malloc((wordLength(string, m) + 1) * sizeof(char));
        for (int i = wordStart(string, m), j = 0; i <= wordFinish(string, m); i++, j++) {
            buffer[j] = string[i];
            buffer[j + 1] = '\0';
        }
        temp = head;
        while(temp->next != NULL){
            if(strcmp(buffer, temp->word) == 0) {
                temp->frequencies++;
                count++;
                free(buffer);
                break;
            }
            temp = temp->next;
        }
        temp = head;
        if(count == 0){
            while (temp->next != NULL){
                temp = temp->next;
            }
            temp->frequencies = 1;
            temp->word = buffer;
            temp->next = initNode();
        }
    }
}

/*void printList(Node* list) {
    while (list->next != NULL) {
        printf("\n%s, %d", list->word, list->frequencies);
        list = list->next;
    }
}*/

/*Node** compressionDifference(Node* head, int* decompressMax){
    Node* node1 = head;
    Node* node2 = NULL;
    Node* indI = NULL;
    Node* indJ = NULL;
    Node** arr = (Node**) malloc(2 * sizeof(Node*));
    int temp;
    *decompressMax = INT_MIN;
    while(node1->next != NULL){
        node2 = node1->next;
        while (node2->next != NULL){
            temp = ((node1->frequencies * wordLength(node1->word, 1) + (node2->frequencies * wordLength(node2->word, 1)) - (node2->frequencies * wordLength(node1->word, 1) + (node1->frequencies * wordLength(node2->word, 1)))));
            if(temp > *decompressMax && temp < 0){
                *decompressMax = temp;
                indI = node1;
                indJ = node2;
            }
            node2 = node2->next;
        }
        node1 = node1->next;
    }
    arr[0] = indI;
    arr[1] = indJ;
    return arr;
}*/

void replaceWords(FILE* f2, FILE* f3, char* wordMax, char* wordMin) {
    char buffer[2000];
    char *word;
    rewind(f2);
    freopen("C:\\LABA2file\\f3.txt","w+",f3);
    while (fgets(buffer, 2000, f2) != NULL) {
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (isLetter(buffer[i]) == 1) {
                word = getWord(buffer, i);
                if (strcmp(wordMin, word) == 0) {
                    fputs(wordMax, f3);
                } else if (strcmp(wordMax, word) == 0) {
                    fputs(wordMin, f3);
                } else {
                    fputs(word, f3);
                }
                while(isLetter(buffer[i+1])){
                    i++;
                }
            } else {
                fputc(buffer[i], f3);
            }
        }
    }
    rewind(f2);
    rewind(f3);
}

/*void getFile(char* name, int length){
    FILE* f1 = fopen(name, "r+");
    FILE* f2 = fopen("C:\\LABA2file\\tempp.txt", "w+");
    char a;
    for (int i = 0; i < length; i++){
        a = (char)fgetc(f1);
        fputc(a,f2);
    }
    fclose(f1);
    fclose(f2);
    remove(name);
    rename("C:\\LABA2file\\tempp.txt",name);
}*/
