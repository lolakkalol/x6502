#ifndef __6502_GUI__

#include <stdio.h>

#include "cpu.h"

void init_gui();
void finish_gui();
void update_gui(cpu *m);

void trace_bus(char *msg);

#endif