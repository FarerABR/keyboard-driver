#include "keyboard.h"
#include "../cpu/isr.h"
#include "../kernel/kernel.h"
#include "../kernel/util.h"
#include "display.h"
#include "ports.h"
#include <stdbool.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C

// static char key_buffer[256];

#define SC_MAX 57

const char *sc_name[] = {
    "ERROR",     "Esc",     "1", "2", "3", "4",      "5",
    "6",         "7",       "8", "9", "0", "-",      "=",
    "Backspace", "Tab",     "Q", "W", "E", "R",      "T",
    "Y",         "U",       "I", "O", "P", "[",      "]",
    "Enter",     "Lctrl",   "A", "S", "D", "F",      "G",
    "H",         "J",       "K", "L", ";", "'",      "`",
    "LShift",    "\\",      "Z", "X", "C", "V",      "B",
    "N",         "M",       ",", ".", "/", "RShift", "Keypad *",
    "LAlt",      "Spacebar"};
// const char sc_ascii[] = {
//     '?', '?', '1', '2', '3', '4', '5', '6', '7', '8', '9',  '0', '-', '=',
//     '?',
//     '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',  '[', ']', '?',
//     '?', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', '?',
//     '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', '?', '?',  '?', '
//     '};

void print_letter(uint8_t scancode) {
  if ((int)scancode < SC_MAX + 1) {
    const char *key = sc_name[(int)scancode];
    char str[string_length(key)];
    string_to_char_array(str, key);
    char msg[] = " is pressed";
    append(str, msg);
    print_string(str);
  } else if (scancode <= 0x7f) {
    print_string("Unknown key down");
  } else if (scancode <= 0x39 + 0x80) {
    const char *key = sc_name[(int)(scancode - 0x80)];
    char str[string_length(key)];
    string_to_char_array(str, key);
    char msg[] = "key up ";
    append(msg, str);
    print_string(msg);
  } else {
    print_string("Unknown key up");
  }
}

static void keyboard_callback(registers_t *regs) {
  uint8_t scancode = port_byte_in(0x60);
  print_letter(scancode);
  print_nl();
}

void init_keyboard() { register_interrupt_handler(IRQ1, keyboard_callback); }
