#include <stdio.h>
#include <string.h>

// function to parse the string
int parse(char str[]);

int main()
{
    char str[100];

    // input string from user
    printf("Enter a string of tokens: ");
    scanf("%s", str);

    // parse the string
    if (parse(str))
        printf("Valid string.\n");
    else
        printf("Invalid string.\n");

    return 0;
}

int parse(char str[])
{
    int len = strlen(str);
    int i = 0;

    // start with non-terminal symbol S
    if (str[0] != 'a' && str[0] != 'c')
        return 0;
    i++;

    // iterate through the string
    while (i < len)
    {
        // check for valid operator
        if (str[i] != '+' && str[i] != '-')
            return 0;
        i++;

        // check for valid operand
        if (i >= len || (str[i] != 'a' && str[i] != 'b' && str[i] != 'c'))
            return 0;
        i++;

        // check for valid recursive rule
        if (i >= len || (str[i] != '+' && str[i] != '-'))
            return 0;
        i++;
    }

    // if all rules are followed, the string is valid
    return 1;
}