#include <stdio.h>
#include "header.h"

int main() {
    FILE* compressed = fopen("C:\\LABA2file\\f2.txt", "r+");
    FILE* decompressed = fopen("C:\\LABA2file\\f3.txt","w+");
    FILE* tempFile = fopen("C:\\LABA2file\\temp.txt", "w+");
    FILE* dictionary = fopen("C:\\LABA2file\\dictionary.txt", "r+");
    if(compressed == NULL){
        printf("File is not found");
        return 0;
    }
    char string[2000];
    Node* head = initNode();

    rewind(compressed);
    while(fgets(string, 2000, compressed) != NULL){
        fputs(string, tempFile);
        meetingFrequencies(string, head);
    }

    printf("\n");
    char word1[100];
    char word2[100];
    rewind(dictionary);
    for (int i = numberOfStringInFile(dictionary); i >= 1; i--){
        fseek(dictionary, startStringInFile(dictionary, i), SEEK_SET);
        fgets(string, 2000, dictionary);
        int j;
        for (j = 0; string[j] != '-'; j++){
            word1[j] = string[j];
            word1[j+1] = '\0';
        }
        int k = 0;
        for (++j; string[j] != '\n'; j++, k++){
            word2[k] = string[j];
            word2[k+1] = '\0';

        }
        printf("\n%s %s", word1, word2);
        rewind(dictionary);
        replaceWords(tempFile, decompressed, word1, word2);

        rewind(decompressed);
        freopen("C:\\LABA2file\\tempFile.txt", "w+", tempFile);
        while(fgets(string,2000, decompressed) != NULL) {
            fprintf(tempFile, "%s", string);
        }
    }
    printf("\n");

    fclose(tempFile);
    fclose(decompressed);
    fclose(compressed);
    remove("C:\\LABA2file\\temp.txt\0");
    printf("Decompression...");
    printf("\nDecompression completed");
    return 0;
}



