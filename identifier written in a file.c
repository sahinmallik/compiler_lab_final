#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_IDENTIFIER_LEN 50
#define MAX_NUM_IDENTIFIERS 1000
#define MAX_FILENAME_LEN 100

int main() {
    char filename[MAX_FILENAME_LEN] = "input.c";

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Unable to open file!");
        return 0;
    }

    char identifiers[MAX_NUM_IDENTIFIERS][MAX_IDENTIFIER_LEN];
    int line_numbers[MAX_NUM_IDENTIFIERS];
    int num_identifiers = 0;

    int line_number = 1;
    char c = fgetc(fp);
    while (c != EOF) {
        if (c == '/') {
            char next_c = fgetc(fp);
            if (next_c == '/') { // Single-line comment, ignore rest of the line
                while (c != '\n') {
                    c = fgetc(fp);
                }
                line_number++;
            } else if (next_c == '*') { // Multi-line comment, ignore until end of comment
                c = fgetc(fp);
                next_c = fgetc(fp);
                while (c != '*' || next_c != '/') {
                    c = next_c;
                    next_c = fgetc(fp);
                    if (c == '\n') {
                        line_number++;
                    }
                }
                c = fgetc(fp);
            } else { // Not a comment
                ungetc(next_c, fp);
            }
        } else if (isalpha(c) || c == '_') {
            char identifier[MAX_IDENTIFIER_LEN] = {0};
            int i = 0;
            while (isalnum(c) || c == '_') {
                identifier[i++] = c;
                c = fgetc(fp);
            }
            int j;
            for (j = 0; j < num_identifiers; j++) {
                if (strcmp(identifiers[j], identifier) == 0 && line_numbers[j] == line_number) {
                    break;
                }
            }
            if (j == num_identifiers) {
                strcpy(identifiers[num_identifiers], identifier);
                line_numbers[num_identifiers] = line_number;
                num_identifiers++;
            }
        } else if (c == '\n') {
            line_number++;
        }
        c = fgetc(fp);
    }
    fclose(fp);

    // Write the identifiers to a file with their line numbers
    char output_filename[MAX_FILENAME_LEN] = "output.txt";

    FILE* output_fp = fopen(output_filename, "w");
    if (output_fp == NULL) {
        printf("Unable to create output file!");
        return 0;
    }

    fprintf(output_fp, "Identifiers:\n");
    fprintf(output_fp, "%-20s %s\n", "Identifier", "Line Number");
    fprintf(output_fp, "-----------------------------------\n");
    for (int i = 0; i < num_identifiers; i++) {
        fprintf(output_fp, "%-20s %d\n", identifiers[i], line_numbers[i]);
    }

    fclose(output_fp);
    printf("Identifiers written to output.txt\n");
    return 0;
}
