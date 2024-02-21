#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct Node {
    struct Branch {
        int front, len;
        char *str;
        struct Node *sub_trie;
    } **to;
    int w1, w2;
    int cnt;
} node;


node *node_init(int w1, int w2) {
    node *node = malloc(sizeof(node) * 1);

    node->cnt = 0;
    node->w1 = w1;
    node->w2 = w2;
    node->to = malloc(0);

    return node;
}


void node_delete(node *node) {
    while (node->cnt--) {
        node_delete(node->to[node->cnt]->sub_trie);
        free(node->to[node->cnt]);
    }

    free(node->to);
    free(node);
}


struct Branch *branch_init(char *str, int front, int len, int w1, int w2) {
    struct Branch *b = malloc(sizeof(struct Branch));

    b->str = str;
    b->front = front;
    b->len = len;
    b->sub_trie = node_init(w1, w2);

    return b;
}


void branch_delete(struct Branch *b) {
    node_delete(b->sub_trie);
    free(b);
}


struct Branch *branch_add(node *trie, char *str, int front, int len, int w1, int w2) {
    trie->to = realloc(trie->to, sizeof(struct Branch *) * ++trie->cnt);

    return trie->to[trie->cnt - 1] = branch_init(str, front, len, w1, w2);
}


int branch_fork_len(struct Branch *branch, char *str, int len, int offset) {
    int cnt = 0, front = branch->front;

    while (cnt < branch->len && offset + cnt < len && branch->str[front + cnt] == str[offset + cnt]) {
        ++cnt;
    }

    return cnt;
}


int branch_search(node *trie, char *str, int offset) {
    for (int i = 0, stop = trie->cnt; i < stop; ++i) {
        struct Branch *b = trie->to[i];

        if (b->str[b->front] == str[offset]) {
            return i;
        }
    }

    return -1;
}


struct Branch *branch_fork(struct Branch *branch, char *str, int len, int offset, int fork, int w1, int w2) {
    struct Branch *ret = branch_init(branch->str, branch->front, fork,
                                     w1 || branch->sub_trie->w1, w2 || branch->sub_trie->w2);

    if (len - offset != fork) {
        branch_add(ret->sub_trie, str, offset + fork, len - offset - fork, w1, w2);
    }

    struct Branch *b = branch_add(ret->sub_trie, branch->str, branch->front + fork, branch->len - fork,
                                  branch->sub_trie->w1, branch->sub_trie->w2);
    node_delete(b->sub_trie);
    b->sub_trie = branch->sub_trie;
    free(branch);

    return ret;
}


void node_add(node *trie, char *str, int len, int offset, int w1, int w2) {
    trie->w1 |= w1;
    trie->w2 |= w2;

    if (offset == len) {
        return;
    }

    int b = branch_search(trie, str, offset);

    if (b == -1) {
        branch_add(trie, str, offset, len - offset, w1, w2);
        return;
    }

    int fork = branch_fork_len(trie->to[b], str, len, offset);

    if (fork != trie->to[b]->len) {
        trie->to[b] = branch_fork(trie->to[b], str, len, offset, fork, w1, w2);
        return;
    }

    node_add(trie->to[b]->sub_trie, str, len, offset + fork, w1, w2);
}


int node_count(struct Branch *branch) {
    int cnt = branch->len;

    for (int i = 0, stop = branch->sub_trie->cnt; i < stop; ++i) {
        struct Branch *b = branch->sub_trie->to[i];

        if (b->sub_trie->w1 && b->sub_trie->w2) {
            cnt += node_count(b);
        }
    }

    return cnt;
}


const int MAX_STR_LEN = 4000;


int main(void) {
    char str_1[MAX_STR_LEN + 1], str_2[MAX_STR_LEN + 1];
    scanf("%s %s", str_1, str_2);
    const int len_1 = strlen(str_1), len_2 = strlen(str_2);

    struct Branch *b = branch_init(NULL, 0, 0, 0, 0);

    for (int i = 0; i < len_1; ++i) {
        node_add(b->sub_trie, str_1, len_1, i, 1, 0);
    }
    for (int i = 0; i < len_2; ++i) {
        node_add(b->sub_trie, str_2, len_2, i, 0, 1);
    }

    printf("%d", 1 + node_count(b));

    branch_delete(b);

    return 0;
}
