#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

int campfunc(const void *a, const void *b) {
  return *(int*)a - *(int*)b;
}

int getMin(int len, int *arr) {
    int min = arr[0];
    
    for (int i = 1; i < len; i++)
        if (min > arr[i]) min = arr[i];
    
    return min;
}

int* closestNumbers(int arr_count, int* arr, int* result_count) {

    qsort(arr, arr_count, sizeof(int), campfunc);    
    int *pairsDeference = calloc(arr_count - 1, sizeof(int));

    for (int i = 0; i < arr_count - 1; i++) pairsDeference[i] = arr[i + 1] - arr[i];
    
    int minDef = getMin(arr_count - 1, pairsDeference);
    
    int len = 0;
    int *result = calloc(10000, sizeof(int));
    
    for (int i = 0, j = 0; i < arr_count - 1; i++) {
        if (arr[i + 1] - arr[i] == minDef) {
            len += 2;
            result[j] = arr[i];
            result[j + 1] = arr[i + 1];
            j += 2;
        }
    }
    
    *result_count = len;
    
    return result;
}

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* n_endptr;
    char* n_str = readline();
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** arr_temp = split_string(readline());

    int* arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        char* arr_item_endptr;
        char* arr_item_str = *(arr_temp + i);
        int arr_item = strtol(arr_item_str, &arr_item_endptr, 10);

        if (arr_item_endptr == arr_item_str || *arr_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(arr + i) = arr_item;
    }

    int arr_count = n;

    int result_count;
    int* result = closestNumbers(arr_count, arr, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, " ");
        }
    }

    fprintf(fptr, "\n");

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}