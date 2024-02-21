#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int key;
    struct Node *prev, *next;
} node;


node *node_push(node *head, int key) {
    node *next = malloc(sizeof(node));

    next->key = key;
    next->prev = head;
    next->next = (head) ? head->next : NULL;

    if (head) {
        if (head->next) {
            head->next->prev = next;
        }
        head->next = next;
    }

    return next;
}


node *node_pop(node *head) {
    if (head == NULL) {
        return head;
    }

    if (head->prev) {
        head->prev->next = head->next;
    }
    if (head->next) {
        head->next->prev = head->prev;
    }

    node *next = head->next;
    free(head);

    return next;
}


node *node_init(int n) {
    node *tmp = NULL, *first_node = tmp;

    for (int key = 1; key <= n; ++key) {
        tmp = node_push(tmp, key);
        if (!first_node) {
            first_node = tmp;
        }
    }

    return first_node;
}


void node_print(void *stream, node *head) {
    node *tmp = head;

    while (tmp) {
        fprintf(stream, "%d ", tmp->key);
        tmp = tmp->next;
    }
}


void node_delete(node *head) {
    node *tmp = head;

    while (tmp) {
        tmp = node_pop(tmp);
    }
}


node *node_process(void *stream, node *list, int n) {
    node *adr[n + 1], *tmp = list;

    for (int i = 1; i <= n; ++i) {
        adr[i] = tmp;
        tmp = tmp->next;
    }

    int m;
    fscanf(stream, "%d", &m);

    int i, j;
    node *head = list;

    for (int k = 0; k < m; ++k) {
        fscanf(stream, "%d %d", &i, &j);

        if (adr[i]->prev == NULL) {
            continue;
        }

        if (adr[i]->prev) {
            adr[i]->prev->next = adr[j]->next;
        }

        if (adr[j]->next) {
            adr[j]->next->prev = adr[i]->prev;
        }

        head->prev = adr[j];
        adr[j]->next = head;

        head = adr[i];
        head->prev = NULL;
    }

    return head;
}


int main(void) {
    FILE *input = fopen("input.txt", "r");

    int n;
    fscanf(input, "%d", &n);

    node *list = node_process(input, node_init(n), n);

    fclose(input);

    FILE *output = fopen("output.txt", "w");
    node_print(output, list);
    fclose(output);

    node_delete(list);

    return 0;
}
