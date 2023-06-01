#include "header.h"


int hash(const char* key) {
    int hash = 0;
    int i = 0;
    while (key[i] != '\0') {
        hash += key[i];
        i++;
    }
    return hash % MAX_CACHE_SIZE;
}


char* getString(){
    rewind(stdin);
    int length = 1;
    char a;
    char* newString = (char*)malloc(length * sizeof(char));
    while ((a = (char)getchar()) != '\n'){
        newString[length - 1] = a;
        length++;
        newString = (char*) realloc(newString, length * sizeof(char));
    }
    newString[length - 1] = '\0';
    if (newString[0] == '\0') return NULL;
    return newString;
}


cacheEntryT* newCacheEntryConsole(char* key, char* value, char* recordType, char* type) {
    cacheEntryT* entry = (cacheEntryT*)malloc(sizeof(cacheEntryT));
    entry->key = strdup(key);
    entry->value = strdup(value);
    entry->recordType = strdup(recordType);
    entry->countEntry = 0;
    entry->type = strdup(type);
    entry->prev = NULL;
    entry->next = NULL;
    return entry;
}


cacheEntryT* newCacheEntry(cacheT* cache) {
    cacheEntryT* entry = (cacheEntryT*)malloc(sizeof(cacheEntryT));
    printf(" Enter the new domain: ");
    entry->key = getString();
    while (!validateKeyAndDuplicate(cache,entry->key)){
        printf("wrong input\n");
        printf(" Enter the domain: ");
        rewind(stdin);
        entry->key = getString();
    }
    printf("Enter the new type: ");
    entry->type = getString();
    while (!validateType(entry)){
        printf("wrong input\n");
        printf("Enter the type: ");
        rewind(stdin);
        entry->type = getString();
    }
    printf("Enter the new record type:");
    entry->recordType = getString();
    while (!validateRecordType(entry)){
        printf("wrong input\n");
        printf("Enter the record type: ");
        rewind(stdin);
        entry->recordType = getString();
    }
    printf("IP: ");
    entry->value = getString();
    while (!validateIP(entry->value) && !strcmp(entry->recordType, "A\0") || validateKeyAndDuplicate(cache, entry->value) &&
                                                                             !strcmp(entry->recordType, "CNAME\0")){
        printf("wrong input\n");
        printf("IP: ");
        rewind(stdin);
        entry->value = getString();
    }
    entry->prev = NULL;
    entry->next = NULL;

    return entry;
}


void freeCacheEntry(cacheEntryT* entry) {
    free(entry->key);
    free(entry->value);
    free(entry->recordType);
    free(entry->type);
    free(entry);
}


cacheT* newCache(int max_size) {
    cacheT* cache = (cacheT*)malloc(sizeof(cacheT));
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;
    cache->table = (cacheEntryT**)calloc(max_size, sizeof(cacheEntryT*));
    return cache;
}


void freeCache(cacheT* cache) {
    cacheEntryT* curr = cache->head;
    while (curr != NULL) {
        cacheEntryT* next = curr->next;
        freeCacheEntry(curr);
        curr = next;
    }
    free(cache->table);
    free(cache);
}


char* getFromCache(cacheT* cache, char* key) {
    int index = hash(key) % MAX_CACHE_SIZE;
    cacheEntryT* entry = cache->table[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            if (entry != cache->head) {
                if (entry->prev != NULL) {
                    entry->prev->next = entry->next;
                }
                else {
                    cache->table[index] = entry->next;
                }
                if (entry->next != NULL) {
                    entry->next->prev = entry->prev;
                }
                entry->next = cache->head;
                entry->prev = NULL;
            }
            if (strcmp(entry->recordType, "CNAME\0") == 0) {
                return getFromCache(cache, entry->value);
            }
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}


void loadCacheFromFile(cacheT* cache, char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open %s\n", filename);
        exit(0);
    }
    char string[LONGSTRING];
    while (fgets(string, LONGSTRING, file) != NULL) {
        char* key = strtok(string, " \t\n");
        char* type = strtok(NULL, " \t\n");
        char* recordType = strtok(NULL, " \t\n");
        char* value = strtok(NULL, " \t\n");
        if (key != NULL && recordType != NULL && value != NULL && type != NULL) {
            cacheEntryT* entry = newCacheEntryConsole(key, value, recordType, type);
            add(cache, entry);
        }
    }
    fclose(file);
}


cacheEntryT* searchCacheEntry(cacheT* cache, char* key) {
    int index = hash(key) % MAX_CACHE_SIZE;
    cacheEntryT* entry = cache->table[index];
    cacheEntryT* startEntry = cache->table[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            deleteLastNode(&startEntry);

            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}

void deleteLastNode(cacheEntryT** head) {
    if (*head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    cacheEntryT* currentNode = *head;

    // Обрабатываем случай, когда список содержит только один элемент
    if (currentNode->next == NULL) {
        free(currentNode);
        *head = NULL;
        return;
    }

    // Проходим до последнего элемента списка
    while (currentNode->next != NULL) {
        currentNode = currentNode->next;
    }

    // Переустанавливаем указатели для удаления последнего элемента
    currentNode->prev->next = NULL;
    free(currentNode);
}

void printCacheEntry(cacheT* cache,cacheEntryT* entry) {
    entry->countEntry++;
    if (!strcmp(entry->recordType, "CNAME\0")) {
        printf("\n");
        printf("Subdomain: %s\nSubdomain IP address: %s\nDomain: %s\nRecord type: %s\nType: %s\n",
               entry->value, getFromCache(cache, entry->value), entry->key, entry->recordType, entry->type);
        printf("\n");
    } else {
        printf("\n");
        printf("IP address: %s\nDomain: %s\nRecord type: %s\nType: %s\n",
               entry->value, entry->key, entry->recordType, entry->type);
        printf("\n");
    }
}


bool validateIP(const char* IP){
    int dotCount = 0;
    int number = 0;
    int rank = 0;
    int length;
    for (length = 0; IP[length] != 0; length++);
    for(int i = length - 1; i >= 0; i--){
        if(IP[i] >= '1' && IP[i] <= '9'){
            number += (IP[i] - '0') * (int) pow(10, rank);
            rank++;
            if (number > 255) return false;
        }
        else if (IP[i] == '.'){
            number = 0;
            rank = 0;
            dotCount++;
            if (i == 0 || IP[i+1] == '\0' || IP[i+1] == '.') return false;
            if (dotCount == 4){
                return false;
            }
        }
        else {
            return false;
        }
    }
    return dotCount == 3;
}


bool validateKeyAndDuplicate(cacheT* cache, char* domain) {
    return !searchCacheEntry(cache, domain);
}


bool validateType(cacheEntryT* entry){
    return  !strcmp(entry->type, "IN\0");
}


bool validateRecordType(cacheEntryT* entry){
    return !(strcmp(entry->recordType, "A\0") != 0 && strcmp(entry->recordType, "CNAME\0") != 0);
}


void addInFile(char* dir, cacheEntryT* entry){
    FILE* f;
    if(fopen_s(&f, dir, "a+t") != 0){
        printf("cant open file.");
        exit(1);
    }
    fprintf(f,"%s    %s    %s    %s\n", entry->key, entry->type, entry->recordType, entry->value);
    fclose(f);
}


void validateChoice(char* string, int* choice, int left, int right){
    printf("%s", string);
    while (scanf_s("%d", choice)!= 1 || *choice > right || *choice < left){
        printf("Wrong choice, try again.");
        rewind(stdin);
        printf("%s", string);
    }
}


void add(cacheT* cache, cacheEntryT* entry){
    cacheEntryT* head = cache->table[hash(entry->key)];
    if (head == NULL) {
        cache->table[hash(entry->key)] = entry;
        return;
    }
    int count = 1;
    while (head->next != NULL){
        count++;
        head = head->next;
    }
    if (head->next != NULL){
        printf("%s was deleted.\n", head->next->key);
        freeCacheEntry(head->next);
    }
    head->next = entry;
    entry->prev = head;
    entry->next = NULL;
}


void menu(char* path) {
    char domainName[STRING];
    int choice;
    cacheT *cache = newCache(MAX_CACHE_SIZE);
    loadCacheFromFile(cache, path);

    while (1) {
        printf("<<<<<<<<>>>>>>>>\n");
        printf("1) Search type 1 and type 2.\n");
        printf("2) Add a new domain to the cache.\n");
        printf("3) Print cache entries.\n");
        printf("4) Quit.\n");
        printf("<<<<<<<<>>>>>>>>\n");
        validateChoice("Please, choose an option:\n", &choice, 1, 4);
        printf("\n");
        cacheEntryT *entry;

        if (choice == 1) {
            printf("Enter the domain name: ");
            scanf_s("%s", &domainName, 1000);
            entry = searchCacheEntry(cache, domainName);
            entry ? printCacheEntry(cache, entry) : printf("Not found");
        }
        else if (choice == 2) {
            entry = newCacheEntry(cache);
            if ((validateKeyAndDuplicate(cache, domainName) == true) && (validateIP(entry->value) == true)) {
                printf("The IP is successfully added to the cache.\n");
                add(cache, entry);
                addInFile(path, entry);
            } else {
                printf("Invalid input. The entry was not added to the cache.\n");
            }
        }
        else if (choice == 3) {
            for (int i = 0; i < MAX_CACHE_SIZE; i++) {
                if (cache->table[i] == NULL) continue;
                printf("\nHash: %d\n", i + 1);
                printCache(cache, cache->table[i]);
            }
        }
        else if(choice == 4){
            freeCache(cache);
            break;
        }
    }
}


void printCache(cacheT* cache, cacheEntryT* entry) {
    while (entry != NULL) {
        printCacheEntry(cache, entry);
        entry = entry->next;
    }
}






