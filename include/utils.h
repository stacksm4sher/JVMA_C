#ifndef JVMA_UTILS_H
#define JVMA_UTILS_H

typedef struct Hash_Map_Node *node;

struct Hash_Map_Node {
    char *key;
    char *value;
    node next_node;
    unsigned int hash;
    unsigned int key_length;
};

typedef struct {
    node *node_array;
    unsigned int size;
} hash_map;

hash_map allocate_hash_map();
void put_hash_map(hash_map hm, char *key, char *value);
char *get_hash_map(hash_map hm, const char *key);
void remove_hash_map(hash_map hm, const char *key);

#endif //JVMA_UTILS_H
