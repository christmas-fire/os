// main.c
#include <stdio.h>
#include "list.h"

int main() {
    Node* head = NULL;

    // Создаем первый элемент
    head = create_list(10);
    printf("Добавлено: 10\n");

    // Добавляем еще элементы
    add_to_end(head, 20);
    add_to_end(head, 30);
    add_to_end(head, 40);

    // Выводим список
    print_list(head);

    // Освобождаем память
    free_list(head);

    printf("Память освобождена.\n");

    return 0;
}