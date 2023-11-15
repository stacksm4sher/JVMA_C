#include <malloc.h>
#include "utils.h"

const unsigned int DEFAULT_BUCKET_ARRAY_SIZE = 16;
const unsigned int NODE_MEM_SIZE = 8 + 8 + 8 + 4 + 4;

unsigned int length(const char *value) {
    unsigned int length = 0;

    char s_char = *value;
    unsigned int ptr = 0;

    while (s_char != 0) {
        s_char = *(value + ++ptr);
        ++length;
    }

    return length;
}

int equals(const char *v1,
           const unsigned int l1,
           const char *v2,
           const unsigned int l2) {
    if (l1 != l2) {
        return 0;
    }

    for (int i = 0; i < l1; ++i) {
        if (*(v1 + i) != *(v2 + i)) {
            return 0;
        }
    }

    return 1;
}

unsigned int hash(const char *key, const unsigned int len) {
    unsigned int h = len;
    unsigned int k;
    for (int i = 0; i < len / 4; i++) {
        k = *(unsigned int *) &key[i * 4];
        k *= 0xcc9e2d51;
        k = (k << 15) | (k >> 17);
        k *= 0x1b873593;
        h ^= k;
        h = (h << 13) | (h >> 19);
        h = h * 5 + 0xe6546b64;
    }
    k = 0;
    for (unsigned int i = len / 4 * 4; i < len; i++) {
        k <<= 8;
        k |= key[i];
    }
    k *= 0xcc9e2d51;
    k = (k << 15) | (k >> 17);
    k *= 0x1b873593;
    h ^= k;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}

hash_map allocate_hash_map() {
    hash_map hm;
    hm.node_array = (node *) malloc(DEFAULT_BUCKET_ARRAY_SIZE * sizeof(node *));
    hm.size = DEFAULT_BUCKET_ARRAY_SIZE;

    for (int i = 0; i < DEFAULT_BUCKET_ARRAY_SIZE; ++i) {
        *(hm.node_array + i) = NULL;
    }

    return hm;
}

void put_hash_map(const hash_map hm, char *key, char *value) {
    const unsigned int key_length = length(key);
    const unsigned int key_hash = hash(key, key_length);
    const unsigned int bucket_idx = key_hash & (hm.size - 1);

    node n = *(hm.node_array + bucket_idx);

    if (n == NULL) {
        node newn = (node) malloc(NODE_MEM_SIZE);
        newn->hash = key_hash;
        newn->key = key;
        newn->key_length = key_length;
        newn->value = value;
        newn->next_node = NULL;
        *(hm.node_array + bucket_idx) = newn;
        return;
    }

    if (n->hash == key_hash) {
        if (equals(key, key_length, n->key, n->key_length)) {
            n->value = value;
            return;
        }
    }

    node nn = n->next_node;
    node pn;

    unsigned int lcnt = 0;
    while (1) {

        if (nn == NULL) {
            nn = (node) malloc(NODE_MEM_SIZE);
            nn->hash = key_hash;
            nn->key = key;
            nn->key_length = key_length;
            nn->value = value;
            nn->next_node = NULL;

            if (lcnt == 0) {
                n->next_node = nn;
                return;
            }

            pn->next_node = nn;

            return;
        }

        if (nn->hash == key_hash) {
            if (equals(key, key_length, nn->key, nn->key_length)) {
                nn->value = value;
                return;
            }
        }

        pn = nn;
        nn = nn->next_node;
        ++lcnt;
    }
}

char *get_hash_map(const hash_map hm, const char *key) {
    const unsigned int key_length = length(key);
    const unsigned int key_hash = hash(key, key_length);
    const unsigned int bucket_idx = key_hash & (hm.size - 1);

    node n = *(hm.node_array + bucket_idx);

    if (n == NULL) {
        return NULL;
    }

    if (n->hash == key_hash) {
        if (equals(key, key_length, n->key, n->key_length)) {
            return n->value;
        }
    }

    node nn = n->next_node;

    while (1) {

        if (nn == NULL) {
            return NULL;
        }

        if (nn->hash == key_hash) {
            if (equals(key, key_length, nn->key, nn->key_length)) {
                return nn->value;
            }
        }

        nn = nn->next_node;
    }
}

void remove_hash_map(const hash_map hm, const char *key) {
    const unsigned int key_length = length(key);
    const unsigned int key_hash = hash(key, key_length);
    const unsigned int bucket_idx = key_hash & (hm.size - 1);

    node n = *(hm.node_array + bucket_idx);

    if (n == NULL) {
        return;
    }

    if (n->hash == key_hash) {
        if (equals(key, key_length, n->key, n->key_length)) {

            node nn = n->next_node;

            if (nn != NULL) {
                *(hm.node_array + bucket_idx) = nn;
                free(n);
                return;
            }

            *(hm.node_array + bucket_idx) = NULL;
            free(n);

            return;
        }
    }

    node nn = n->next_node;
    node pn = n;

    unsigned int lcnt = 0;

    while (1) {

        if (nn == NULL) {
            return;
        }

        if (nn->hash == key_hash) {
            if (equals(key, key_length, nn->key, nn->key_length)) {

                node nnn;
                if (lcnt == 0) {
                    nnn = n->next_node;
                } else {
                    nnn = nn->next_node;
                }

                if (nnn != NULL) {
                    pn->next_node = nnn;
                    free(nn);
                    return;
                }

                pn->next_node = NULL;
                free(nn);

                return;
            }
        }

        pn = nn;
        nn = nn->next_node;
        ++lcnt;
    }
}
