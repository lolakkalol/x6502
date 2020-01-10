#include "io.h"

#include <ncurses.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>

#include "functions.h"
#include "opcodes.h"

void init_io() {
}

void finish_io() {
}

void handle_io(cpu *m) {
  if (get_emu_flag(m, EMU_FLAG_DIRTY)) {
    uint16_t addr = m->dirty_mem_addr;

    if (addr == IO_PUTCHAR) {
      addch(m->mem[addr]);
    }
  }
}
