#include "global.h"

size_t flength(FILE *file) {
	fpos_t fpos;
	fgetpos(file, &fpos);
	fseek(file, 0, SEEK_END);
	size_t n = ftell(file);
	fsetpos(file, &fpos);
	return n;
}

int split_file_by_amount(FILE* source, char* original_name, int amount) {
	size_t length = flength(source);
	size_t each_fsize = length / amount;

	// Calculate size
	size_t n = length - each_fsize * amount;

	// Use For-Loop to write files
	for (int i = 0; i < amount; i++) {
		// New filename
		size_t original_name_length = strlen(original_name) + 1;
		size_t name_length = original_name_length + 12 + 1;
		char newfn[name_length];
		memset(newfn, 0, name_length);
		strcpy(newfn, original_name);
		strcat(newfn, ".");
		char number[11] = { '\0' };
		sprintf(number, "%d", i + 1);
		strcat(newfn, number);

		// Open new file
		FILE* newfile = fopen(newfn, "wb");
		if (newfile == NULL) return -2;

		// Calculate size to read
		size_t size_to_read = each_fsize;
		if (n > 0) {
			size_to_read++;
			n--;
		}

		// Create a memory heap to store data
		void* content = NULL;
		content = malloc(size_to_read);
		if (content == NULL) return -1;
		fread(content, 1, size_to_read, source);

		fwrite(content, 1, size_to_read, newfile);

		// Close file & free memory used
		fclose(newfile);
		free(content);
	}

	return 0;
}

int split_file_by_size(FILE* source, char* original_name, size_t size) {
	size_t length = flength(source);
	size_t amount = length / size;
	if (length % size != 0) amount++;

	// Use For-Loop to write files
	for (int i = 0; i < amount; i++) {
		// New filename
		size_t original_name_length = strlen(original_name) + 1;
		size_t name_length = original_name_length + 12 + 1;
		char newfn[name_length];
		memset(newfn, 0, name_length);
		strcpy(newfn, original_name);
		strcat(newfn, ".");
		char number[11] = { '\0' };
		sprintf(number, "%d", i + 1);
		strcat(newfn, number);

		// Open new file
		FILE* newfile = fopen(newfn, "wb");
		if (newfile == NULL) return -2;

		// Calculate size to read
		size_t size_to_read = size;
		if (length - ftell(source) < size) {
			size_to_read = length - ftell(source);
		}

		// Create a memory heap to store data
		void* content = NULL;
		content = malloc(size_to_read);
		if (content == NULL) return -1;
		fread(content, 1, size_to_read, source);

		fwrite(content, 1, size_to_read, newfile);

		// Close file & free memory used
		fclose(newfile);
		free(content);
	}

	return 0;
}

int merge_file(char* name) {
	size_t name_length = strlen(name) + 1;
	char first_filename[name_length + 2];
	strcpy(first_filename, name);
	strcat(first_filename, ".1");

	FILE* first_file = fopen(first_filename, "rb");
	if (!first_file) return -1;

	FILE* original_file = fopen(name, "wb");
	if (!original_file) return -3;

	size_t length = flength(first_file);

	void* buffer = malloc(length);
	if (buffer == NULL) return -2;
	fread(buffer, 1, length, first_file);
	fwrite(buffer, 1, length, original_file);
	free(buffer);
	fclose(first_file);

	size_t file_count = 2;

	while (1) {
		char filename[name_length + 12];
		strcpy(filename, name);
		char number[11] = { '\0' };
		sprintf(number, "%d", (int)file_count);
		strcat(filename, ".");
		strcat(filename, number);

		FILE* file = fopen(filename, "rb");
		if (file == NULL) break;

		size_t file_length = flength(file);

		void* buffer = malloc(length);
		if (buffer == NULL) return -2;
		fread(buffer, 1, file_length, file);
		fwrite(buffer, 1, file_length, original_file);
		free(buffer);
		fclose(file);

		file_count++;
	}

	fclose(original_file);
	return 0;
}

