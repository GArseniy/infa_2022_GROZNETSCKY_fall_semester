#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct Node {
    struct Branch {
        int front, len;
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


void delete_node(Node *node) {
    while (node->cnt--) {
        delete(node->to[node->cnt]->sub_trie);
        free(node->to[node->cnt]);
    }

    free(node->to);
    free(node);
}


struct Branch *init_branch(int front, int len) {
    struct Branch *b = malloc(sizeof(struct Branch));

    b->front = front;
    b->len = len;
    b->sub_trie = init_node();

    return b;
}


struct Branch *add_branch(Node *trie, int front, int len) {
    trie->to = realloc(trie->to, sizeof(struct Branch *) * ++trie->cnt);

    return trie->to[trie->cnt - 1] = init_branch(front, len);
}


int count_fork(struct Branch *branch, char *str, int len, int offset) {
    int cnt = 0, front = branch->front;

    while (cnt < branch->len && offset + cnt < len && str[front + cnt] == str[offset + cnt]) {
        ++cnt;
    }

    return cnt;
}


int search_branch(Node *trie, char *str, int len, int offset) {
    for (int b = 0, stop = trie->cnt; b < stop; ++b) {
        int front = trie->to[b]->front;
        if (str[front] == str[offset]) {
            return b;
        }
    }

    return -1;
}


struct Branch *fork_branch(struct Branch *branch, int len, int offset, int fork) {
    struct Branch *ret = malloc(sizeof(struct Branch));

    ret->front = branch->front;
    ret->len = fork;
    ret->sub_trie = init_node();

    struct Branch *old = add_branch(ret->sub_trie, branch->front + fork, branch->len - fork);

    if (len - offset != fork) {
        add_branch(ret->sub_trie, offset + fork, len - offset - fork);
    }

    delete(old->sub_trie);
    old->sub_trie = branch->sub_trie;

    free(branch);

    return ret;
}


void add_substr(Node *trie, char *str, int len, int offset) {
    int b = search_branch(trie, str, len, offset);

    if (b == -1) {
        add_branch(trie, offset, len - offset);
        return;
    }

    int fork = count_fork(trie->to[b], str, len, offset);

    if (fork != trie->to[b]->len) {
        trie->to[b] = fork_branch(trie->to[b], len, offset, fork);
        return;
    }

    add_substr(trie->to[b]->sub_trie, str, len, offset + fork);
}


int count(Node *trie) {
    int cnt = 0;

    for (int i = 0, stop = trie->cnt; i < stop; ++i) {
        cnt += count(trie->to[i]->sub_trie) + trie->to[i]->len;
    }

    return cnt;
}


const int MAX_STR_LEN = 2000;


int main(void) {
    char str[MAX_STR_LEN + 1];
    scanf("%s", str);
    const int len = (int) strlen(str);

    Node *trie = init_node();

    for (int offset = 0; offset < len; ++offset) {
        add_substr(trie, str, len, offset);
    }

    printf("%d", 1 + count(trie));

    delete(trie);

    return 0;
}
