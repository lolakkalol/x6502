#include "io.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>

#include "functions.h"
#include "opcodes.h"

#define MONITOR_ROWS 4
#define MONITOR_COLS 40

#define MONITOR_HEIGHT (MONITOR_ROWS) + 2
#define MONITOR_WIDTH (MONITOR_COLS) + 2

#define TRACE_ROWS 20
#define TRACE_COLS 80

#define TRACE_HEIGHT (TRACE_ROWS) + 2
#define TRACE_WIDTH (TRACE_COLS) + 2

#define MONITOR_ORIGINX 0
#define MONITOR_ORIGINY 4

#define TRACE_ORIGINX (MONITOR_ORIGINX)
#define TRACE_ORIGINY (MONITOR_ORIGINY) + (MONITOR_HEIGHT)

uint8_t io_modeflags = 0x00;
uint8_t io_supports_paint;

FILE *blck0 = NULL;

WINDOW *window = NULL;
WINDOW *wnd_monitor = NULL;
WINDOW *wnd_monitor_content = NULL;
WINDOW *wnd_trace = NULL;
WINDOW *wnd_trace_content = NULL;

void set_block_source(FILE *source) {
    blck0 = source;
}

void init_io() {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    io_supports_paint = (has_colors() != FALSE);
    if (io_supports_paint) {
        start_color();
        for (int i = 0; i < 8; i++) {
            init_pair(i, i, COLOR_BLACK);
        }
    }

    wnd_monitor = newwin(MONITOR_HEIGHT, MONITOR_WIDTH, MONITOR_ORIGINY, MONITOR_ORIGINX);
    wnd_monitor_content = newwin(MONITOR_ROWS, MONITOR_COLS, MONITOR_ORIGINY+1, MONITOR_ORIGINX+1);
    wnd_trace = newwin(TRACE_HEIGHT, TRACE_WIDTH, TRACE_ORIGINY, TRACE_ORIGINX);
    wnd_trace_content = newwin(TRACE_ROWS, TRACE_COLS, TRACE_ORIGINY+1, TRACE_ORIGINX+1);
    scrollok(wnd_trace_content, TRUE);
    refresh();
    box(wnd_monitor, 0, 0);
    mvwprintw(wnd_monitor, 0, 1, "CPU-Monitor");
    box(wnd_trace, 0, 0);
    mvwprintw(wnd_trace, 0, 1, "Bus-Trace");
    wrefresh(wnd_monitor);
    wrefresh(wnd_trace);
}

void finish_io() {
    if (io_modeflags & IO_MODEFLAG_WAIT_HALT) {
        nodelay(stdscr, FALSE);
        printw("\nterminated, press any key to exit.\n");
        while(getch() == ERR);
    }

    endwin();
}

void update_modeflags(uint8_t old_flags, uint8_t new_flags) {
    io_modeflags = new_flags;
}

void update_paint(uint8_t paint) {
    wattrset(window,
            COLOR_PAIR(paint & 0x0F) |
            (paint & IO_PAINT_DIM ? A_DIM : 0) |
            (paint & IO_PAINT_UNDERLINE ? A_UNDERLINE : 0) |
            (paint & IO_PAINT_BOLD ? A_BOLD : 0));
}

void trace_bus(char *msg) {
    wprintw(wnd_trace_content, msg);
    wrefresh(wnd_trace_content);
}

void handle_io(cpu *m) {
    int read;

    // start by populating the monitor
    mvwprintw(wnd_monitor_content, 0, 0, "PC: %04X, OP: %02X (%s)", m->pc_actual, m->opcode, translate_opcode(m->opcode));
    mvwprintw(wnd_monitor_content, 1, 0, "ACC: %02X, X: %02X, Y: %02X, SP: %02X", m->ac, m->x, m->y, m->sp);
    mvwprintw(wnd_monitor_content, 2, 0, "SR: %c%c-%c%c%c%c%c",
      m->sr & 0x80 ? 'N' : '-',
      m->sr & 0x40 ? 'V' : '-',
      m->sr & 0x10 ? 'B' : '-',
      m->sr & 0x08 ? 'D' : '-',
      m->sr & 0x04 ? 'I' : '-',
      m->sr & 0x02 ? 'Z' : '-',
      m->sr & 0x01 ? 'C' : '-');
    mvwprintw(wnd_monitor_content, 3, 0, "Clock mode: %s", m->clock_mode == CLOCK_FAST ? "FAST" : m->clock_mode == CLOCK_SLOW ? "SLOW" : "STEP");
    wrefresh(wnd_monitor_content);

    switch (m->clock_mode) {
      case CLOCK_FAST:
        halfdelay(1);
	read = getch();
	break;
      case CLOCK_SLOW:
	halfdelay(10);
	read = getch();
	break;
      case CLOCK_STEP:
	while ((read = getch()) == ERR);
	break;
    }

    switch(read) {
      case ERR:
	break;
      case 's':
      case 'S':
	break;
      case 'b':
      case 'B':
	m->clock_mode = CLOCK_STEP;
	break;
      case 'g':
	m->clock_mode = CLOCK_SLOW;
	break;
      case 'G':
	m->clock_mode = CLOCK_FAST;
	break;
      default:
        m->interrupt_waiting = 0x01;
       	m->mem[IO_GETCHAR] = read;
    } 

    if (get_emu_flag(m, EMU_FLAG_DIRTY)) {
        uint16_t addr = m->dirty_mem_addr;

        if (addr == IO_PUTCHAR) {
            if (io_modeflags & IO_MODEFLAG_VTERM) {
                wprintw(window, "%c", m->mem[addr]);
                wrefresh(window);
            } else {
                addch(m->mem[addr]);
            }
        } else if (addr == IO_MODEFLAGS) {
            update_modeflags(io_modeflags, m->mem[IO_MODEFLAGS]);
        } else if (addr == IO_PAINT) {
            update_paint(m->mem[addr]);
        } else if (addr == IO_BLCK0_ADDRL
                || addr == IO_BLCK0_ADDRH
                || addr == IO_BLCK0_READ) {
            if (blck0 == NULL) {
                fprintf(stderr, "tried to read from unattached block device\n");
                exit(-1);
                return;
            }

            uint16_t read_addr =
                    m->mem[IO_BLCK0_ADDRH] << 8 | m->mem[IO_BLCK0_ADDRL];
            int res = fseek(blck0, read_addr, SEEK_SET);
            if (res) {
                m->mem[IO_BLCK0_ERR] = IO_BLCK_ERR_SEEK;
                return;
            }

            res = fgetc(blck0);
            if (res == EOF) {
                m->mem[IO_BLCK0_ERR] = IO_BLCK_ERR_EOF;
                return;
            }
            m->mem[IO_BLCK0_READ] = 0xFF & res;
            m->mem[IO_BLCK0_ERR] = 0x00;
        }
    }
}
