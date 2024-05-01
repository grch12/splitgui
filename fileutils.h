#ifndef FILEUTILS_H
#define FILEUTILS_H

#include "global.h"

size_t flength(FILE* file);

int split_file_by_amount(FILE* source, char* original_name, int amount);
int split_file_by_size(FILE* source, char* original_name, size_t size);

int merge_file(char* name);

#endif

