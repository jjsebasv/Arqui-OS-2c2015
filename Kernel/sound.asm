; play sound test
GLOBAL play_test

; =============================================================================
; BareMetal -- a 64-bit OS written in Assembly for x86-64 systems
; Copyright (C) 2008-2012 Return Infinity
; =============================================================================


align 16
db 'DEBUG: SOUND    '
align 16
os_SystemVariables:	equ 0x0000000000110000
os_ClockCounter:	equ os_SystemVariables + 0x10


; -----------------------------------------------------------------------------
; os_speaker_tone -- Generate a tone on the PC speaker
; IN:	RAX = note frequency
; OUT:	All registers preserved
; Note:	Call os_speaker_off to stop the tone
os_speaker_tone:
  push rax
  push rcx

  mov cx, ax		; Store note value for now
  mov al, 182
  out 0x43, al		; System timers..
  mov ax, cx		; Set up frequency
  out 0x42, al
  mov al, ah		; 64-bit mode.... AH allowed????
  out 0x42, al
  in al, 0x61		; Switch PC speaker on
  or al, 0x03
  out 0x61, al

  pop rcx
  pop rax
  ret
; -----------------------------------------------------------------------------


; -----------------------------------------------------------------------------
; os_speaker_off -- Turn off PC speaker
; IN:	Nothing
; OUT:	All registers preserved
os_speaker_off:
  push rax

  in al, 0x61		; Switch PC speaker off
  and al, 0xFC
  out 0x61, al

  pop rax
  ret
; -----------------------------------------------------------------------------


; -----------------------------------------------------------------------------
; os_speaker_beep -- Create a standard OS beep
; IN:	Nothing
; OUT:	All registers preserved
play_test_4:
  push rax
  push rcx

  cli

  xor eax, eax
  mov ax, 0x0C80
  call os_speaker_tone
  mov ax, 2		; A quarter of a second
  call os_speaker_off

  sti

  pop rcx
  pop rax
  ret
; -----------------------------------------------------------------------------

; -----------------------------------------------------------------------------
; os_delay -- Delay by X eights of a second
; IN:	RAX = Time in eights of a second
; OUT:	All registers preserved
; A value of 8 in RAX will delay 1 second and a value of 1 will delay 1/8 of a second
; This function depends on the RTC (IRQ 8) so interrupts must be enabled.
os_delay:
  push rcx
  push rax

  mov rcx, [os_ClockCounter]	; Grab the initial timer counter. It increments 8 times a second
  add rax, rcx			; Add RCX so we get the end time we want
os_delay_loop:
  cmp qword [os_ClockCounter], rax	; Compare it against our end time
  jle os_delay_loop		; Loop if RAX is still lower

  pop rax
  pop rcx
  ret
; -----------------------------------------------------------------------------


; =============================================================================
; EOF

play_test_2:
	IN AL, 61h  ;Save state
	PUSH AX	  

	MOV BX, 6818; 1193180/175
	MOV AL, 6Bh  ; Select Channel 2, write LSB/BSB mode 3
	OUT 43h, AL	 
	MOV AX, BX	
	OUT 24h, AL  ; Send the LSB
	MOV AL, AH	 
	OUT 42h, AL  ; Send the MSB
	IN AL, 61h	 ; Get the 8255 Port Contence
	OR AL, 3h		
	OUT 61h, AL  ;End able speaker and use clock channel 2 for input
	MOV CX, 03h ; High order wait value
	MOV DX, 0D04h; Low order wait value
	MOV AX, 86h;Wait service
	INT 15h			
	POP AX;restore Speaker state
	OUT 61h, AL
	RET

play_test_3:
	push rbp
	mov rbp, rsp

	mov	eax,7
	int 	80h

	mov rsp, rbp
	pop rbp
	ret

; nasm -f elf beep.asm
; ld -s -o beep beep.o

global _start
section .text
play_test:

	push rbp
	mov rbp, rsp

	mov rax,4  ; sys_write
	mov rbx,1  ; stdout
	mov rcx,beep ; buffer
	mov rdx, 1  ; length
	int 80h

	mov rax,1  ; sys_exit
	xor rbx, rbx ; I didn't see an error, did you see an error? :)
	int 80h

	mov rsp, rbp
	pop rbp
	ret

section .data
; hell, put it in the code section...
beep db 7 ; "BELL"