 ;*************************************Common (Foundations)*************************************
 macro disp4number num,Col,Row ; display 4-digit decimal number
    
  mov ax,num
  mov dx,0
  mov cx,1000
  div cx
  mov cx,dx
  
  ;print digit in AL at Col,Row
  mov ah,02
  mov bh,00
  mov dl,Col
  mov dh,Row
  int 10h 
  mov dl,AL
  add dl,30h
  int 21h
  
  
  mov ax,cx
  mov cl,100
  div cl
  mov bl,ah 

  ;print digit in AL at Col+1,Row
  mov ah,02
  mov bh,00
  mov dl,Col
  add dl,1
  mov dh,Row
  int 10h
  mov dl,AL
  add dl,30h
  int 21h
  
  mov ax,bx
  mov cl,10
  div cl
  mov bl,ah
  

  ;print digit in AL at Col+2,Row
  mov ah,02 
  mov bh,00
  mov dl,Col
  add dl,2
  mov dh,Row
  int 10h
  mov dl,AL
  add dl,30h
  int 21h
  
  ;print digit in BL at Col+3,Row
  mov ah,02
  mov bh,00
  mov dl,Col
  add dl,3
  mov dh,Row
  int 10h  
  mov dl,BL
  add dl,30h
  int 21h
  
  endm
;------------------------------------------
  macro disp2number num,Col,Row; display 2-digit decimal number

  mov al,num
  mov ah,0
  mov cl,10
  div cl
  mov bl,ah
  
  ;print digit in AL at Col,Row
  mov ah,02 
  mov bh,00
  mov dl,Col
  mov dh,Row
  int 10h
  mov dl,AL
  add dl,30h
  int 21h
  
  ;print digit in BL at Col+1,Row
  mov ah,02
  mov bh,00
  mov dl,Col
  add dl,1
  mov dh,Row
  int 10h  
  mov dl,BL
  add dl,30h
  int 21h
  
  endm
;==============
;-------------Hide Pixel-------------------
macro hidepixel  x,y
mov cx,x
mov dx,y
draw cx,dx,0
endm
;-------------Video Mode---------------
MACRO videomode
mov ah,0h
mov al,13h
int 10h
ENDM 
;----------------TEXT MODE
MACRO TEXTMODE
mov ah,0h
mov al,03h
int 10h
ENDM 
;-----------------------------------------
macro dispstring string,Col,Row ;set cursor as well as print string
  mov ah,02
  mov bh,00
  mov dl,Col
  mov dh,Row
  int 10h
  mov ah,09
  mov dx,offset string
  int 21h
endm
;------------------------------------------
SaveCursor MACRO Xdest, Ydest
    PUSHA
    
        mov ah,3
        mov bh,0h
        int 10h
		mov Ydest, dh
		mov Xdest, dl
        
    POPA
ENDM
;-----------------Draw Horizontal Line----------------
macro DrawLineH x,y,lenth,col
local loop1
pusha
	mov bx,0
	mov dx,y
	mov al,col
	mov ah,0ch
	mov cx,x
loop1:
	DRAW cx,dx,al
	inc cx
	inc bx
	cmp bx,lenth
	jne loop1
popa
endm
;--------------Draw Vertical line-------------
macro DrawLineV x,y,lenth,col
local loop1
pusha
	mov bx,0
	mov dx,y
	mov al,col
	mov ah,0ch
	mov cx,x
loop1:
	DRAW cx,dx,al
	inc dx
	inc bx
	cmp bx,lenth
	jne loop1
popa
endm
;---------------Draw Square----------------
macro drawsquare x,y,z,s 
local loop1, loop2, loop3
pusha
	mov dx, y
	mov di,s
	dec dx
loop1:
	mov cx,x 
	mov si,s
	cmp  di,0
	je loop3  
	dec di 
	inc dx
loop2:
	pusha
	draw cx,dx,z
	popa
	dec si  
	inc cx
	cmp si,0 
	je loop1
	jmp loop2 
loop3:
popa 
endm
;--------------------DrawStar
macro DrawStar x,y,col
pusha
	mov cx,x
	mov dx,y
	mov al,Col
	mov ah,0ch
	int 10h ;main line
	inc cx
	int 10h
	inc cx 
	int 10h
	sub cx,3
	int 10h
	dec cx
	int 10h
	add cx,2
	dec dx
	int 10h ; up point
	add dx,2
	int 10h ; left point
	dec cx
	int 10h ; left point
	add cx,2
	int 10h
	dec cx
	inc dx
	int 10h
popa
endm
;---------------Draw Pixel----------------
MACRO DRAW X,Y,Z
	mov ah,0ch ;Draw Pixel Command
	mov cx,X ;Column
	mov dx,Y ;Row
	mov al,Z ;Pixel color
	int 10h
ENDM
;--------------Check Pixel Color----------------
macro checkpixel x,y,p
mov ah,0dh
mov bh,p
mov cx,x
mov dx,y
int 10h
endm
;---------------Display String-------------------
macro displaystring mes
mov ah, 9
mov dx, offset mes
int 21h 
endm
;---------------Get Key Pressed------------------
macro getkeypressed  ;wait for a key
mov ah,0
int 16h
endm
;--------------Draw Pixel------------------
macro DrawPixel X,Y,C
mov ah,0ch
mov cx,X
mov dx,Y
mov al,C
int 10h
endm
;-----------------Read Pixel-------------------
macro ReadPixel X,Y
mov ah,0dh
mov cx, X
mov dx, Y
int 10h
endm
;----------------------Check Color-------------------------
macro checkcol x,y
mov ah,0dh
mov Bx,0
mov CX, x
mov DX, y
int 10h 
endm
;--------------Clear Screen------------------
macro ClearScreen
LOCAL COL,ROW
PUSHA
mov al,0 ;Pixel color
mov ah,0ch ;Draw Pixel Command
MOV CX,0
ROW:
MOV DX,0
COL:
int 10h
INC DX
CMP DX,200
JLE Col
INC Cx
CMP CX,320
JLE ROW
MoveCursor 0,0
POPA
endm
;----------------Move Cursor---------------
MoveCursor MACRO Xloc,Yloc
    PUSHA 
        MOV AH, 0FH
        INT 10H
        mov ah,2
		mov dh, Yloc
		mov dl, Xloc
        int 10h
    
    POPA
ENDM
;-------------chatmodedraw------
chatmodedraw MACRO
    PUSHA
	
		mov ax, 0600h
		mov bh, 07
		mov cx, 0
		mov dx, 184fh
		int 10h
		
		MoveCursor 0, 12
        
        mov cx, 0
PRINTDASH:
        mov ah,2
        mov dl,'-'
        int 21h
		INC CX
        CMP CX,79
		JLE PRINTDASH
    
    POPA
ENDM