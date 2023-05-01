#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int main() {
    FILE *input_file, *output_file;
    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    int is_comment = 0;

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

        // Check if the line is a comment
        if (strstr(line, "//") != NULL) {
            is_comment = 1;
        }

        // Check if the line starts a multiline comment
        if (strstr(line, "/*") != NULL) {
            is_comment = 1;
        }

        // Write the line to the output file if it's not a comment
        if (!is_comment) {
            fprintf(output_file, "%s", line);
        }

        // Check if the line ends a multiline comment
        if (strstr(line, "*/") != NULL) {
            is_comment = 0;
        }

        // Reset the comment flag for the next line
        if (strchr(line, '\n') != NULL) {
            is_comment = 0;
        }
    }

    // Close the files
    fclose(input_file);
    fclose(output_file);

    printf("Output file written successfully\n");

    return 0;
}
