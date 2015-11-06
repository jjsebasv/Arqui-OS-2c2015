GLOBAL _inb
GLOBAL _outb

_inb:
    	push    rbp
    	mov     rbp, rsp
	
    	push    rdx
	
    	mov     rdx, [ss:rdi]
    	xor     rax, rax
    	in      al, dx
	
    	pop     rdx
	
    	leave
	ret

_outb:
	push rbp
	mov rbp, rsp

	pushaq	
	
	mov dx, [rdi] 
	mov ax, [rsi]

	out dx, al
	
	popaq
	
	leave
	ret