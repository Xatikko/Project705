#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>

FILE* open_or_create_fs(const char* filename);
char* view_file(const char* filename);
int delete_file(const char* filename);
int create_file(const char* filename, const char* content);
int modify_file(const char* filename, const char* new_content);

#endif
