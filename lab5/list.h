// list.h
#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Функции библиотеки
Node* create_list(int value);
Node* add_to_end(Node* head, int value);
void print_list(Node* head);
void free_list(Node* head);

#endif