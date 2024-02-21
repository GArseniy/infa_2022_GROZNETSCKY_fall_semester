#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int key;
    struct Node *next;
} node;


void node_print(void *stream, node *head) {
    node *tmp = head;

    while (tmp) {
        fprintf(stream, "%d ", tmp->key);
        tmp = tmp->next;
    }
}


node *node_read(void *stream) {
    node *head = NULL;

    int key;
    while (fscanf(stream, "%d", &key) > 0) {
        node *new = malloc(sizeof(node));

        new->key = key;
        new->next = head;

        head = new;
    }

    return head;
}


void node_delete(node *head) {
    while (head) {
        node *next = head->next;
        free(head);

        head = next;
    }
}


node *node_merge_sorted(node *left, node *right) {
    if (left == NULL) {
        return right;
    } else if (right == NULL) {
        return left;
    }

    node *result = NULL;

    if (left->key <= right->key) {
        result = left;
        result->next = node_merge_sorted(left->next, right);
    } else {
        result = right;
        result->next = node_merge_sorted(left, right->next);
    }

    return result;
}


void node_split(node *head, node **left, node **right) {
    if (head == NULL || head->next == NULL) {
        *left = head;
        *right = NULL;

        return;
    }

    node *slow = head;
    node *fast = head->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *left = head;
    *right = slow->next;
    slow->next = NULL;
}

void node_merge_sort(node **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    node *left;
    node *right;

    node_split(*head, &left, &right);

    node_merge_sort(&left);
    node_merge_sort(&right);

    *head = node_merge_sorted(left, right);
}


int main(void) {
    FILE *input = fopen("input.txt", "r");
    node *list = node_read(input);
    fclose(input);

    node_merge_sort(&list);

    FILE *output = fopen("output.txt", "w");
    node_print(output, list);
    fclose(output);

    node_delete(list);

    return 0;
}
