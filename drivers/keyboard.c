#include "keyboard.h"
#include "../cpu/isr.h"
#include "../kernel/kernel.h"
#include "../kernel/util.h"
#include "display.h"
#include "ports.h"
#include <stdbool.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C

#define SC_MAX 72

const char *sc_name[] = {
    "ERROR",      "Esc",      "1",        "2",  "3",  "4",      "5",
    "6",          "7",        "8",        "9",  "0",  "-",      "=",
    "Backspace",  "Tab",      "Q",        "W",  "E",  "R",      "T",
    "Y",          "U",        "I",        "O",  "P",  "[",      "]",
    "Enter",      "Lctrl",    "A",        "S",  "D",  "F",      "G",
    "H",          "J",        "K",        "L",  ";",  "'",      "`",
    "LShift",     "\\",       "Z",        "X",  "C",  "V",      "B",
    "N",          "M",        ",",        ".",  "/",  "RShift", "Keypad *",
    "LAlt",       "Spacebar", "CapsLock", "F1", "F2", "F3",     "F4",
    "F5",         "F6",       "F7",       "F8", "F9", "F10",    "NumLock",
    "ScrollLock", "Home"};

char *last_char = "";
bool alt_up;

void print_letter(uint8_t scancode) {
  if ((int)scancode <= SC_MAX) { // key is recognized and is pressed down
    const char *key = sc_name[(int)scancode];
    if (key == "Lctrl" || key == "LShift" || key == "Rctrl" ||
        key == "RShift" || key == "LAlt" || key == "RAlt") {
      string_to_char_array(last_char, key);
      alt_up = true;
      return;
    }
    if (string_length(last_char) > 0) {
      char str[string_length(key) + string_length(last_char)];
      char sec_key[string_length(key)];
      string_to_char_array(str, last_char);
      string_to_char_array(sec_key, key);
      append(str, " + ");
      append(str, sec_key);
      char msg[] = " is pressed";
      append(str, msg);
      print_string(str);
    } else {
      char str[string_length(key)];
      string_to_char_array(str, key);
      char msg[] = " is pressed";
      append(str, msg);
      print_string(str);
    }

  } else if ((int)scancode > SC_MAX &&
             (int)scancode < 0x80) { // key is not in the list
    print_string("Unknown key down");

  } else if ((int)scancode <= SC_MAX + 0x80) { // key is recognized and released
    const char *key = sc_name[(int)(scancode - 0x80)];
    if (key == "Lctrl" || key == "LShift" || key == "LAlt" || key == "Rctrl" ||
        key == "RShift" || key == "RAlt") {
      if (alt_up == false)
        return;
      // print the alt key
      char str[string_length(key)];
      string_to_char_array(str, key);
      char msg[] = " is pressed";
      append(str, msg);
      print_string(str);
      print_nl();
      // print key up
      char u_str[string_length(key)];
      string_to_char_array(u_str, key);
      char u_msg[] = "key up ";
      append(u_msg, u_str);
      print_string(u_msg);
      // remove from the stack
      clear_string(last_char);

    } else if (string_length(last_char) > 0) { // alt-key + key is up
      char str[string_length(key) + string_length(last_char)];
      char sec_key[string_length(key)];
      string_to_char_array(str, last_char);
      string_to_char_array(sec_key, key);
      append(str, " + ");
      append(str, sec_key);
      char msg[] = "key up ";
      append(msg, str);
      print_string(msg);
      // remove from the stack
      clear_string(last_char);
      // set the flag
      alt_up = false;

    } else { // just a simple key being released
      char str[string_length(key)];
      string_to_char_array(str, key);
      char msg[] = "key up ";
      append(msg, str);
      print_string(msg);
    }
  } else { // uknown key is released
    print_string("Unknown key up");
  }
}

static void keyboard_callback(registers_t *regs) {
  uint8_t scancode = port_byte_in(0x60);
  print_letter(scancode);
  print_nl();
}

void init_keyboard() { register_interrupt_handler(IRQ1, keyboard_callback); }
