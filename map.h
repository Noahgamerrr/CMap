#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

enum type {
    INTEGER,
    CHARACTER,
    STRING,
    FLOAT,
    DOUBLE,
    UNSIGNED_CHARACTER,
    UNSIGNED_INTEGER,
    SHORT,
    UNSIGNED_SHORT,
    LONG,
    LONG_LONG,
    UNSIGNED_LONG,
    UNSIGNED_LONG_LONG,
    LONG_DOUBLE
};

struct Map {
    size_t map_size;
    struct Entry* entries;
    enum type key_type;
} Map_init = {0, NULL, INTEGER};

struct Entry {
    void* key;
    void* value;
};

static bool mapkeycmp(struct Map map, void* map_key, void* key) {
    switch (map.key_type){
    case INTEGER:
        return *(int*)map_key == *(int*)key;
    case CHARACTER:
        return *(char*)map_key == *(char*)key;
    case STRING:
        return strcmp((char*)map_key, (char*)key) == 0;
    case FLOAT:
        return *(float*)map_key = *(float*)key;
    case DOUBLE:
        return *(double*)map_key = *(double*)key;
    case UNSIGNED_CHARACTER:
        return *(unsigned char*)map_key = *(unsigned char*)key;
    case UNSIGNED_INTEGER:
        return *(unsigned int*)map_key == *(unsigned int*)key;
    case SHORT:
        return *(short*)map_key == *(short*)key;
    case UNSIGNED_SHORT:
        return *(unsigned short*)map_key = *(unsigned short*)key;
    case LONG:
        return *(long*)map_key = *(long*)key;
    case LONG_LONG:
        return *(long long*)map_key = *(long long*)key;
    case UNSIGNED_LONG:
        return *(unsigned long*)map_key = *(unsigned long*)key;
    case UNSIGNED_LONG_LONG:
        return *(unsigned long long*)map_key = *(unsigned long long*)key;
    case LONG_DOUBLE:
        return *(long double*)map_key = *(long double*)key;
    default:
        return false;
    }
}

static void mapset(struct Map map, void* key, void* value) {
    for (size_t i = 0; i < map.map_size; i++) {
        if (mapkeycmp(map, map.entries[i].key, key)) {
            free(map.entries[i].value);
            map.entries[i].value = value;
            return;
        }
    }
}

void* mapget(struct Map map, void* key) {
    for (size_t i = 0; i < map.map_size; i++) {
        if (mapkeycmp(map, map.entries[i].key, key)) return map.entries[i].value;
    }
    return NULL;
}

void* mapgetordefault(struct Map map, void* key, void* def) {
    void* result = mapget(map, key);
    if (result != NULL) return result;
    return def;
}

struct Map mapput(struct Map map, void* key, void* value) {
    if (mapget(map, key) == NULL) {
        map.map_size++;
        if (map.map_size == 1) map.entries = (struct Entry*)malloc(sizeof(struct Entry));
        else map.entries = (struct Entry*)realloc(map.entries, map.map_size*sizeof(struct Entry));
        map.entries[map.map_size - 1].key = key;
        map.entries[map.map_size - 1].value = value;
    } else mapset(map, key, value);
    return map;
}

void mapfree(struct Map map) {
    for (size_t i = 0; i < map.map_size; i++) {
        free(map.entries[i].key);
        free(map.entries[i].value);
    }
    free(map.entries);
    map.map_size = 0;
}