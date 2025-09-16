// list.c
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

Node* create_list(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return NULL;
    }
    node->data = value;
    node->next = NULL;
    return node;
}

Node* add_to_end(Node* head, int value) {
    if (!head) {
        return create_list(value);
    }

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = (Node*)malloc(sizeof(Node));
    if (!current->next) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return head;
    }
    current->next->data = value;
    current->next->next = NULL;

    return head;
}

void print_list(Node* head) {
    printf("Список: ");
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}