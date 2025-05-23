#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"

#define MAX_FILENAME_LENGTH 255

// Компиляция: gcc main.c filesystem.c -o fs_program
int main()
{
    while (1) {
        int file_action;
        printf("\nВыберите действие с файлом:\n"
               "1 - Открыть/Создать файл\n"
               "2 - Прочитать файл\n"
               "3 - Удалить файл\n"
               "4 - Добавить новый файл\n"
               "5 - Обновить файл\n"
               "0 - Выйти из программы\n"
               "> ");
        scanf("%d", &file_action);
        
        // Очистка буфера ввода
        while(getchar() != '\n');
        
        if (file_action == 0) {
            printf("Выход из программы...\n");
            break;
        }
        
        char filename[MAX_FILENAME_LENGTH];
        printf("Введите имя файла: ");
        fgets(filename, MAX_FILENAME_LENGTH, stdin);
        filename[strcspn(filename, "\n")] = '\0'; // Удаление символа новой строки
        
        FILE* fp = NULL;
        char* result = NULL;
        char content[1024];
        
        switch(file_action) {
            case 1:
                fp = open_or_create_fs(filename);
                if (fp) {
                    printf("Файл '%s' успешно открыт/создан\n", filename);
                    fclose(fp);
                } else {
                    printf("Ошибка при работе с файлом '%s'\n", filename);
                }
                break;
                
            case 2:
                result = view_file(filename);
                if (result) {
                    printf("\nСодержимое файла '%s':\n%s\n", filename, result);
                    free(result);
                } else {
                    printf("Файл '%s' не найден или ошибка чтения\n", filename);
                }
                break;
                
            case 3:
                if (delete_file(filename) == 0) {
                    printf("Файл '%s' успешно удален\n", filename);
                } else {
                    printf("Ошибка при удалении файла '%s'\n", filename);
                }
                break;
                
            case 4:
                printf("Введите содержимое файла (окончание ввода - Ctrl+D):\n");
                fgets(content, sizeof(content), stdin;
                content[strcspn(content, "\n")] = '\0';
                
                if (create_file(filename, content) {
                    printf("Файл '%s' успешно создан\n", filename);
                } else {
                    printf("Ошибка при создании файла '%s'\n", filename);
                }
                break;
                
            case 5:
                printf("Введите новое содержимое файла (окончание ввода - Ctrl+D):\n");
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = '\0';
                
                if (modify_file(filename, content) {
                    printf("Файл '%s' успешно обновлен\n", filename);
                } else {
                    printf("Ошибка при обновлении файла '%s'\n", filename);
                }
                break;
                
            default:
                printf("Ошибка: неизвестное действие\n");
        }
    }

    return 0;
}
