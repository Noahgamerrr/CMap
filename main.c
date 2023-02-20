#include <time.h>
#include "map.h"

void init_map(struct Map* map) {
    char *key = "sus";
    int *ptr;
    int val = 5;
    ptr = &val;
    *map = mapput(*map, key, ptr);
}

int main() {
    struct Map map = Map_init;
    map.key_type = STRING;
    init_map(&map);
    char* test = "sus";
    printf("%d", *(int*)mapget(map, test));
    mapfree(map);
    return 0;
}