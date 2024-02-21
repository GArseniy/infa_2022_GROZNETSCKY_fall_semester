#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct Node {
    struct Branch {
        int front, len;
        char *str;
        int str_len;
        struct Node *sub_trie;
    } **to;
    int w1, w2;
    int cnt;
} Node;


Node *init_node(int w1, int w2) {
    Node *node = malloc(sizeof(Node));

    node->cnt = 0;
    node->w1 = w1;
    node->w2 = w2;
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


struct Branch *init_branch(char *str, int const_len, int front, int len, int w1, int w2) {
    struct Branch *b = malloc(sizeof(struct Branch));

    b->str = str;
    b->str_len = const_len;
    b->front = front;
    b->len = len;
    b->sub_trie = init_node(w1, w2);

    return b;
}


struct Branch *add_branch(Node *trie, char *str, int const_len, int front, int len, int w1, int w2) {
    trie->to = realloc(trie->to, sizeof(struct Branch *) * ++trie->cnt);

    return trie->to[trie->cnt - 1] = init_branch(str, const_len, front, len, w1, w2);
}


int count_fork(struct Branch *branch, char *str, int len, int offset) {
    int cnt = 0, front = branch->front;

    while (cnt < branch->len && offset + cnt < len && branch->str[front + cnt] == str[offset + cnt]) {
        ++cnt;
    }

    return cnt;
}


int search_branch(Node *trie, char *str, int len, int offset) {
    for (int i = 0, stop = trie->cnt; i < stop; ++i) {
        struct Branch *b = trie->to[i];
        if (b->front < b->str_len && offset < len && b->str[b->front] == str[offset]) {
            return i;
        }
    }

    return -1;
}


struct Branch *fork_branch(struct Branch *branch, char *str, int len, int offset, int fork, int w1, int w2) {
    struct Branch *ret = malloc(sizeof(struct Branch));

    ret->str = branch->str;
    ret->str_len = branch->str_len;
    ret->front = branch->front;
    ret->len = fork;
    ret->sub_trie = init_node(w1 || branch->sub_trie->w1, w2 || branch->sub_trie->w2);

    if (len - offset != fork) {
        add_branch(ret->sub_trie, str, len, offset + fork, len - offset - fork, w1, w2);
    }

    struct Branch *old = add_branch(ret->sub_trie, branch->str, branch->str_len, branch->front + fork,
                                    branch->len - fork, branch->sub_trie->w1, branch->sub_trie->w2);
    delete(old->sub_trie);
    old->sub_trie = branch->sub_trie;
    free(branch);

    return ret;
}


void add_substr(Node *trie, char *str, int len, int offset, int w1, int w2) {
    trie->w1 |= w1;
    trie->w2 |= w2;

    if (offset == len) {
        return;
    }

    int b = search_branch(trie, str, len, offset);

    if (b == -1) {
        add_branch(trie, str, len, offset, len - offset, w1, w2);
        return;
    }

    int fork = count_fork(trie->to[b], str, len, offset);

    if (fork != trie->to[b]->len) {
        trie->to[b] = fork_branch(trie->to[b], str, len, offset, fork, w1, w2);
        return;
    }

    add_substr(trie->to[b]->sub_trie, str, len, offset + fork, w1, w2);
}


int count(struct Branch *branch, Node *trie) {
    int cnt = 0;

    for (int i = 0, stop = trie->cnt; i < stop; ++i) {
        struct Branch *b = trie->to[i];
        if (b->sub_trie->w1 && b->sub_trie->w2) {
            cnt += count(b, b->sub_trie);
        }
    }

    if (branch) {
        cnt += branch->len;
    }

    return cnt;
}


void print_node(Node *trie, int cnt) {
    for (int i = 0; i < trie->cnt; ++i) {
        for (int j = 0; j < cnt; ++j) {
            printf("\t");
        }

        for (int j = 0; j < trie->to[i]->len; ++j) {
            printf("%c", trie->to[i]->str[trie->to[i]->front + j]);
        }
        if (trie->to[i]->len == 0) {
            printf(".");
        }

        printf(" %d %d\n", trie->to[i]->sub_trie->w1, trie->to[i]->sub_trie->w2);

        print_node(trie->to[i]->sub_trie, cnt + 1);
    }
}


const int MAX_STR_LEN = 4000;


int main(void) {
    Node *trie = init_node(1, 1);

    char str_1[MAX_STR_LEN + 1], str_2[MAX_STR_LEN + 1];
    scanf("%s %s", str_1, str_2);
    const int len_1 = (int) strlen(str_1), len_2 = (int) strlen(str_2);


    for (int offset = 0; offset < len_1; ++offset) {
        add_substr(trie, str_1, len_1, offset, 1, 0);
    }
    for (int offset = 0; offset < len_2; ++offset) {
        add_substr(trie, str_2, len_2, offset, 0, 1);
    }

    //print_node(trie, 0);

    printf("%d", 1 + count(NULL, trie));

    delete(trie);

    return 0;
}
