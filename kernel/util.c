#include <stdbool.h>
#include <stdint.h>

int string_length(const char s[]) {
  int i = 0;
  while (s[i] != '\0')
    ++i;
  return i;
}

void reverse(char s[]) {
  int c, i, j;
  for (i = 0, j = string_length(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
void clear_string(char s[]) { *s = '\0'; }

void int_to_string(int n, char str[]) {
  int i, sign;
  if ((sign = n) < 0)
    n = -n;
  i = 0;
  do {
    str[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0)
    str[i++] = '-';
  str[i] = '\0';

  reverse(str);
}

void string_to_char_array(char out[], const char *str) {
  while (*str != '\0') {
    *out = *str;
    str++;
    out++;
  }
  *out = '\0';
}

void append(char s[], char n[]) {
  int len1 = string_length(s);
  int len2 = string_length(n);
  int length;

  for (int i = 0; i < len2; i++) {
    s[i + len1] = n[i];
  }
  s[len1 + len2] = '\0';
}

bool backspace(char s[]) {
  int len = string_length(s);
  if (len > 0) {
    s[len - 1] = '\0';
    return true;
  } else {
    return false;
  }
}

/* K&R
 * Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2 */
int compare_string(char s1[], char s2[]) {
  int i;
  for (i = 0; s1[i] == s2[i]; i++) {
    if (s1[i] == '\0')
      return 0;
  }
  return s1[i] - s2[i];
}
