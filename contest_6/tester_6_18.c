#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node_cor {
    char *key;
    int len;
    int sec_len;
    struct Node_cor *son;
    struct Node_cor *next;
} Node_cor;


Node_cor *add(Node_cor *head, char *str, int len) {
    if (!head) {
        head = calloc(1, sizeof(*head));
        head->key = str;
        head->len = len;
        return head;
    }
    int curr = 0;
    for (; curr < head->len && head->key[curr] == str[curr]; ++curr);
    if (!curr) {
        head->son = add(head->son, str, len);
    } else if (curr == len) {
    } else if (curr == head->len) {
        head->next = add(head->next, str + curr, len - curr);
    } else {
        Node_cor *copy = add(NULL, head->key + curr, head->len - curr);
        copy->next = head->next;
        copy->son = add(copy->son, str + curr, len - curr);
        head->next = copy;
        head->len = curr;
    }
    return head;
}


Node_cor *update(Node_cor *head, char *str, int len) {
    if (!head) {
        return head;
    }
    int curr = 0;
    for (; curr < head->len && head->key[curr] == str[curr]; ++curr);
    if (!curr) {
        head->son = update(head->son, str, len);
    }
    if (curr == head->len) {
        head->next = update(head->next, str + curr, len - curr);
    }
    head->sec_len = head->sec_len > curr ? head->sec_len : curr;
    return head;
}


int substr_count(Node_cor *head) {
    if (!head) {
        return 0;
    }
    return substr_count(head->son) + head->sec_len + substr_count(head->next);
}


void print(Node_cor *head) {
    if (!head) {
        return;
    }
    print(head->son);
    printf("%s %d %d\n", head->key, head->len, head->sec_len);
    print(head->next);
}


void del(Node_cor *head) {
    if (!head) {
        return;
    }
    del(head->son);
    del(head->next);
    free(head);
}


int correct(char *str1, char *str2) {
    Node_cor *head = NULL;

    int len1 = strlen(str1), len2 = strlen(str2);

    for (int i = 0; i < len1; ++i) {
        head = add(head, str1 + i, len1 - i);
    }
    for (int i = 0; i < len2; ++i) {
        head = update(head, str2 + i, len2 - i);
    }

    int cnt = substr_count(head) + 1;
    del(head);

    return cnt;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct Node {
    struct Branch {
        int front, len;
        char *str;
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


struct Branch *init_branch(char *str, int front, int len, int w1, int w2) {
    struct Branch *b = malloc(sizeof(struct Branch));

    b->str = str;
    b->front = front;
    b->len = len;
    b->sub_trie = init_node(w1, w2);

    return b;
}


struct Branch *add_branch(Node *trie, char *str, int front, int len, int w1, int w2) {
    trie->to = realloc(trie->to, sizeof(struct Branch *) * ++trie->cnt);

    return trie->to[trie->cnt - 1] = init_branch(str, front, len, w1, w2);
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
        if (b->str[b->front] == str[offset]) {
            return i;
        }
    }

    return -1;
}


struct Branch *fork_branch(struct Branch *branch, char *str, int len, int offset, int fork, int w1, int w2) {
    struct Branch *ret = malloc(sizeof(struct Branch));

    ret->str = branch->str;
    ret->front = branch->front;
    ret->len = fork;
    ret->sub_trie = init_node(w1 || branch->sub_trie->w1, w2 || branch->sub_trie->w2);

    if (len - offset != fork) {
        add_branch(ret->sub_trie, str, offset + fork, len - offset - fork, w1, w2);
    }

    struct Branch *old = add_branch(ret->sub_trie, branch->str, branch->front + fork, branch->len - fork,
                                    branch->sub_trie->w1, branch->sub_trie->w2);
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
        add_branch(trie, str, offset, len - offset, w1, w2);
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


const int MAX_STR_LEN = 2000;


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


int program(char *str_1, char *str_2) {
    Node *trie = init_node(1, 1);
    const int len_1 = (int) strlen(str_1), len_2 = (int) strlen(str_2);

    for (int offset = 0; offset < len_1; ++offset) {
        add_substr(trie, str_1, len_1, offset, 1, 0);
    }

    for (int offset = 0; offset < len_2; ++offset) {
        add_substr(trie, str_2, len_2, offset, 0, 1);
    }

    int cnt = 1 + count(NULL, trie);

    delete(trie);

    return cnt;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int main(void) {
    const int MOD = 100;

    while (1) {
        int len_1 = rand() % MOD, len_2 = rand() % MOD;
        char str_1[len_1 + 1], str_2[len_2 + 1];
        for (int i = 0; i < len_1; ++i) {
            str_1[i] = 'a' + rand() % 26;
        }
        for (int i = 0; i < len_2; ++i) {
            str_2[i] = 'a' + rand() % 26;
        }

        str_1[len_1] = '\0', str_2[len_2] = '\0';

        if (program(str_1, str_2) != correct(str_1, str_2)) {
            printf("%s\n%s", str_1, str_2);
            break;
        }

    }

    return 0;
}
