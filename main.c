#include <time.h>
#include "map.h"

int val = 5;
int val2 = 7;
int val3 = 8;

void init_map(struct Map* map) {
    char *key = "test1";
    char *key2 = "test2";
    int *ptr = NULL;
    int *ptr2 = NULL;
    ptr = &val;
    ptr2 = &val2;
    mapput(map, key, ptr);
    mapput(map, key2, ptr2);
    key = NULL;
    key2 = NULL;
    ptr = NULL;
    ptr2 = NULL;
}

void printputifabsent(struct Map *map) {
    printf("----------START PUT IF ABSENT----------\n");
    char *key3 = "test3";
    int *ptr3 = NULL;
    ptr3 = &val3;
    printf("PUT WAS SUCCESSFULL: %d\n", mapputifabsent(map, key3, ptr3));
    printf("PUT WAS SUCCESSFULL: %d\n", mapputifabsent(map, key3, ptr3));
    key3 = NULL;
    ptr3 = NULL;
}

void printkeys(struct Map *map) {
    printf("----------START PRINT KEYS----------\n");
    char** keys = (char**)mapkeys(map);
    for (size_t i = 0; i < mapsize(map); i++) printf("%s\n", keys[i]);
    keys = NULL;
}

void printvalues(struct Map *map) {
    printf("----------START PRINT VALUES----------\n");
    int** values = (int**)mapvalues(map);
    for (size_t i = 0; i < mapsize(map); i++) printf("%d\n", *values[i]);
    values = NULL;
}

void printentries(struct Map *map) {
    printf("----------START PRINT ENTRIES----------\n");
    struct Entry* entries = mapentries(map);
    for (size_t i = 0; i < mapsize(map); i++) printf("%s: %d\n", (char*)entries[i].key, *(int*)entries[i].value);
    entries = NULL;
}

void printget(struct Map *map) {
    printf("----------START PRINT GET----------\n");
    char* test = "test1";
    printf("%d\n", *(int*)mapget(map, test));
    test = "test2";
    printf("%d\n", *(int*)mapget(map, test));
    test = NULL;
}

void printgetordefault(struct Map *map) {
    printf("----------START PRINT GET OR DEFAULT----------\n");
    char* test = "test1";
    int* def = NULL;
    int defval = 0;
    def = &defval;
    printf("%d\n", *(int*)mapgetordefault(map, test, def));
    test = "not a key";
    printf("%d\n", *(int*)mapgetordefault(map, test, def));
    test = NULL;
    def = NULL;
}

void printcontains(struct Map *map) {
    printf("----------START CONTAINS----------\n");
    char* test = "test1";
    printf("%d\n", mapcontains(map, test));
    test = "not a key";
    printf("%d\n", mapcontains(map, test));
    test = NULL;
}

void printremove(struct Map *map) {
    printf("----------START REMOVE----------\n");
    char* test = "test2";
    int* def = NULL;
    int defval = 0;
    def = &defval;
    printf("Current size: %d\n", mapsize(map));
    printf("Current value at key test2: %d\n", *(int*)mapgetordefault(map, test, def));
    printf("----------CURRENT KEYS----------\n");
    printkeys(map);
    printf("--------------------------------\n");
    printf("Removed value: %d\n", *(int*)mapremove(map, test));
    printf("Current size: %d\n", mapsize(map));
    printf("Current value at key test2: %d\n", *(int*)mapgetordefault(map, test, def));
    printf("----------CURRENT KEYS----------\n");
    printkeys(map);
    printf("--------------------------------\n");
    test = NULL;
    def = NULL;
}

void printremovepair(struct Map *map) {
    printf("----------START REMOVE PAIR----------\n");
    char* test = "test1";
    int* def = NULL;
    int defval = 0;
    def = &defval;
    printf("Current size: %d\n", mapsize(map));
    printf("Current value at key test1: %d\n", *(int*)mapgetordefault(map, test, def));
    printf("----------CURRENT KEYS----------\n");
    printkeys(map);
    printf("--------------------------------\n");
    printf("Was removed: %d\n", mapremovepair(map, test, &val));
    printf("Current size: %d\n", mapsize(map));
    printf("Current value at key test1: %d\n", *(int*)mapgetordefault(map, test, def));
    printf("----------CURRENT KEYS----------\n");
    printkeys(map);
    printf("--------------------------------\n");
    printf("Was removed: %d\n", mapremovepair(map, test, &val));
    test = NULL;
    def = NULL;
}

void runtests(struct Map *map) {
    printputifabsent(map);
    printkeys(map);
    printvalues(map);
    printentries(map);
    printget(map);
    printgetordefault(map);
    printcontains(map);
    printremove(map);
    printremovepair(map);
}

int main() {
    struct Map map = Map_init;
    map.key_type = STRING;
    init_map(&map);
    runtests(&map);
    printf("----------SUCCESSFUL----------");
    mapfree(&map);
    return 0;
}