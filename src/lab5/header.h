
#ifndef LAB5SEM2_HEADER_H
#define LAB5SEM2_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_CACHE_SIZE 3
#define STRING 256
#define LONGSTRING 1024

typedef struct cacheEntry {
    int countEntry;
    char* key;
    char* value;
    char* recordType;
    char* type;
    struct cacheEntry* prev;
    struct cacheEntry* next;
} cacheEntryT;

typedef struct cache {
    int size;
    cacheEntryT* head;
    cacheEntryT* tail;
    cacheEntryT** table;
} cacheT;


cacheEntryT* searchCacheEntry(cacheT* cache, char* key);

int hash(const char* key);

void deleteLastNode(cacheEntryT** head);

cacheEntryT* newCacheEntry(cacheT* cache);

void freeCacheEntry(cacheEntryT* entry);

cacheT* newCache(int max_size);

void freeCache(cacheT* cache);

char* getFromCache(cacheT* cache, char* key);

void loadCacheFromFile(cacheT* cache, char* filename);

void printCacheEntry(cacheT* cache,cacheEntryT* entry);

void printCache(cacheT* cache, cacheEntryT* entry);

bool validateKeyAndDuplicate(cacheT* cache, char* domain);

void addInFile(char* dir, cacheEntryT* entry);

bool validateIP(const char* IP);

void validateChoice(char* string, int* choice, int left, int right);

void menu(char* path);

bool validateRecordType(cacheEntryT* entry);

bool validateType(cacheEntryT* entry);

char* getString();

void add(cacheT* cache, cacheEntryT* entry);

cacheEntryT* newCacheEntryConsole(char* key, char* value, char* recordType, char* type);

void printCacheAll(cacheT* cache);

#endif //LAB5SEM2_HEADER_H