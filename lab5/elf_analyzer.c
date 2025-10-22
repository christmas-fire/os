#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <string.h>

// Функция для вывода всех секций с их именами
void print_sections(Elf64_Ehdr* ehdr, Elf64_Shdr* shdr, char* shstrtab) {
    printf("Список секций:\n");
    for (int i = 0; i < ehdr->e_shnum; i++) {
        if (shdr[i].sh_name != 0 && shstrtab != NULL) {
            printf("  [%d] %s\n", i, &shstrtab[shdr[i].sh_name]);
        } else {
            printf("  [%d] <без имени>\n", i);
        }
    }
}

// Функция для вывода экспортируемых функций
void print_exported_functions(Elf64_Ehdr* ehdr, Elf64_Shdr* shdr, char* shstrtab, int fd) {
    // Находим секции .dynsym и .dynstr по имени
    Elf64_Shdr* dynsym_shdr = NULL;
    Elf64_Shdr* dynstr_shdr = NULL;
    
    for (int i = 0; i < ehdr->e_shnum; i++) {
        if (shdr[i].sh_name != 0 && shstrtab != NULL) {
            char* name = &shstrtab[shdr[i].sh_name];
            if (strcmp(name, ".dynsym") == 0) {
                dynsym_shdr = &shdr[i];
            } else if (strcmp(name, ".dynstr") == 0) {
                dynstr_shdr = &shdr[i];
            }
        }
    }
    
    if (!dynsym_shdr || !dynstr_shdr) {
        fprintf(stderr, "Ошибка: не найдены .dynsym или .dynstr\n");
        return;
    }
    
    // Читаем таблицу символов
    Elf64_Sym* symtab = malloc(dynsym_shdr->sh_size);
    if (!symtab) {
        perror("malloc");
        return;
    }
    
    if (lseek(fd, dynsym_shdr->sh_offset, SEEK_SET) == -1) {
        perror("lseek dynsym");
        free(symtab);
        return;
    }
    
    if (read(fd, symtab, dynsym_shdr->sh_size) != dynsym_shdr->sh_size) {
        fprintf(stderr, "Ошибка чтения .dynsym\n");
        free(symtab);
        return;
    }
    
    // Читаем строковую таблицу
    char* strtab = malloc(dynstr_shdr->sh_size);
    if (!strtab) {
        perror("malloc strtab");
        free(symtab);
        return;
    }
    
    if (lseek(fd, dynstr_shdr->sh_offset, SEEK_SET) == -1) {
        perror("lseek dynstr");
        free(symtab);
        free(strtab);
        return;
    }
    
    if (read(fd, strtab, dynstr_shdr->sh_size) != dynstr_shdr->sh_size) {
        fprintf(stderr, "Ошибка чтения .dynstr\n");
        free(symtab);
        free(strtab);
        return;
    }
    
    printf("\nЭкспортируемые функции:\n");
    int sym_count = dynsym_shdr->sh_size / sizeof(Elf64_Sym);
    for (int i = 0; i < sym_count; i++) {
        if (symtab[i].st_name == 0) continue;
        if (ELF64_ST_BIND(symtab[i].st_info) != STB_GLOBAL) continue;
        if (ELF64_ST_TYPE(symtab[i].st_info) != STT_FUNC) continue;
        // Фильтр: только определенные в этой библиотеке
        if (symtab[i].st_shndx == SHN_UNDEF) continue;
        
        printf("  %s\n", &strtab[symtab[i].st_name]);
    }
    
    free(symtab);
    free(strtab);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <lib>.so\n", argv[0]);
        exit(1);
    }
    
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    
    // Чтение заголовка ELF
    Elf64_Ehdr ehdr;
    if (read(fd, &ehdr, sizeof(ehdr)) != sizeof(ehdr)) {
        fprintf(stderr, "Ошибка чтения заголовка ELF\n");
        close(fd);
        exit(1);
    }
    
    // Проверка магического числа
    if (ehdr.e_ident[EI_MAG0] != ELFMAG0 ||
        ehdr.e_ident[EI_MAG1] != ELFMAG1 ||
        ehdr.e_ident[EI_MAG2] != ELFMAG2 ||
        ehdr.e_ident[EI_MAG3] != ELFMAG3) {
        fprintf(stderr, "Не является ELF-файлом\n");
        close(fd);
        exit(1);
    }
    
    // Чтение таблицы секций
    if (lseek(fd, ehdr.e_shoff, SEEK_SET) == -1) {
        perror("lseek shoff");
        close(fd);
        exit(1);
    }
    
    Elf64_Shdr* shdr = malloc(ehdr.e_shnum * sizeof(Elf64_Shdr));
    if (!shdr) {
        perror("malloc shdr");
        close(fd);
        exit(1);
    }
    
    if (read(fd, shdr, ehdr.e_shnum * sizeof(Elf64_Shdr)) != ehdr.e_shnum * sizeof(Elf64_Shdr)) {
        fprintf(stderr, "Ошибка чтения таблицы секций\n");
        free(shdr);
        close(fd);
        exit(1);
    }
    
    char* shstrtab = NULL;
    if (ehdr.e_shstrndx < ehdr.e_shnum) {
        Elf64_Shdr* shstr_shdr = &shdr[ehdr.e_shstrndx];
        shstrtab = malloc(shstr_shdr->sh_size);
        if (shstrtab) {
            if (lseek(fd, shstr_shdr->sh_offset, SEEK_SET) != -1) {
                if (read(fd, shstrtab, shstr_shdr->sh_size) != shstr_shdr->sh_size) {
                    free(shstrtab);
                    shstrtab = NULL;
                }
            } else {
                free(shstrtab);
                shstrtab = NULL;
            }
        }
    }
    
    // Вывод списка секций
    print_sections(&ehdr, shdr, shstrtab);
    
    // Вывод экспортируемых функций
    print_exported_functions(&ehdr, shdr, shstrtab, fd);
    
    // Очистка
    if (shstrtab) free(shstrtab);
    free(shdr);
    close(fd);
    
    return 0;
}
