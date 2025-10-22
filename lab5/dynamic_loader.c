#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>      
#include <unistd.h>     
#include <string.h>
#include <sys/types.h> 

// Типы для указателей на функции
typedef void* (*create_list_func)(int);
typedef void* (*add_to_end_func)(void*, int);
typedef void (*print_list_func)(void*);
typedef void (*free_list_func)(void*);

int main() {
    pid_t pid = getpid();
    printf("PID процесса: %d\n", pid);

    printf("Библиотека ещё не загружена. Проверьте /proc/%d/maps\n", pid);
    printf("Нажмите Enter, чтобы загрузить библиотеку...\n");
    getchar();

    // Путь к библиотеке
    const char* lib_path = "./liblist.so";

    // Открываем библиотеку
    void* handle = dlopen(lib_path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Ошибка загрузки библиотеки: %s\n", dlerror());
        exit(1);
    }
    printf("Библиотека %s успешно загружена.\n", lib_path);

    printf("Библиотека загружена. Проверьте /proc/%d/maps\n", pid);
    printf("Нажмите Enter, чтобы продолжить...\n");
    getchar();

    // Получаем указатели на функции
    create_list_func create_list = dlsym(handle, "create_list");
    add_to_end_func add_to_end = dlsym(handle, "add_to_end");
    print_list_func print_list = dlsym(handle, "print_list");
    free_list_func free_list = dlsym(handle, "free_list");

    // Проверяем ошибки при получении символов
    char* error;
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "Ошибка получения символа: %s\n", error);
        dlclose(handle);
        exit(1);
    }

    // Используем функции
    printf("Создаём список...\n");
    void* head = create_list(10);
    if (!head) {
        fprintf(stderr, "Ошибка создания списка\n");
        dlclose(handle);
        exit(1);
    }

    printf("Добавляем элементы...\n");
    add_to_end(head, 20);
    add_to_end(head, 30);

    printf("Выводим список:\n");
    print_list(head);

    printf("Освобождаем память...\n");
    free_list(head);

    printf("Работа с библиотекой завершена, но она ещё загружена. Проверьте /proc/%d/maps\n", pid);
    printf("Нажмите Enter, чтобы выгрузить библиотеку...\n");
    getchar();

    // Выгружаем библиотеку
    printf("Выгружаем библиотеку...\n");
    dlclose(handle);
    printf("Библиотека успешно выгружена.\n");

    printf("Библиотека выгружена. Проверьте /proc/%d/maps\n", pid);
    printf("Нажмите Enter для завершения программы...\n");
    getchar();

    return 0;
}
