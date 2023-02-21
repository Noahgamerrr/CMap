#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 50

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
    enum type key_type; //The data type of the key
    enum type value_type; //The data type of the value
} Map_init = {0, NULL, INTEGER, INTEGER};


//Declaration of the struct Entry
struct Entry {
    void* key; //The key
    void* value; //The value
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
            return (*(int*)map_key == *(int*)key);
        case CHARACTER:
            return (*(char*)map_key == *(char*)key);
        case STRING:
            return (strcmp((char*)map_key, (char*)key) == 0);
        case FLOAT:
            return (*(float*)map_key = *(float*)key);
        case DOUBLE:
            return (*(double*)map_key = *(double*)key);
        case UNSIGNED_CHARACTER:
            return (*(unsigned char*)map_key = *(unsigned char*)key);
        case UNSIGNED_INTEGER:
            return (*(unsigned int*)map_key == *(unsigned int*)key);
        case SHORT:
            return (*(short*)map_key == *(short*)key);
        case UNSIGNED_SHORT:
            return (*(unsigned short*)map_key = *(unsigned short*)key);
        case LONG:
            return (*(long*)map_key = *(long*)key);
        case LONG_LONG:
            return (*(long long*)map_key = *(long long*)key);
        case UNSIGNED_LONG:
            return (*(unsigned long*)map_key = *(unsigned long*)key);
        case UNSIGNED_LONG_LONG:
            return (*(unsigned long long*)map_key = *(unsigned long long*)key);
        case LONG_DOUBLE:
            return (*(long double*)map_key = *(long double*)key);
        default:
            return false;
    }
}

/*
    Checks if the map is empty
    @param map The map
    @return Is the map empty or not
*/
bool mapempty(struct Map *map) {
    return map->map_size == 0;
}

/*
    Gets the value from the map
    @param map The map where the entry is saved
    @param key The key from which the value needs to be extracted
    @return The value behind the key or NULL, if the map doesn't contain such key
*/
void* mapget(struct Map *map, void* key) {
    for (size_t i = 0; i < map->map_size; i++) {
        if (mapkeycmp(map->key_type, map->entries[i].key, key)) {
            return map->entries[i].value;
        }
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
void* mapgetordefault(struct Map *map, void* key, void* def) {
    void* result = mapget(map, key);
    if (result != NULL) return result;
    return def;
}


/*
    Checks if the map contains a specific key
    @param map The map
    @param key The key 
    @return Does the map contain the key
*/
bool mapcontains(struct Map *map, void* key) {
    return (mapget(map, key) != NULL);
}

/*
    Sets the value of an already existing key in a map
    @param map The map where the value needs to be set
    @param key The key where the value needs to be changed
    @param value The new value
*/
static void mapset(struct Map *map, void* key, void* value) {
    for (size_t i = 0; i < map->map_size; i++) {
        if (mapkeycmp(map->key_type, map->entries[i].key, key)) {
            map->entries[i].value = value;
            return;
        }
    }
}

/*
    Puts a key-value-pair into the map
    @param map The map in which the entry is saved
    @param key The key of the entry
    @param The value linked to the key
*/
void mapput(struct Map *map, void* key, void* value) {
    if (!mapcontains(map, key)) {
        map->map_size++;
        if (mapempty(map)) map->entries = (struct Entry*)malloc(sizeof(struct Entry));
        else map->entries = (struct Entry*)realloc(map->entries, map->map_size*sizeof(struct Entry));
        map->entries[map->map_size - 1].key = key;
        map->entries[map->map_size - 1].value = value;
    } else mapset(map, key, value);
}

/*
    Puts a key-value-pair into the map if the key isn't already reserved
    @param map The map in which the entry is saved
    @param key The key of the entry
    @param The value linked to the key
    @return If the key was able to be put in the map
*/
bool mapputifabsent(struct Map *map, void* key, void* value) {
    if (mapget(map, key) != NULL) return false;
    mapput(map, key, value);
    return true;
}

/*
    Gets the size of the map
    @param map The map from which the size needs to be retrieved
    @return The size of the map
*/
size_t mapsize(struct Map *map) {
    return map->map_size;
}

/*
    Gets all the entries saved in the map
    @param map The map from which the entries need to be retrieved
    @return All the entries saved in the map
*/
struct Entry* mapentries(struct Map *map) {
    return map->entries;
}

/*
    Gets all the keys saved in the map
    @param map The map from which the keys need to be retrieved
    @return All the keys saved in the map
*/
void** mapkeys(struct Map *map) {
    void** keys = malloc(map->map_size * sizeof(void*));
    for (size_t i = 0; i < map->map_size; i++) keys[i] = map->entries[i].key;
    return keys;
}

/*
    Gets all the values saved in the map
    @param map The map from which the values need to be retrieved
    @return All the values saved in the map
*/
void** mapvalues(struct Map *map) {
    void** values = malloc(map->map_size * sizeof(void*));
    for (size_t i = 0; i < map->map_size; i++) values[i] = map->entries[i].value;
    return values;
}

/*
    Removes a key from the map
    @param map The map where the key needs to be removed
    @param key The key to be removed
    @return The value which was linked to the key
*/
void* mapremove(struct Map *map, void* key) {
    struct Entry* entries = mapentries(map);
    void* value = NULL;
    for (size_t i = 0; i < mapsize(map); i++) {
        if (mapkeycmp(map->key_type, entries[i].key, key)) {
            value = entries[i].value;
            for (size_t j = i; j < mapsize(map) - 1; j++) entries[i] = entries[i+1];
            map->map_size--;
            if (!mapempty(map)) map->entries = (struct Entry*)realloc(map->entries, map->map_size*sizeof(struct Entry));
            else map->entries = NULL;
            break;
        }
    }
    entries = NULL;
    return value;
}

/*
    Removes a key-value-pair from the map
    @param map The map where the key needs to be removed
    @param key The key to be removed
    @param value The value to the pair
    @return Returns true if the key-value-relation had been present in the map and has thus been removed
*/
bool mapremovepair(struct Map *map, void* key, void* value) {
    if (!(mapcontains(map, key) && mapkeycmp(map->value_type, mapget(map, key), value))) return false;
    mapremove(map, key);
    return true;
}

/*
    Delocates the memory from the map (only the entries-pointer,
    the keys and values need to be freed individually if dynamically allocated)
    @param map The map to be resets
*/
void mapfree(struct Map *map) {
    free(map->entries);
    map->map_size = 0;
}