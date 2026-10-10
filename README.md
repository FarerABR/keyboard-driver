# keyboard-driver

A small educational 32-bit x86 OS kernel project focused on handling keyboard input via IRQ1.

## What this repository is

This repo builds a bootable floppy image that:

- boots from a custom MBR and enters protected mode
- initializes IDT/ISR interrupt handling
- enables external interrupts
- registers a keyboard interrupt handler
- reads keyboard scancodes from port `0x60` and prints key press/release events to screen

## Project structure

- `boot/` – boot sector, disk loading, protected-mode switch, and kernel entry assembly
- `cpu/` – IDT and ISR/IRQ setup
- `drivers/` – hardware drivers (`display`, `ports`, `keyboard`)
- `kernel/` – kernel entrypoint and utility functions
- `Makefile` – build and run commands

## Build and run

### Prerequisites

- `nasm`
- `qemu-system-i386`
- `x86_64-elf-gcc`
- `x86_64-elf-ld`
- GNU `make`

### Commands

```bash
make        # builds and runs in QEMU
make run    # explicit run target
make clean  # remove build artifacts
```

## Output behavior

When running in QEMU, the kernel prints initialization messages and then logs keyboard events (for example key presses, key combinations with modifier keys, and key releases).
