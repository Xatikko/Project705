#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CONTENT_SIZE 4096
#define DELIMITER "---\n"

// Вспомогательная функция для чтения всего файла в строку
static char* read_entire_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(length + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);

    return buffer;
}

// Вспомогательная функция для записи в файл
static bool write_to_file(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (!file) return false;

    fprintf(file, "%s", content);
    fclose(file);
    return true;
}

// 1. Открыть/создать файл файловой системы
FILE* open_or_create_fs(const char* filename) {
    FILE* file = fopen(filename, "a+"); // Открыть для чтения и добавления, создаст если нет
    return file;
}

// 2. Просмотреть содержимое файла
char* view_file(const char* filename) {
    char* fs_content = read_entire_file(filename);
    if (!fs_content) return NULL;

    // Находим начало нужного файла
    char* file_start = strstr(fs_content, filename);
    if (!file_start) {
        free(fs_content);
        return NULL;
    }

    // Пропускаем само имя файла и перенос строки
    file_start += strlen(filename) + 1;

    // Находим конец содержимого (разделитель или конец файла)
    char* file_end = strstr(file_start, DELIMITER);
    if (!file_end) file_end = fs_content + strlen(fs_content);

    // Копируем только нужную часть
    size_t content_length = file_end - file_start;
    char* content = malloc(content_length + 1);
    if (!content) {
        free(fs_content);
        return NULL;
    }

    strncpy(content, file_start, content_length);
    content[content_length] = '\0';

    free(fs_content);
    return content;
}

// 3. Удалить файл из файловой системы
int delete_file(const char* filename) {
    char* fs_content = read_entire_file(filename);
    if (!fs_content) return -1;

    char* file_start = strstr(fs_content, filename);
    if (!file_start) {
        free(fs_content);
        return -1;
    }

    // Находим начало следующего файла (или конец)
    char* next_file = strstr(file_start, DELIMITER);
    if (!next_file) {
        // Это последний файл, просто обрезаем
        *file_start = '\0';
    } else {
        // Копируем оставшуюся часть
        memmove(file_start, next_file, strlen(next_file) + 1);
    }

    bool success = write_to_file(filename, fs_content);
    free(fs_content);
    return success ? 0 : -1;
}

// 4. Создать новый файл в файловой системе
int create_file(const char* filename, const char* content) {
    FILE* file = fopen(filename, "a+");
    if (!file) return -1;

    // Проверяем, существует ли уже файл с таким именем
    fseek(file, 0, SEEK_SET);
    char buffer[MAX_CONTENT_SIZE];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strncmp(buffer, filename, strlen(filename)) == 0 && 
            buffer[strlen(filename)] == '\n') {
            fclose(file);
            return -1; // Файл уже существует
        }
    }

    // Добавляем новый файл
    fprintf(file, "%s\n%s%s", filename, content, DELIMITER);
    fclose(file);
    return 0;
}

// 5. Обновить содержимое файла
int modify_file(const char* filename, const char* new_content) {
    // Сначала удаляем старый файл
    if (delete_file(filename) != 0) {
        return -1;
    }

    // Затем создаем с новым содержимым
    return create_file(filename, new_content);
}
