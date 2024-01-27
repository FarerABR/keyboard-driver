#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"

#include "util.h"

void start_kernel() {
    char *video_memory = (char *)0xb8000;
    *video_memory = 'X';
    clear_screen();
    print_string("Installing interrupt service routines (ISRs).\n");
    isr_install();

    print_string("Enabling external interrupts.\n");
    asm volatile("sti");

    print_string("Initializing keyboard (IRQ 1).\n");
    init_keyboard();
}
