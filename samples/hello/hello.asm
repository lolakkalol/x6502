	org $8000
start:
	lda #$02
	sta $ff02
	ldx #$00
loop:
	lda msg,x
        beq end
	sta $ff00
	inx
        bra loop
end:
	lda #$0a
	sta $ff00
	stp

int_handler:
nmi_handler:
	rti

msg:    string "Hello, world!"
msgend:


	org $fffa
	word int_handler
	word start
	word nmi_handler
	

