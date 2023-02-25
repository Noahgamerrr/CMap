#include <time.h>
#include "map.h"

int val = 5;
int val2 = 7;
int val3 = 8;
int val4 = 10;
Map *map1;

void init_map(Map* map) {
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

void init_map2(Map *map) {
    char *key = "test3";
    char *key2 = "test4";
    char *key3 = "test2";
    int *ptr = &val3;
    int *ptr2 = &val4;
    int *ptr3 = &val2;
    mapput(map, key, ptr);
    mapput(map, key2, ptr2);
    mapput(map, key3, ptr3);
    key = NULL;
    key2 = NULL;
    key3 = NULL;
    ptr = NULL;
    ptr2 = NULL;
    ptr3 = NULL;
}

void incrementvalue(void* key, void* value) {
    (*(int*)value)++;
}

void mergeval(void* old_value, void* value) {
    *(int*)old_value = *(int*)value;
}

void mergemap(void* key, void* value) {
    mapmerge(map1, key, value, mergeval);
}


void printputifabsent(Map *map) {
    static int val3 = 8;
    printf("----------START PUT IF ABSENT----------\n");
    char *key3 = "test3";
    int *ptr3 = NULL;
    ptr3 = &val3;
    printf("PUT WAS SUCCESSFULL: %d\n", mapputifabsent(map, key3, ptr3));
    printf("PUT WAS SUCCESSFULL: %d\n", mapputifabsent(map, key3, ptr3));
    key3 = NULL;
    ptr3 = NULL;
}

void printkeys(Map *map) {
    printf("----------START PRINT KEYS----------\n");
    char** keys = (char**)mapkeys(map);
    for (size_t i = 0; i < mapsize(map); i++) printf("%s\n", keys[i]);
    keys = NULL;
}

void printvalues(Map *map) {
    printf("----------START PRINT VALUES----------\n");
    int** values = (int**)mapvalues(map);
    for (size_t i = 0; i < mapsize(map); i++) printf("%d\n", *values[i]);
    values = NULL;
}

void printentries(Map *map) {
    printf("----------START PRINT ENTRIES----------\n");
    struct Entry* entries = mapentries(map);
    for (size_t i = 0; i < mapsize(map); i++) printf("%s: %d\n", (char*)entries[i].key, *(int*)entries[i].value);
    entries = NULL;
}

void printget(Map *map) {
    printf("----------START PRINT GET----------\n");
    char* test = "test1";
    printf("%d\n", *(int*)mapget(map, test));
    test = "test2";
    printf("%d\n", *(int*)mapget(map, test));
    test = NULL;
}

void printgetordefault(Map *map) {
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

void printcontains(Map *map) {
    printf("----------START CONTAINS----------\n");
    char* test = "test1";
    printf("%d\n", mapcontainskey(map, test));
    test = "not a key";
    printf("%d\n", mapcontainskey(map, test));
    test = NULL;
}

void printremove(Map *map) {
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

void printremovepair(Map *map) {
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

void printreplace(Map *map) {
    printf("----------START REPLACE----------\n");
    char* test = "test2";
    int* def = NULL;
    static int defval = 15;
    def = &defval;
    printf("----------CURRENT ENTRIES----------\n");
    printentries(map);
    printf("--------------------------------\n");
    printf("Replaced value: %d\n", *(int*)mapreplace(map, test, def));
    printf("----------CURRENT ENTRIES----------\n");
    printentries(map);
    test = NULL;
    def = NULL;
}

void printreplacepair(Map *map) {
    printf("----------START REPLACE PAIR----------\n");
    char* test = "test2";
    int* old = NULL;
    static int old_val = 15;
    old = &old_val;
    int* def = NULL;
    static int defval = 7;
    def = &defval;
    printf("----------CURRENT ENTRIES----------\n");
    printentries(map);
    printf("--------------------------------\n");
    printf("Was replaced: %d\n", mapreplacepair(map, test, old, def));
    printf("----------CURRENT ENTRIES----------\n");
    printentries(map);
    printf("Was replaced: %d\n", mapreplacepair(map, test, old, def));
    test = NULL;
    def = NULL;
    old = NULL;
}

void printcontainsvalue(Map *map) {
    printf("----------START REPLACE PAIR----------\n");
    int val = 7;
    int* ptr = &val;
    printf("Map contains value %d: %d\n", val, mapcontainsvalue(map, ptr));
    val = 15;
    printf("Map contains value %d: %d\n", val, mapcontainsvalue(map, ptr));
    ptr = NULL;
}

void printforeach(Map *map) {
    printf("----------START FOREACH----------\n");
    printf("Entries before foreach:\n");
    printentries(map);
    mapforeach(map, incrementvalue);
    printf("Entries after foreach:\n");
    printentries(map);
}

void printmerge(Map *map, Map *map2) {
    printf("----------START MERGE----------\n");
    printf("Entries of 2nd map:\n");
    printentries(map2);
    mapforeach(map2, mergemap);
    printf("Entries after merge:\n");
    printentries(map);
}

void printcompute(Map *map) {
    printf("----------START COMPUTE----------\n");
    char* key = "test2";
    printf("Value of key test2 before compute: %d\n", *(int*)mapget(map, key));
    mapcompute(map, key, incrementvalue);
    printf("Value of key test2 after compute: %d\n", *(int*)mapget(map, key));
}

void runtests(Map *map, Map *map2) {
    init_map(map);
    init_map2(map2);
    printputifabsent(map);
    printkeys(map);
    printvalues(map);
    printentries(map);
    printget(map);
    printgetordefault(map);
    printcontains(map);
    printremove(map);
    printremovepair(map);
    mapclear(map);
    init_map(map);
    printreplace(map);
    printreplacepair(map);
    printcontainsvalue(map);
    printforeach(map);
    printmerge(map, map2);
    printcompute(map);
}

int main() {
    map1 = mapcreate(STRING, INTEGER);
    Map *map2 = mapcreate(STRING, INTEGER);
    runtests(map1, map2);
    printf("----------SUCCESSFUL----------");
    mapfree(map1);
    mapfree(map2);
    return 0;
}