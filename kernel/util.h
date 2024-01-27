#pragma once

#include <stdbool.h>
#include <stdint.h>

#define low_16(address) (uint16_t)((address)&0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

int string_length(const char s[]);

void string_to_char_array(char out[],const  char *str);

void clear_string(char s[]);

void reverse(char s[]);

void int_to_string(int n, char str[]);

void append(char s[], char n[]);
