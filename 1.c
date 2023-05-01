#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_IDENTIFIERS 100
#define MAX_LENGTH 100

int main()
{
    char filename[MAX_LENGTH];
    char identifiers[MAX_IDENTIFIERS][MAX_LENGTH];
    int identifier_count = 0;

    printf("Enter the filename to read from: ");
    scanf("%s", filename);

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return 1;
    }

    char word[MAX_LENGTH];
    char reversed_word[MAX_LENGTH];
    char symbol_table[MAX_IDENTIFIERS][MAX_LENGTH];
    int symbol_table_count = 0;

    while (fscanf(file, "%s", word) != EOF) {
        int length = strlen(word);

        // Check if the last character is a semicolon and remove it if it is
        if (word[length-1] == ';') {
            word[length-1] = '\0';
            length--;
        }

        // Reverse the word
        for (int i = 0; i < length; i++) {
            reversed_word[i] = word[length - i - 1];
        }
        reversed_word[length] = '\0';

        // Check if the word is a data type
        bool is_data_type = false;
        if (strcmp(reversed_word, "siht") == 0 || strcmp(reversed_word, "elbuod") == 0 || strcmp(reversed_word, "gnirts") == 0) {
            is_data_type = true;
        }

        // Check if the word is already in the symbol table
        bool is_in_table = false;
        int index = -1;
        for (int i = 0; i < symbol_table_count; i++) {
            if (strcmp(reversed_word, symbol_table[i]) == 0) {
                is_in_table = true;
                index = i;
                break;
            }
        }

        if (!is_in_table) {
            // Add the word to the symbol table
            strcpy(symbol_table[symbol_table_count], reversed_word);
            index = symbol_table_count;
            symbol_table_count++;
        }

        // If the word is an identifier, add it to the identifiers list
        if (isalpha(word[0]) && strcmp(word, ";") != 0) {
            if (!is_data_type) {
                strcpy(identifiers[identifier_count], word);
                identifier_count++;
            }
            printf("%s : %s\n", word, reversed_word);
            printf("System call return: %d\n", index);
        }
    }

    fclose(file);

    FILE* output_file = fopen("output.txt", "w");
    fprintf(output_file, "Identifiers:\n");
    for (int i = 0; i < identifier_count; i++) {
        fprintf(output_file, "%s\n", identifiers[i]);
    }

    fprintf(output_file, "\nSymbol Table:\n");
    for (int i = 0; i < symbol_table_count; i++) {
        fprintf(output_file, "%d : %s\n", i, symbol_table[i]);
    }

    fclose(output_file);

    printf("Output written to output.txt\n");

    return 0;
}
