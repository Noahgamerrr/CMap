#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

//Declaration of the enum type which enumerates data types
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

//Declaration of the struct Map
struct Map {
    size_t map_size; //The size of the map
    struct Entry* entries; //The entries inside the map
    enum type key_type; //The type of the key
} Map_init = {0, NULL, INTEGER};


//Declaration of the struct Entry
struct Entry {
    void* key; //the key
    void* value; // the value
};

/*
    This function compares two keys and returns if they're equal or not
    @param key_type The type of the key
    @param map_key The key from the map
    @param key The key requested by the user
    @return are the two keys equal or not
*/
static bool mapkeycmp(enum type key_type, void* map_key, void* key) {
    switch (key_type){
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

/*
    Sets the value of an already existing key in a map
    @param map The map where the value needs to be set
    @param key The key where the value needs to be changed
    @param value The new value
*/
static void mapset(struct Map map, void* key, void* value) {
    for (size_t i = 0; i < map.map_size; i++) {
        if (mapkeycmp(map.key_type, map.entries[i].key, key)) {
            free(map.entries[i].value);
            map.entries[i].value = value;
            return;
        }
    }
}

/*
    Gets the value from the map
    @param map The map where the entry is saved
    @param key The key from which the value needs to be extracted
    @return The value behind the key or NULL, if the map doesn't contain such key
*/
void* mapget(struct Map map, void* key) {
    for (size_t i = 0; i < map.map_size; i++) {
        if (mapkeycmp(map.key_type, map.entries[i].key, key)) return map.entries[i].value;
    }
    return NULL;
}

/*
    Gets the value from the map or a default value
    @param map The map where the entry is saved
    @param key The key from which the value needs to be extracted
    @param def The default value if the key is not in the map
    @return The value behind the key or the default value, if the map doesn't contain such key
*/
void* mapgetordefault(struct Map map, void* key, void* def) {
    void* result = mapget(map, key);
    if (result != NULL) return result;
    return def;
}

/*
    Puts a key-value-pair into the map
    @param map the map in which the entry is saved
    @param key the key of the entry
    @param the value linked to the key
    @return the map with the key-value-pair
*/
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
/*
    delocates the memory from the map
    @param map The map to be reset
*/
void mapfree(struct Map map) {
    for (size_t i = 0; i < map.map_size; i++) {
        free(map.entries[i].key);
        free(map.entries[i].value);
    }
    free(map.entries);
    map.map_size = 0;
}