;----------------Let's Fight with Laser ^_^-----------------
macro ShootLaser PosX,PosY,Len,Play ;The upper leftmost point of the player who shot the laser and its side length. These variables are 2-bytes size.
local d1, d2, d3, d4, l1, l2, l3, l4, Before, After, zero1, zero2, Up, Down, finish, playerone, playertwo, go, dec1, dec2, nodec, finishfinish
local cond0, cond1, cond2, cond3, cond4, cond5, cond6, cond7, cond8, cond9, cond10, cond11

	cmp Play,1
	jne Playertwo

;Check if Player 1 can shoot laser
playerone:
	cmp bombs1,0
	jz finishfinish
	dec bombs1
jmp go

;Check if Player 2 can shoot laser
playertwo:
	cmp bombs2,0
	jz finishfinish
	dec bombs2
jmp go

go:
	mov bx,PosY
	add bx,Len
	add bx,1
	sub PosY,1

;Draw the part of laser before the player
Before:
	;change of X
	mov si,0

	;change of Y
	add PosY,1
	cmp bx,PosY
	jne l1 ;We haven't finished.

	;We have finished. PosY will back to original value;
	mov dx,PosY
	sub dx,len
	sub dx,2
	mov PosY, dx
jmp After

l1:
	cmp si,PosX
	jz Before
	ReadPixel si,PosY
	cmp al,0
	jne d1 ;To check if the color of pixel is not black (Wall, Player, or food)
	mov al,LaserColor
	sub al,1
jmp cond0

d1:
		cmp al,Player1Color
		jz cond1
		cmp al,Player2Color
		jne cond0
	cond2:
		mov flag2,1
	jmp cond0
	cond1:
		mov flag1,1
	cond0: 
		add al,1
		DrawPixel si,PosY,al
		add si,1
jmp l1


;Draw the part of laser after the player
After:
	;change of X
	mov si, PosX
	add si, Len
	add si, 1

	;change of Y
	add PosY,1
	cmp bx,PosY
	jne l2 ;We haven't finished.

	;We have finished. PosY will back to its original value.
	mov dx,PosY
	sub dx,Len
	sub dx,1
	mov PosY, dx

	;bx = PosY   the limit
	mov bx,PosY

	;PosX = PosX+Len+1    to be the limit
	mov dx,PosX
	add dx,Len
	add dx,1
	mov PosX, dx
	
	mov PosY,0
jmp Up

	l2:
		cmp si,limitX 
		jz After
		ReadPixel si,PosY
		cmp al,0
		jne d2 ;To check if the color of pixel is not black (Wall, Player, or food)
		mov al,LaserColor
		sub al,1
		jmp cond3 
		d2:
			cmp al,Player1Color
			jz cond4
			cmp al,Player2Color
			jne cond3
			cond5:
				mov flag2,1
				jmp cond3
			cond4:
				mov flag1,1
			cond3: 
			add al,1
			DrawPixel si,PosY,al
			add si,1
	jmp l2


;Draw the part of laser above the player
Up:
	;change of X
	mov si,PosX
	sub si,Len
	sub si,1
	
	;change of Y
	add PosY,1
	cmp bx,PosY
	jne l3 ;We haven't finished.

	;We have finished.
	;PosY = PosY+Len    the start
	mov dx,PosY
	add dx,Len
	mov PosY, dx
	
jmp Down

	l3:
		cmp si,PosX
		jz Up
		ReadPixel si,PosY
		cmp al,0
		jne d3 ;To check if the color of pixel is not black (Wall, Player, or food)  
		mov al,LaserColor
		sub al,1
		jmp cond6
		d3:
			cmp al,Player1Color
			jz cond7
			cmp al,Player2Color
			jne cond6
			cond8:
				mov flag2,1
				jmp cond6
			cond7:
				mov flag1,1
			cond6:
			add al,1
			DrawPixel si,PosY,al
			add si,1
	jmp l3


;Draw the part of laser below the player
Down:
	;change of X
	mov si,PosX
	sub si,Len
	sub si,1
	
	;change of Y
	add PosY,1
	mov di,PosY
	cmp di,limitY
	jne l4 ;We haven't finished.

	jmp finish
	l4:
		cmp si,PosX
		jz Down
		
		ReadPixel si,PosY
		cmp al,0
		jne d4 ;To check if the color of pixel is not black (Wall, Player, or food)  
		mov al,LaserColor
		sub al,1
		jmp cond9
		d4:
			cmp al,Player1Color
			jz cond10
			cmp al,Player2Color
			jne cond9
			cond11:
				mov flag2,1
				jmp cond9
			cond10:
				mov flag1,1
			cond9:
			add al,1
		    	DrawPixel si,PosY,al
		    	add si,1
		    	jmp l4

finishfinish:
mov nodelete,1

finish:
	cmp play,1
	jne dec1  ;if player 1 who shot the laser, check if player 2 is shot. else check if player 1 is shot

dec2:
	cmp flag2,1
	jne nodec ;if player 2 isn't shot, don't decrement its score.
	cmp score2,6
	jl zero2  ;if the score of player 2 isn't zero, decrement its score.
	dec score2,5
jmp nodec

zero2:
	mov score2,0
jmp nodec

dec1:
	cmp flag1,1
	jne nodec ;if player 1 isn't shot, don't decrement its score.
	cmp score1,6
	jl zero1  ;if the score of player 1 isn't zero, decrement its score.
	dec score1,5
jmp nodec

zero1:
	mov score1,0

nodec:
	mov flag1,0  ;Go to normal case
	mov flag2,0  ;Go to normal case

endm
;----------------------------Delete Laser----------------------------
macro DeleteLaser PosX,PosY,Len ;The upper leftmost point of the player who shot the laser and its side length. These variables are 2-bytes size.
local d1,d2,d3,d4,l1,l2,l3,l4
local Before,After,Up,Down,finish

cmp nodelete,1
jz finish

mov bx,PosY
add bx,Len
add bx,1
sub PosY,1

;Delete the part of laser before the player
Before:
	;change of X
	mov si,0

	;change of Y
	add PosY,1
	cmp bx,PosY
	jne l1 ;We haven't finished.

	;We have finished. PosY will back to original value;
	mov dx,PosY
	sub dx,len
	sub dx,2
	mov PosY, dx
	jmp After

	l1:
		cmp si,PosX
		jz Before
		ReadPixel si,PosY
		cmp al,LaserColor
		jne d1 ;To check if the color of pixel is not black (Wall, Player, or food) 
		mov al,1
		d1:
			sub al,1
			DrawPixel si,PosY,al
			add si,1
			jmp l1


;Delete the part of laser after the player
After:
	;change of X
	mov si, PosX
	add si, Len
	add si, 1

	;change of Y
	add PosY,1
	cmp bx,PosY
	jne l2 ;We haven't finished.

	;We have finished. PosY will back to its original value.
	mov dx,PosY
	sub dx,Len
	sub dx,1
	mov PosY, dx

	;bx = PosY   the limit
	mov bx,PosY

	;PosX = PosX+Len+1    to be the limit
	mov dx,PosX
	add dx,Len
	add dx,1
	mov PosX, dx
	
	mov PosY,0
	jmp Up

	l2:
		cmp si,limitX 
		jz After
		ReadPixel si,PosY
		cmp al,LaserColor
		jne d2 ;To check if the color of pixel is not black (Wall, Player, or food) 
		mov al,1
		d2:
			sub al,1
			DrawPixel si,PosY,al
			add si,1
			jmp l2


;Delete the part of laser above the player
Up:
	;change of X
	mov si,PosX
	sub si,Len
	sub si,1
	
	;change of Y
	add PosY,1
	cmp bx,PosY
	jne l3 ;We haven't finished.

	;We have finished.
	;PosY = PosY+Len    the start
	mov dx,PosY
	add dx,Len
	mov PosY, dx
	
	jmp Down

	l3:
		cmp si,PosX
		jz Up
		ReadPixel si,PosY
		cmp al,LaserColor
		jne d3 ;To check if the color of pixel is not black (Wall, Player, or food) 
		mov al,1
		d3:
			sub al,1
			DrawPixel si,PosY,al
			add si,1
			jmp l3


;Delete the part of laser below the player
Down:
	;change of X
	mov si,PosX
	sub si,Len
	sub si,1
	
	;change of Y
	add PosY,1
	mov di,PosY
	cmp di,limitY
	jne l4 ;We haven't finished.
	jmp finish
	l4:
		cmp si,PosX
		jz Down
		
		ReadPixel si,PosY
		cmp al,LaserColor
		jne d4 ;To check if the color of pixel is not black (Wall, Player, or food) 
		mov al,1
		d4:
		    sub al,1
		    DrawPixel si,PosY,al
		    add si,1
		    jmp l4
finish:
mov nodelete,0
endm
