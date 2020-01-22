#ifndef __6502_LCD__
#define __6502_LCD__

#include <stdint.h>
#include <stdbool.h>

#define CMD_CLEAR             0x01

#define CMD_HOME              0x02

#define CMD_ENTRY_MODE        0x04
#define CMD_EM_SHIFT_CURSOR   0x00
#define CMD_EM_SHIFT_DISPLAY  0x01
#define CMD_EM_DECREMENT      0x00
#define CMD_EM_INCREMENT      0x02

#define CMD_DISPLAY_MODE      0x08
#define CMD_DM_CURSOR_NOBLINK 0x00
#define CMD_DM_CURSOR_BLINK   0x01
#define CMD_DM_CURSOR_OFF     0x00
#define CMD_DM_CURSOR_ON      0x02
#define CMD_DM_DISPLAY_OFF    0x00
#define CMD_DM_DISPLAY_ON     0x04

#define CMD_FUNCTION_SET      0x20
#define CMD_FS_FONT5x7        0x00
#define CMD_FS_FONT5x10       0x04
#define CMD_FS_ONE_LINE       0x00
#define CMD_FS_TWO_LINE       0x08
#define CMD_FS_4_BIT          0x00
#define CMD_FS_8_BIT          0x10

#define CMD_CGRAM_SET         0x40
#define CMD_DDRAM_SET         0x80

#define LCD_MEM_SIZE          0x100

#define LCD_ROWS              4
#define LCD_COLS              20

typedef struct {
  // settings
  bool initialized;
  // enable latch (last status)
  bool enable_latch;
  uint8_t function;
  uint8_t entry_mode;
  uint8_t display_mode;
  // data bus latch
  uint8_t data;
  bool fourbit_mode;
  uint8_t data_msb;
  uint8_t data_lsb;
  bool lower_bits;
  // data
  uint8_t ddram[LCD_MEM_SIZE];
  // cursor position
  uint8_t cursor;
} lcd;

lcd* new_lcd();

void destroy_lcd(lcd* l);

void process_input(lcd *l, bool enable, bool rwb, bool data, uint8_t input);

#endif
