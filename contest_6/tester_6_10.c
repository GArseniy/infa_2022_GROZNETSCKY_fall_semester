#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int key;
    struct Node *prev, *next;
} Node;


Node *push(Node *head, int key) {
    Node *next = malloc(sizeof(Node));

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


Node *pop(Node *head) {
    if (head == NULL) {
        return head;
    }

    if (head->prev) {
        head->prev->next = head->next;
    }
    if (head->next) {
        head->next->prev = head->prev;
    }

    Node *next = head->next;
    free(head);

    return next;
}


Node *init(int n) {
    Node *tmp = NULL, *first_node = tmp;

    for (int key = 1; key <= n; ++key) {
        tmp = push(tmp, key);
        if (!first_node) {
            first_node = tmp;
        }
    }

    return first_node;
}


void print(void *stream, Node *head) {
    Node *tmp = head;

    while (tmp) {
        fprintf(stream, "%d ", tmp->key);
        tmp = tmp->next;
    }
}


void delete(Node *head) {
    Node *tmp = head;

    while (tmp) {
        tmp = pop(tmp);
    }
}


Node *process(void *stream, Node *list, int n) {
    Node *adr[n + 1], *tmp = list;

    for (int i = 1; i <= n; ++i) {
        adr[i] = tmp;
        tmp = tmp->next;
    }

    int m;
    fscanf(stream, "%d", &m);

    int i, j;
    Node *head = list;

    for (int k = 0; k < m; ++k) {
        fscanf(stream, "%d %d", &i, &j);

        if (adr[i]->prev == NULL || i == j) {
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


struct List {
    struct List *prev, *next;
    int val;
};


struct List *crRoot(int val, struct List *a[]) {
    struct List *root = (struct List *) malloc(sizeof(struct List));;
    root->val = 1;
    root->prev = NULL;
    struct List *cur = root;
    a[1] = root;
    for (int i = 2; i <= val; i++) {
        struct List *tmp = (struct List *) malloc(sizeof(struct List));;
        tmp->val = i;
        tmp->prev = cur;
        tmp->next = NULL;
        cur->next = tmp;
        cur = tmp;
        a[i] = cur;
    }
    return root;
}


void prListInFile(struct List *root, FILE *fOutput) {
    struct List *cur = root;
    while (cur) {
        fprintf(fOutput, "%d ", cur->val);
        cur = cur->next;
    }
}

struct List *sublistToBegin(struct List *from, struct List *to, struct List *root) {
    if (from->prev) {
        from->prev->next = to->next;
    } else {
        return root;
    }
    if (to->next) {
        to->next->prev = from->prev;
    }
    root->prev = to;
    to->next = root;
    from->prev = NULL;
    return from;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void make_test() {
    FILE *input = fopen("input.txt", "w");

    const int MOD = 15;
    int n = 1 + rand() % MOD, m = 1 + rand() % MOD;

    fprintf(input, "%d %d\n", n, m);

    for (int k = 0; k < m; ++k) {
        int i = 1 + rand() % n, j = 1 + rand() % n;
        while (i > j) {
            i = 1 + rand() % n, j = 1 + rand() % n;
        }
        fprintf(input, "%d %d\n", i, j);
    }

    fclose(input);
}


int correct_program(void) {
    FILE *fInput = fopen("input.txt", "r");
    FILE *fOutput = fopen("correct.txt", "w");

    int n, m;
    fscanf(fInput, "%d %d", &n, &m);

    struct List *a[n + 1];
    struct List *root = crRoot(n, a);

    for (int i = 0; i < m; ++i) {
        int from, to;
        fscanf(fInput, "%d %d", &from, &to);
        root = sublistToBegin(a[from], a[to], root);
    }

    prListInFile(root, fOutput);
    fclose(fInput);
    fclose(fOutput);

    struct List *tmp;
    for (int i = 0; i < n; ++i) {
        tmp = root;
        root = root->next;
        free(tmp);
    }

    return 0;
}


int program(void) {
    int n;

    FILE *input = fopen("input.txt", "r");
    fscanf(input, "%d", &n);

    Node *list = process(input, init(n), n);

    fclose(input);

    FILE *output = fopen("output.txt", "w");
    print(output, list);
    fclose(output);

    delete(list);

    return 0;
}


int is_correct_answer() {
    int v, cor_v;

    FILE *output = fopen("output.txt", "r");
    FILE *correct = fopen("correct.txt", "r");

    int t1, t2;

    while ((t1 = fscanf(output, "%d", &v)) == (t2 = fscanf(correct, "%d", &cor_v)) && t1 > 0) {
        if (v != cor_v) {
            return 0;
        }
    }

    fclose(output);
    fclose(correct);

    return t1 == t2;
}


int init_s() {
    FILE *output = fopen("output.txt", "w");
    FILE *correct = fopen("correct.txt", "w");

    fprintf(output, "1");
    fprintf(correct, "1");

    fclose(output);
    fclose(correct);

    return 0;
}


int main(void) {
    //init_s();

    if (1) {
        make_test();
        correct_program();
        program();
    }


    return 0;
}
