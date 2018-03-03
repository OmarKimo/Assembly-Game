;------------INTIAL CONEECT ---------------
Configure MACRO
    PUSHA
        ;Set Divisor Latch Access Bit
        mov dx,3fbh 			; Line Control Register
        mov al,10000000b		;Set Divisor Latch Access Bit
        out dx,al			;Out it
        ;Set LSB byte of the Baud Rate Divisor Latch register.
        mov dx,3f8h			
        mov al,0ch			
        out dx,al
        ;Set MSB byte of the Baud Rate Divisor Latch register.
        mov dx,3f9h
        mov al,00h
        out dx,al
        ;Set port configuration
        mov dx,3fbh
        mov al,00011011b
        out dx,al 
    POPA
ENDM
;--------------------------------------------------------------take name-------------------------------------------------
macro intialname 
local lops,lopr
;READ & send name & recive the another name
	displaystring req1
	mov ah,0ah
	mov dx,offset name1
	int 21h ;take the name 
	
	mov bx,0
	mov si,offset name1
	add si,2
	mov di,offset name2
	add di,2
lops:
	mov al,[si]
	mov LETTER ,al
	Send LETTER
	inc si
lopr:
	Receive
	cmp VALUE,0 
	je lopr
	mov al,value
	mov [di],al
	inc di
	INC bx 
	cmp bx,10
	jle lops
endm

;--------------------------------------------------------chat Macro---------------------------------------------------------
Send MACRO STAGE
local end,AGAIN,newline
PUSHA

        ;Check that Transmitter Holding Register is Empty
		mov dx , 3FDH		; Line Status Register
AGAIN:  In al , dx 			;Read Line Status
        AND al , 00100000b
        JZ AGAIN

		;check if it's a new line
		cmp STAGE, 13
		jz newline
		
        ;If empty put the VALUE in Transmit data register
  		mov dx , 3F8H		; Transmit data register
  		mov  al,STAGE
  		out dx , al 
		mov STAGE, 0
jmp end
		
newline:
        mov dx , 3F8H		; Transmit data register
		mov  al,STAGE
		out dx , al 
		mov STAGE, 10
end:    
POPA
ENDM
;------------------------------Receive
Receive MACRO
LOCAL NOTRECEIVED, END
PUSHA 

		;Check that Data Ready
		mov dx , 3FDH		; Line Status Register
		in al , dx 
		AND al , 1
		JZ NOTRECEIVED

		;If Ready read the VALUE in Receive data register
		mov dx , 03F8H
		in al , dx 
		mov VALUE , al
JMP END
			
NOTRECEIVED:
		mov VALUE, 0 
			
END:
POPA
ENDM
;------------------------------GetKey
GetKey MACRO
LOCAL NOKEY,END
PUSHA 
			
	CMP LETTER, 0
	JNZ END
	mov ah,1
	int 16h
	jz NOKEY	
	mov ah,0
	int 16h	
	MOV LETTER, AL
JMP END
	
NOKEY:
		MOV LETTER, 0
END:
POPA
ENDM
;-----------------------------PrintChar
PrintChar MACRO CHAR, X, Y
    local SCROLL_UP, SCROLL_DOWN, PRINT,MYAGE,SCROLL_UP2
	PUSHA
		
		MOV AL,  X
		cmp AL, 79
		jz SCROLL_DOWN
	MYAGE:	
		MOV AH, Y
		cmp AH, 11
		jz SCROLL_UP
		cmp AH, 23
		jz SCROLL_UP2
	jmp print 

	SCROLL_UP:
		mov ah,6       ; v function 6
		mov al,1        ; scroll by 1 line    
		mov bh,7       ; normalideo attribute         
		mov ch,1       ; upper left Y
		mov cl,0        ; upper left X
		mov dh,11     ; lower right Y
		mov dl,79      ; lower right X 
		int 10h
		DEC Y
	JMP PRINT
			
	SCROLL_UP2:
		mov ah,6      ; v function 6
		mov al,1        ; scroll by 1 line    
		mov bh,7       ; normalideo attribute         
		mov ch,14       ; upper left Y
		mov cl,0        ; upper left X
		mov dh,22     ; lower right Y
		mov dl,79      ; lower right X 
		int 10h
		DEC Y
	JMP PRINT

	SCROLL_DOWN:
		inc Y
		mov x,0
	JMP MYAGE	
	PRINT:
		mov ch, X
		mov cl, Y
		MoveCursor ch, cl
		mov ah,2
		mov dl,CHAR
		int 21h
	POPA
ENDM