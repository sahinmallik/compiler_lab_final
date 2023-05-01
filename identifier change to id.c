#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_IDENT_LEN 100

int is_identifier_char(char c) {
    return isalnum(c) || c == '_';
}

int is_pure_number(const char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isdigit(s[i])) {
            return 0;
        }
    }
    return 1;
}

int main() {
    FILE *input_file, *output_file;
    char ident[MAX_IDENT_LEN + 1];
    char c;
    int i = 0;

    // Open input file for reading
    input_file = fopen("input.c", "r");
    if (input_file == NULL) {
        printf("Error: Cannot open input file\n");
        exit(1);
    }

    // Open output file for writing
    output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Error: Cannot open output file\n");
        exit(1);
    }

    // Read input file character by character
    while ((c = fgetc(input_file)) != EOF) {
        if (is_identifier_char(c)) {
            ident[i++] = c;
            if (i >= MAX_IDENT_LEN) {
                printf("Error: Identifier too long\n");
                exit(1);
            }
        } else {
            // Write current identifier (if any) to output file
            if (i > 0) {
                ident[i] = '\0';
                if (is_pure_number(ident)) {
                    fprintf(output_file, "%s", ident);
                } else {
                    fprintf(output_file, "id");
                }
                i = 0;
            }

            // Write non-identifier character to output file
            fputc(c, output_file);
        }
    }

    // Write last identifier (if any) to output file
    if (i > 0) {
        ident[i] = '\0';
        if (is_pure_number(ident)) {
            fprintf(output_file, "%s", ident);
        } else {
            fprintf(output_file, "id");
        }
    }

    // Close files
    fclose(input_file);
    fclose(output_file);

    return 0;
}