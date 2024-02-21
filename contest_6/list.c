#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int key;
    struct Node *next;
} node;


node *push(node *head, int key) {
    node *next = malloc(sizeof(node));

    next->key = key;
    next->next = NULL;

    if (head) {
        head->next = next;
    }

    return next;
}


node *read(void *stream, node *head) {
    node *tmp = head, *first_node = head;
    int key;

    while (fscanf(stream, "%d", &key), key) {
        tmp = push(tmp, key);
        if (!first_node) {
            first_node = tmp;
        }
    }

    return first_node;
}


node *merge(node *head1, node *head2) {
    node *list1 = head1;
    node *list2 = head2;

    if (list2->key < list1->key) {
        node *tmp = list2;
        list2 = list1;
        list1 = tmp;
    }

    node *ret = list1;

    node *prev = list1;

    while (list1->next && list2->next) {
        if (list1->key <= list2->key) {
            prev = list1;
            list1 = list1->next;
        } else {
            node *tmp = list2->next;

            prev->next = list2;
            prev = prev->next;
            list2->next = list1;

            list2 = tmp;
        }
    }

    if (!list1->next) {
        while (list2 && list1->key >= list2->key) {
            node *tmp = list2->next;

            prev->next = list2;
            prev = prev->next;
            list2->next = list1;

            list2 = tmp;
        }

        list1->next = list2;
    } else {
        while (1)
            if (list1->key >= list2->key) {
                prev->next = list2;
                list2->next = list1;
                break;
            } else {
                prev = list1;
                list1 = list1->next;
            }
    }


    return ret;
}


void print(node *head) {
    node *tmp = head;

    while (tmp) {
        printf("%d ", tmp->key);
        tmp = tmp->next;
    }
}


int main(void) {
    FILE *input = fopen("input.txt", "r");
    node *head1 = read(input, NULL), *head2 = read(input, NULL);
    fclose(input);

    print(merge(head1, head2));

    return 0;
}
