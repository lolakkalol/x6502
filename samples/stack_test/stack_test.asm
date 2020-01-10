ROM_START     .equ $8000

RESET_VECTOR  .equ $fffc

  .org ROM_START

data_display:
  ldx #$00                 ; Initialize counter
loop_data:
  lda data,x               ; Load data bytes from address data + x
  beq end_prog             ; On end of stream move to end of program
  jsr write_data
  inx                      ; Increase counter
  jmp loop_data
end_prog:
  stp

write_data:
  jsr pulse                ; Pulse 6522
  rts                      ; Return

pulse:
  sta $ff00
  rts                      ; Return from subroutine

data:
  string "Merry Christmas!"

  .org RESET_VECTOR
  word data_display
  word $0000

