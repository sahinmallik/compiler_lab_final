#include <stdio.h>
#include <stdbool.h>

bool isDigit(const char ch) {
    if (ch >= '0' && ch <= '9') {
        return true;
    }
    else {
        return false;
    }
}

typedef enum { None, Int, Float, AmbFloat, AmbExp, Exp } State;

bool isNumber(const char* str) {
    State state = None;

    for (const char* it = str; *it != '\0';) {
        if (isDigit(*it)) {
            if (state == None) {
                state = Int;
            }
            else if (state == AmbFloat) {
                state = Float;
            }
            else if (state == AmbExp) {
                state = Exp;
            }
            else {
                return false;
            }

            while (*(++it) != '\0' && isDigit(*it)) {
            }
        }
        else if (*it == '.') {
            if (state == Int) {
                state = AmbFloat;
            }
            else {
                return false;
            }

            it++;
        }
        else if (*it == '^') {
            if (state == Int || state == Float) {
                state = AmbExp;
            }
            else {
                return false;
            }

            it++;
        }
        else {
            return false;
        }
    }

    if (state == Int || state == Float || state == Exp) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    printf("%d\n", isNumber("1"));
    printf("%d\n", isNumber("22"));
    printf("%d\n", isNumber("3.3"));
    printf("%d\n", isNumber("44.4"));
    printf("%d\n", isNumber("55.55"));
    printf("%d\n", isNumber("1^1"));
    printf("%d\n", isNumber("22^2"));
    printf("%d\n", isNumber("33^33"));
    printf("%d\n", isNumber("4.4^2"));
    printf("%d\n", isNumber("55.5^2"));
    printf("%d\n", isNumber("66.66^2"));
    printf("%d\n", isNumber("66..66^2"));

    return 0;
}
