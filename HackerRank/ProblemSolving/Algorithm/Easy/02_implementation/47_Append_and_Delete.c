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

char* appendAndDelete(char* s, char* t, int k) {
    int sLen = strlen(s),
        tLen = strlen(t);
        
    if (sLen + tLen <= k) return "Yes";
    
    int numberOfMatch = 0,
        i = 0;
    
    while (s[i] == t[i++]) {
        numberOfMatch += 2;
    }
    
    k -= (sLen + tLen - numberOfMatch);
    
    if (k >= 0 && !(k % 2)) return "Yes";
    
    return "No";
}

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* t = readline();

    char* k_endptr;
    char* k_str = readline();
    int k = strtol(k_str, &k_endptr, 10);

    if (k_endptr == k_str || *k_endptr != '\0') { exit(EXIT_FAILURE); }

    char* result = appendAndDelete(s, t, k);

    fprintf(fptr, "%s\n", result);

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