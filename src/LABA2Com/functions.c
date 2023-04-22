
#include <stdio.h>
#include "header.h"

int isLetter(char symbol){
    return ((symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z'));
}

int wordStart(const char* string, int word) {
    int i;
    for (i = wordFinish(string, word); isLetter(string[i]); i--);
    return i + 1;
}

int wordFinish(const char* string, int word){
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

int  wordLength(const char* string, int word){
    int length;
    length = wordFinish(string, word) - wordStart(string, word);
    return length + 1;
}

int amountWords(const char* string) {
    int count = 0;
    for(int i = 0; string[i] != '\0'; i++) {
        if((isLetter(string[i]) == 1) && (isLetter(string[i + 1]) == 0)){
            count++;
        }
    }
    return count;
}

void meetingFrequencies(const char* string, Node* head){
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

Node* initNode(){
    Node* node = (Node*)malloc(sizeof(Node));
    node->word = "\0";
    node->frequencies = 0;
    node->next = NULL;
    return node;
}

void printList(Node* list) {
    while (list->next != NULL) {
        printf("\n%s, %d", list->word, list->frequencies);
        list = list->next;
    }
}

Node** compressionDifference(Node* head, int* maxCompress){
    Node* node1 = head;
    Node* node2 = NULL;
    Node* indI = NULL;
    Node* indJ = NULL;
    Node** arr = (Node**) malloc(2 * sizeof(Node*));
    int temp;
    *maxCompress = 0;
    while(node1->next != NULL){
        node2 = node1->next;
        while (node2->next != NULL){
            temp = (node1->frequencies * wordLength(node1->word, 1) + (node2->frequencies * wordLength(node2->word, 1)) - (node2->frequencies * wordLength(node1->word, 1) + (node1->frequencies * wordLength(node2->word, 1))) -
                    (wordLength(node1->word, 1) + wordLength(node2->word, 1) + 2));
            if(temp > *maxCompress){
                *maxCompress = temp;
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
}

char* getWord(const char* string, int indStart){
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

//oleg is wordlen wordlen wmi wordlen wmi wordlen oleg wordlen wordlen mmmmmmmmmm mmmmmmmmmm gogogog gogogog.

void replaceWords(FILE* f2, FILE* f3, const Node* wordMax, const Node* wordMin) {
    char buffer[2000];
    const char *word;
    rewind(f2);
    freopen("C:\\LABA2file\\f3.txt","w+",f3);
    while (fgets(buffer, 2000, f2) != NULL) {
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (isLetter(buffer[i]) == 1) {
                word = getWord(buffer, i);
                if (strcmp(wordMin->word, word) == 0) {
                    fputs(wordMax->word, f3);
                } else if (strcmp(wordMax->word, word) == 0) {
                    fputs(wordMin->word, f3);
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
