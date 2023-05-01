#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int main() {
    FILE *input_file, *output_file;
    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    char operators[] = "+-*/<>=!";
    char *operator_names[] = {"+", "-", "*", "/", "<", ">", "<=", ">=", "!"};
    int i, j;

    // Open the input file
    input_file = fopen("input.c", "r");
    if (input_file == NULL) {
        printf("Error: Could not open input file\n");
        exit(1);
    }

    // Open the output file
    output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Error: Could not open output file\n");
        exit(1);
    }

    // Read the file line by line
    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
        line_number++;

        // Find operators in the line
        for (i = 0; i < strlen(line); i++) {
            for (j = 0; j < strlen(operators); j++) {
                if (line[i] == operators[j]) {
                    fprintf(output_file, "Line %d: %s\n", line_number, operator_names[j]);
                    break;
                }
            }
        }
    }

    // Close the files
    fclose(input_file);
    fclose(output_file);

    printf("Output file written successfully\n");

    return 0;
}
