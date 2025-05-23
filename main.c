#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void create_file(char *path) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        printf("Ошибка при создании файла\n");
        return;
    }
    fclose(file);
    printf("Файл создан: %s\n", path);
}

void delete_file(char *path) {
    if (remove(path) {
        printf("Ошибка при удалении файла\n");
        return;
    }
    printf("Файл удалён: %s\n", path);
}

void edit_file(char *path) {
    printf("Введите текст для файла (Ctrl+D для завершения):\n");
    
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return;
    }
    
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        fputs(buffer, file);
    }
    
    fclose(file);
    printf("Файл изменён: %s\n", path);
}

void view_file(char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return;
    }
    
    char buffer[256];
    printf("Содержимое файла %s:\n", path);
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    
    fclose(file);
}

int main() {
    printf("Добро пожаловать в SimpleFS!\n");
    printf("Доступные команды: создать, удалить, изменить, посмотреть\n");
    
    char input[256];
    char command[50];
    char path[200];
    
    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        
        // Удаляем символ новой строки
        input[strcspn(input, "\n")] = 0;
        
        int parsed = sscanf(input, "%49s %199[^\n]", command, path);
        
        if (parsed == 0) continue;
        
        if (strcmp(command, "создать") == 0 && parsed == 2) {
            create_file(path);
        } else if (strcmp(command, "удалить") == 0 && parsed == 2) {
            delete_file(path);
        } else if (strcmp(command, "изменить") == 0 && parsed == 2) {
            edit_file(path);
        } else if (strcmp(command, "посмотреть") == 0 && parsed == 2) {
            view_file(path);
        } else {
            printf("Неизвестная команда или неверные параметры\n");
        }
    }
    
    return 0;
}
