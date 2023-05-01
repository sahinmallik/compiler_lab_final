#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isAlphabet(const char ch) {
  if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
    return true;
  else
    return false;
}

bool isValid(const char ch) {
  if ((ch >= '0' && ch <= '9') || isAlphabet(ch) || ch == '_')
    return true;
  else
    return false;
}

enum State {
  None,
  C1,
};

const char* keywords[] = {"return"};

bool isKeyword(const char* str) {
  int len = sizeof(keywords) / sizeof(keywords[0]);
  for (int i = 0; i < len; i++) {
    if (strcmp(str, keywords[i]) == 0)
      return true;
  }
  return false;
}

bool isIdentifier(const char* str) {
  enum State state = None;
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    if (isAlphabet(str[i]) || str[i] == '_') {
      if (state == None) state = C1;
    } else if (isValid(str[i])) {
      if (state == C1) {
      } else
        return false;
    } else
      return false;
  }
  if (isKeyword(str)) return false;
  return true;
}

int main() {
  printf("%d\n", isIdentifier("1"));
  printf("%d\n", isIdentifier("a"));
  printf("%d\n", isIdentifier("a1"));
  printf("%d\n", isIdentifier("aa"));
  printf("%d\n", isIdentifier("_a"));
  printf("%d\n", isIdentifier("ab_1_2"));
  return 0;
}
