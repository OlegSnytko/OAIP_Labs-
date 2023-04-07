#include <stdio.h>
#include "header.h"

int main() {
    FILE *f2 = fopen("C:\\LABA2file\\f2.txt", "w+");
    FILE *f1 = fopen("C:\\LABA2file\\f1.txt", "r+");
    FILE *f3 = fopen("C:\\LABA2file\\f3.txt", "w+");
    FILE *dictionary = fopen("C:\\LABA2file\\dictionary.txt", "w+");

    int count = 0;
    char string[2000];
    Node** indexWord;
    int maxCompress = 0;
    Node* head = initNode();
    rewind(f1);
    while(fgets(string, 2000, f1) != NULL){
        fprintf(f2, "%s", string);
        meetingFrequencies(string, head);
    }
    printf("\n");
    do{
        indexWord = compressionDifference(head, &maxCompress);
        if (indexWord[0] == NULL || indexWord[1] == NULL || maxCompress <= 0){
            break;
        }

        for (int i = 0; i < wordLength(indexWord[0]->word, 1); i++){
            fputc((indexWord[0]->word)[i], dictionary);
        }
        fputc('-', dictionary);
        for (int i = 0; i < wordLength(indexWord[1]->word, 1); i++){
            fputc((indexWord[1]->word)[i], dictionary);
        }
        fputc('\n', dictionary);


        replaceWords(f2, f3, indexWord[0], indexWord[1]);

        freopen("C:\\LABA2file\\f2.txt", "w+", f2);
        while(fgets(string,2000, f3) != NULL) {
            fprintf(f2, "%s", string);
        }

        int temp = indexWord[0]->frequencies;
        indexWord[0]->frequencies = indexWord[1]->frequencies;
        indexWord[1]->frequencies = temp;
        count++;
        rewind(f2);
        printf("\n\n");

    }while(1);

    printf("Compression...");
    printf("\n");
    fseek(f2, 0, SEEK_END);
    fclose(f3);
    remove("C:\\LABA2file\\f3.txt");
    printf("count = %d", count);
    printf("\nCompression completed.");
    return 0;
}



