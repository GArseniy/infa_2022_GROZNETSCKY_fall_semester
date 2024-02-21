#include <stdlib.h>
#include <stdio.h>


typedef struct Node {
    struct Branch {
        int front, len;
        struct Node *sub_trie;
    } **to;
    int cnt;
} Node;


void print_node(Node *trie, int cnt, char *str) {
    for (int i = 0; i < trie->cnt; ++i) {
        for (int j = 0; j < cnt; ++j) {
            printf("\t");
        }

        for (int j = 0; j < trie->to[i]->len; ++j) {
            printf("%c", str[trie->to[i]->front + j]);
        }
        if (trie->to[i]->len == 0) {
            printf("0");
        }

        printf("\n");

        print_node(trie->to[i]->sub_trie, cnt + 1, str);
    }
}


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
        if (front < len && offset < len && str[front] == str[offset]) {
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
    add_branch(ret->sub_trie, offset + fork, len - offset - fork);

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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int max_prefix_func(char *str, int start, int len) {
    int pi[len - start];
    pi[0] = 0;

    if (len - start == 1) {
        return 0;
    }

    int j = 0, i = 1;

    while (i < len - start) {
        if (str[i + start] == str[j + start]) {
            pi[i] = j + 1;
            i++;
            j++;
        } else {
            if (j == 0) {
                pi[i] = 0;
                i++;
            } else {
                j = pi[j - 1];
            }
        }
    }

    int max = 0;

    for (int k = 0; k < len - start; k++) {
        if (pi[k] > max) {
            max = pi[k];
        }
    }

    return max;

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(void) {
    const int MOD = 50;

    while (1) {
        int len = rand() % MOD;
        char str[len + 1];
        for (int i = 0; i < len; ++i) {
            str[i] = 'a' + rand() % 26;
        }

        str[len] = '\0';

        Node *trie = init_node();

        for (int offset = 0; offset < len; ++offset) {
            add_substr(trie, str, len, offset);
        }

        int cnt = 1;

        for (int i = len - 1; i >= 0; i--) {
            cnt += len - i - max_prefix_func(str, i, len);
        }

        if (1 + count(trie) != cnt) {
            printf("%s\n", str);
        }

        delete(trie);
    }

    return 0;
}
