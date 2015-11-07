GLOBAL _inb
GLOBAL _outb

_inb:
	mov rax, 0
	mov rdx, rdi
	in al, dx
	mov rax, rdi
	ret

_outb:
 	mov rdx, rsi
 	mov rax, rdi
 	out dx, al
 	ret