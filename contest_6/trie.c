#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct Node {
    struct Branch {
        char key;
        struct Node *sub_trie;
    } **to;
    int cnt;
} Node;


Node *init_node(void) {
    Node *node = malloc(sizeof(Node));

    node->cnt = 0;
    node->to = malloc(0);

    return node;
}


struct Branch *init_branch(char key) {
    struct Branch *b = malloc(sizeof(struct Branch));

    b->key = key;
    b->sub_trie = init_node();

    return b;
}


struct Branch *add_branch(Node *trie, char key) {
    trie->to = realloc(trie->to, sizeof(struct Branch *) * ++trie->cnt);

    return trie->to[trie->cnt - 1] = init_branch(key);
}


struct Branch *search_branch(char key, Node *trie) {
    for (int i = 0, stop = trie->cnt; i < stop; ++i) {
        if (trie->to[i]->key == key) {
            return trie->to[i];
        }
    }

    return NULL;
}


void add_word(Node *trie, char *word, int len) {
    Node *sub_trie = trie;
    struct Branch *b;

    for (int i = 0; i < len; ++i) {
        if ((b = search_branch(word[i], sub_trie)) == NULL) {
            b = add_branch(sub_trie, word[i]);
        }

        sub_trie = b->sub_trie;
    }
}


void delete_trie(Node *trie) {
    while (trie->cnt--) {
        delete_trie(trie->to[trie->cnt]->sub_trie);
        free(trie->to[trie->cnt]);
    }

    free(trie->to);
    free(trie);
}


int counter(Node *trie) {
    int cnt = 1;

    for (int i = 0, stop = trie->cnt; i < stop; ++i) {
        cnt += counter(trie->to[i]->sub_trie);
    }

    return cnt;
}


const int MAX_STR_LEN = 2000;


int main(void) {
    char word[MAX_STR_LEN + 1];
    scanf("%s", word);
    const int len = (int) strlen(word);

    Node *trie = init_node();

    for (int i = 0; i < len; ++i) {
        add_word(trie, word + i, len - i);
    }

    printf("%d", counter(trie));

    delete_trie(trie);

    return 0;
}
