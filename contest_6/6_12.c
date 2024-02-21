#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct Node {
    struct Branch {
        int front, len;
        struct Node *sub_trie;
    } **to;
    int cnt;
} node;


node *node_init(void) {
    node *root = malloc(sizeof(node));

    root->cnt = 0;
    root->to = malloc(0);

    return root;
}


void node_delete(node *root) {
    while (root->cnt--) {
        node_delete(root->to[root->cnt]->sub_trie);
        free(root->to[root->cnt]);
    }

    free(root->to);
    free(root);
}


struct Branch *branch_init(int front, int len) {
    struct Branch *b = malloc(sizeof(struct Branch));

    b->front = front;
    b->len = len;
    b->sub_trie = node_init();

    return b;
}


struct Branch *branch_add(node *trie, int front, int len) {
    trie->to = realloc(trie->to, sizeof(struct Branch *) * ++trie->cnt);

    return trie->to[trie->cnt - 1] = branch_init(front, len);
}


int branch_fork_len(struct Branch *branch, char *str, int len, int offset) {
    int cnt = 0;

    while (cnt < branch->len && offset + cnt < len &&
           str[branch->front + cnt] == str[offset + cnt]) {
        ++cnt;
    }

    return cnt;
}


int branch_search(node *trie, char *str, int len, int offset) {
    for (int b = 0, stop = trie->cnt; b < stop; ++b) {
        int front = trie->to[b]->front;

        if (front < len && offset < len &&
            str[front] == str[offset]) {
            return b;
        }
    }

    return -1;
}


struct Branch *branch_fork(struct Branch *branch, int len, int offset, int fork) {
    struct Branch *ret = branch_init(branch->front, fork);

    if (len - offset != fork) {
        branch_add(ret->sub_trie, offset + fork, len - offset - fork);
    }

    struct Branch *b = branch_add(ret->sub_trie, branch->front + fork, branch->len - fork);
    node_delete(b->sub_trie);
    b->sub_trie = branch->sub_trie;
    free(branch);

    return ret;
}


void node_add(node *trie, char *str, int len, int offset) {
    if (offset == len) {
        return;
    }

    int b = branch_search(trie, str, len, offset);

    if (b == -1) {
        branch_add(trie, offset, len - offset);
        return;
    }

    int fork = branch_fork_len(trie->to[b], str, len, offset);

    if (fork != trie->to[b]->len) {
        trie->to[b] = branch_fork(trie->to[b], len, offset, fork);
        return;
    }

    node_add(trie->to[b]->sub_trie, str, len, offset + fork);
}


int node_count(node *trie) {
    int cnt = 0;

    for (int i = 0, stop = trie->cnt; i < stop; ++i) {
        cnt += node_count(trie->to[i]->sub_trie) + trie->to[i]->len;
    }

    return cnt;
}


const int MAX_STR_LEN = 2000;


int main(void) {
    char str[MAX_STR_LEN + 1];
    scanf("%s", str);
    const int len = (int) strlen(str);

    node *trie = node_init();

    for (int i = 0; i < len; ++i) {
        node_add(trie, str, len, i);
    }

    printf("%d", 1 + node_count(trie));

    node_delete(trie);

    return 0;
}
