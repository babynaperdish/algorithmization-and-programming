#define _CRT_SECURE_NO_WARNINGS
#define BUFFER_SIZE 5    

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void remove_element(char arr[], int* size, int index) {
	if (index < 0 || index >= *size) {
		printf("Wrong index.\n");
		return;
	}
	for (int i = index; i < *size - 1; i++) {
		arr[i] = arr[i + 1];
	}
	(*size)--;
}

void add_element(char arr[], int* size, int index, char element) {
	if (index < 0 || index >= *size) {
		printf("Wrong index.\n");
		return;
	}
	for (int i = *size; i > index; i--) {
		arr[i] = arr[i - 1];
	}
	arr[index] = element;
	(*size)++;
}

// snake_case to smallCamelCase
void sc_to_scc(char* s) {
	int length = strlen(s);
	for (int i = 0; i < length; i++) {
		if (s[i] == '_') {
			if (i + 1 < length){
				s[i + 1] = toupper(s[i + 1]);
			}
			remove_element(s, &length, i);
			i--;
		}
	}
};

// smallCamelCase to snake_case
void scc_to_sc(char* s) {
	int length = strlen(s);
	for (int i = 0; i < length; i++) {
		if (isupper(s[i])) {
			s[i] = tolower(s[i]);
			add_element(s, &length, i, '_');
			i++;
		}
	}
};

void standard_verification(char* s) {
	int flag_upper = 0;
	int flag_underscore = 0;
	int length = strlen(s);

	for (int i = 0; i < length; i++) {
		if (isupper(s[i])) {
			flag_upper = 1;
		}
		if (s[i] == '_') {
			flag_underscore = 1;
		}
	}

	if (flag_upper == 1 && flag_underscore == 1) {
		strcpy(s, "error");
	}
	if (flag_upper == 0 && flag_underscore == 1) {
		sc_to_scc(s); 
	}
	if (flag_upper == 1 && flag_underscore == 0) {
		scc_to_sc(s); 
	}
};

int main() {
	FILE* f1 = fopen("startfile.txt", "rt");
	FILE* f2 = fopen("endfile.txt", "wt");
	if (!f1) {
		perror("Unable to open file");
		fclose(f1);
		return 1;
	}
	if (!f2) {
		perror("Unable to open file");
		fclose(f2);
		return 1;
	}

	size_t buffer_size = BUFFER_SIZE;
	size_t len = 0;
	char* buffer = malloc(BUFFER_SIZE);
	int flag = 0;
	if (!buffer) {
		perror("Unable to allocate memory");
		fclose(f1);
		return 1;
	}

	if (f1) {
		int n = (fgets(buffer, 5, f1));
		int k = 0;
		while (fgets(buffer, buffer_size, f1)) {
			len = strlen(buffer);
			if (buffer[len - 1] == '\n') {
				buffer[len - 1] = '\0';
				len--;
			}
			if (len == buffer_size - 1 && buffer[len - 1] != '\n') {
				buffer_size *= 2;
				char* temp = realloc(buffer, buffer_size);
				if (!temp) {
					perror("Unable to reallocate memory");
					free(buffer);
					fclose(f1);
					return 1;
				}
				buffer = temp;
				fgets(buffer + len, buffer_size - len, f1);
			}
			standard_verification(buffer);
			k += 1;
			fputs(buffer, f2);
			fputs("\n", f2);
			printf("%s\n", buffer);
			if (k >= n) {
				break;
				while (fgets(buffer, buffer_size, f1)) {
					fputs(buffer, f2);
				}
			}
		}
		if (n > k) {
			fclose(f2);
			FILE* f2 = fopen("endfile.txt", "wt");
			fputs("Not enough strings.", f2);
			flag = 1;
		}
	}
	if (!flag) {
		free(buffer);
	}
	fclose(f1);
	fclose(f2);
	return 0;
}