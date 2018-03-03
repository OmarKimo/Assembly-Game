;-------------check direction---------------
macro checkup ;must mov cx,x & mov dx,y before that
local lop1,lop2,skip1,skip2,damege,bouns,cwall,aplayer

	mov bx,0 	; for count & to know if something happened -at the end-
	mov ax,0 	; clear ax for read col 
	dec dx 		; check if there is something before moving 
	pusha
	pusha

;fir check if there are wall 
lop1:
	push bx
	mov bx,0
	checkcol cx,dx ; check color of pixel
	cmp al,WallColor ;wall 
	jz skip1
	inc cx
	pop bx 
	inc bx
	cmp bx,PlayerLength
	jl lop1


;check for another thing 
popa
mov bx,0
lop2:
	push bx
	mov bx,0
	checkcol cx,dx ; check color of pixel
	cmp al,BombColor ; bomb
	jz damege
	cmp al,BonusColor ; bouns
	jz bouns
	cmp al,TrapColor ;  trap
	jz cwall
	cmp al,Player2Color ; another player 
	jz aplayer
	cmp al,Player1Color ; another player 
	jz aplayer
	inc cx
	pop bx
	inc bx
	cmp bx,PlayerLength
	jl lop2
	popa
jmp skip2

bouns:
	pop bx
	popa
	mov bx,01
jmp skip2

damege:
; move it from map
	sub dx,4
	sub cx,2
	mov erasex,cx
	mov erasey,dx
	drawsquare erasex,erasey,0,5
	pop bx
	popa
	mov bx,02
jmp skip2

cwall:
	pop bx
	popa
	DrawLineH cx,dx,PlayerLength,WallColor
	sub dx,PlayerLength
jmp skip2

aplayer:
	pop bx
	popa
	mov bx,4
	inc dx
jmp skip2

skip1:
pop bx
popa
popa
inc dx

skip2:
endm
;-------------checkdown--------------
macro checkdown ;must mov cx,x & mov dx,y before that
local lop1,lop2,skip1,skip2,damege,bouns,cwall,aplayer

	mov bx,0 ;  for count & to know if something happened -at the end-
	mov ax,0
	inc dx ; check if there is something before moving
	pusha
	pusha
	add dx,PlayerLength ;(add dimension of square-1)
	dec dx
;fir check if there are wall 
lop1:
	push bx
	mov bx,0
	checkcol cx,dx ; check color of pixel
	cmp al,WallColor ;wall 
	jz skip1
	inc cx
	pop bx 
	inc bx
	cmp bx,PlayerLength
	jl lop1


;check for another thing 
	popa
	mov bx,0
	add dx,PlayerLength ;(add dimension of square-1)
	dec dx

lop2:
push bx
	mov bx,0
	checkcol cx,dx check color of pixel
	cmp al,WallColor ; wall 
	jz skip1
	cmp al,BombColor ; bomb
	jz damege
	cmp al,BonusColor ;bouns
	jz bouns
	cmp al,TrapColor ; trap
	jz cwall
	cmp al,Player2Color ; another player 
	jz aplayer
	cmp al,Player1Color; another player 
	jz aplayer
	inc cx
	pop bx
	inc bx
	cmp bx,PlayerLength
	jl lop2
	popa
jmp skip2

bouns:
	pop bx
	popa
	mov bx,01
jmp skip2

damege:
	; move it from map
	sub cx,2
	mov erasex,cx
	mov erasey,dx
	drawsquare erasex,erasey,0,5
	pop bx
	popa
	mov bx,02
jmp skip2

cwall:
pop bx
	popa
	add dx,PlayerLength
	dec dx 
	DrawLineH cx,dx,PlayerLength,WallColor
	inc dx
jmp skip2

aplayer:
	pop bx
	popa
	mov bx,4
	dec dx
jmp skip2

skip1:
	pop bx
	popa
	dec dx

skip2:
endm
;-------------checkright-------------
macro checkright ;must mov cx,x & mov dx,y before that
local lop1,lop2,skip1,skip2,damege,bouns,cwall,aplayer

	mov bx,0 ;  for count & to know if something happened -at the end-
	mov ax,0
	inc cx ; check if there is somthing before moving 
	pusha
	pusha

	add cx,PlayerLength ;(add dimension of square-1)
	dec cx
	;fir check if there are wall 
lop1:
	push bx
	mov bx,0
	checkcol cx,dx ; check color of pixel
	cmp al,WallColor ;wall 
	jz skip1
	inc dx
	pop bx 
	inc bx
	cmp bx,PlayerLength
	jl lop1

;check for another thing 
popa
	mov bx,0
	add cx,PlayerLength ;(add dimension of square-1)
	dec cx

lop2:
	push bx
	mov bx,0
	checkcol cx,dx check color of pixel
	cmp al,WallColor ; wall 
	je skip1
	cmp al,BombColor ; bomb
	je damege
	cmp al,BonusColor ; bouns
	je bouns
	cmp al,TrapColor ;  trap
	je cwall
	cmp al,Player2Color ;  another player 
	je aplayer
	cmp al,Player1Color; another player 
	je aplayer
	inc dx
	pop bx
	inc bx
	cmp bx,PlayerLength
	jl lop2
popa
jmp skip2

bouns:
	pop bx
popa
	mov bx,01
jmp skip2

damege:
	dec dx
	mov erasex,cx
	mov erasey,dx
	drawsquare erasex,erasey,0,5
	pop bx
popa
	mov bx,02
jmp skip2

cwall:
	pop bx
	popa
	add Cx,PlayerLength
	dec cx 
	DrawLineV cx,dx,PlayerLength,WallColor
	inc Cx
jmp skip2

aplayer:
	pop bx
	popa
	mov bx,4
	dec cx
jmp skip2

skip1:
	pop bx
popa
	dec cx

skip2:
endm
;------------checkleft-------------
macro checkleft ;must mov cx,x & mov dx,y before that
local lop1,lop2,skip1,skip2,damege,bouns,cwall,aplayer

	mov bx,0 ;  for count & to know if something happened -at the end-
	mov ax,0
	dec cx ; check if there is something before moving 
pusha
pusha

;fir check if there are wall 
lop1:
	push bx
	mov bx,0
	checkcol cx,dx ; check color of pixel
	cmp al,WallColor ;wall 
	je skip1
	inc cx
	pop bx 
	inc bx
	cmp bx,PlayerLength
	jl lop1

;check for another thing 
	popa
	mov bx,0
lop2:
	push bx
	mov bx,0
	checkcol cx,dx check color of pixel
	cmp al,WallColor ;wall 
	je skip1
	cmp al,BombColor ; bomb
	je damege
	cmp al,BonusColor ; bouns
	je bouns
	cmp al,TrapColor ; trap
	je cwall
	cmp al,Player2Color ; another player 
	je aplayer
	cmp al,Player1Color; another player 
	je aplayer
	inc dx
	pop bx
	inc bx
	cmp bx,PlayerLength
	jl lop2
popa
jmp skip2

bouns:
	pop bx
	popa
	mov bx,01
jmp skip2

damege:
	sub cx,5
	dec dx
	mov erasex,cx
	mov erasey,dx
	drawsquare erasex,erasey,0,5
	pop bx
	popa
	mov bx,02
jmp skip2

cwall:
	pop bx
	popa
	DrawLineV cx,dx,PlayerLength,WallColor
	sub Cx,PlayerLength
jmp skip2

aplayer:
	pop bx
	popa
	mov bx,4
	inc cx
jmp skip2

skip1:
	pop bx
	popa
	inc cx

skip2:
endm
;----------------------------------------------
;---------------map-----------------
MACRO DRAWmap 
local map1,map2,map3,con  	    ; General 
local loop0,loop1 				; for point
local loop11,loop12 			; for fir map
local loop6,loop7 				; for sec map
local loop2,loop3,loop4,loop5   ; for 3rd map
	ClearScreen 
;draw the out line 
	DrawLineV 0,0,130,WallColor
	DrawLineV 319,0,130,WallColor
	DrawLineH 0,0,320,WallColor
	DrawLineH 0,130,320,WallColor

;points 
	mov dx,5
loop1:
	mov cx,5 
loop0:
	DrawLineV cx,dx,1,BonusColor
	add cx,10
	cmp cx,318
	jle loop0
	add dx,10
	cmp dx,125
	jle loop1

	mov al,mapn
	cmp al,0
	je map1
	cmp al,1
	je map2
jmp map3

;---------------------------fir1-------------------------
map1:
;draw level1                
	DrawLineV 10,10,50,WallColor
	DrawLineV 310,10,50,WallColor
	DrawLineV 310,70,50,WallColor
	DrawLineV 10,70,50,WallColor
	DrawLineH 10,10,145,WallColor
	DrawLineH 165,10,145,WallColor
	DrawLineH 10,120,145,WallColor
	DrawLineH 165,120,145,WallColor
  
;draw level2  	
	DrawLineV 20,20,92,WallColor
	DrawLineV 300,20,92,WallColor
 
;draw lvl3 as loop (all wall has same lenth and same distance from the another) 
	mov ax,20
loop12:
	push ax
	DrawLineH  30,ax,260,WallColor
	pop ax
	add ax,10
	cmp ax,110
	jle loop12

;bomb
	DrawStar  5,5,BombColor
	DrawStar  315,5,BombColor
	DrawStar  5,125,BombColor
	DrawStar  315,125,BombColor

	mov ax,160
	mov bx,25
loop11:
	DrawStar  ax,bx,BombColor
	add bx,10
	cmp bx,110
	jl loop11

;wall convertor 
	DrawLineH   155,10,10,TrapColor
	DrawLineH   155,120,10,TrapColor
	DrawLineV  10,60,10,TrapColor
	DrawLineV  310,60,10,TrapColor
	DrawLineH   21,20,10,TrapColor
	DrawLineH   20,110,10,TrapColor
	DrawLineH   290,20,10,TrapColor
	DrawLineH   290,110,10,TrapColor

;put the initial coordinates of the two player					
	drawsquare 1,61,Player1Color,PlayerLength ;first player
	drawsquare 312,61,Player2Color,PlayerLength ;second player
	mov Player1x,1
	mov Player1y,61
	mov Player2x,312
	mov Player2y,61

	mov Player1xx,1
	mov Player1yy,61
	mov Player2xx,312
	mov Player2yy,61

	mov dirc1,4
	mov dirc2,3

	mov delay,0EFFFh ;speed 

jmp con
;-----------------------2nd----------------------
map2:
;draw the rest wall
;1st level
	DrawLineV 10,10,110,WallColor
	DrawLineV 310,10,110,WallColor
	DrawLineH 20,10,281,WallColor
	DrawLineH 20,120,281,WallColor
;2nd level
	DrawLineV 20,20,40,WallColor
	DrawLineV 20,70,40,WallColor
	DrawLineV 300,20,40,WallColor
	DrawLineV 300,70,40,WallColor
	DrawLineH 20,20,280,WallColor                   
	DrawLineH 20,110,280,WallColor
;3rd level
	DrawLineH 20,60,100,WallColor
	DrawLineH 20,70,100,WallColor
	DrawLineH 200,60,100,WallColor
	DrawLineH 200,70,100,WallColor
	DrawLineV 130,30,70,WallColor
	DrawLineV 190,30,70,WallColor

;wall convertor
	DrawLineV  190,21,8,TrapColor
	DrawLineV  130,21,8,TrapColor
	DrawLineV  130,101,8,TrapColor
	DrawLineV  190,101,8,TrapColor

	DrawLineV  300,11,8,TrapColor
	DrawLineV  20,11,8,TrapColor

	DrawLineV  20,111,8,TrapColor
	DrawLineV  300,111,8,TrapColor

	DrawLineV  300,61,8,TrapColor
	DrawLineV  20,61,8,TrapColor

;bomb
	DrawStar  160,5,BombColor
	DrawStar  160,15,BombColor
	DrawStar  160,115,BombColor
	DrawStar  160,125,BombColor

	mov ax,65
	mov bx,35
loop6:
	DrawStar  bx,ax,BombColor
	add bx,10
	cmp bx,130
	jl loop6

	mov bx,195
loop7:
	DrawStar  bx,ax,BombColor
	add bx,10
	cmp bx,280
	jl loop7

;the initial postion of the two player
	drawsquare 1,65,Player1Color,PlayerLength ; fir player
	drawsquare 312,65,Player2Color,PlayerLength ;sec player

	mov Player1x,1
	mov Player1y,65
	mov Player2x,312
	mov Player2y,65

	mov Player1xx,1
	mov Player1yy,65
	mov Player2xx,312
	mov Player2yy,65 

	;mov dirc1,4
	;mov dirc2,3  ;for not move before 1st player
	mov delay,0AFFFh ;speed 

jmp con
;-----------------------3rd----------------------
map3:
; for this map most Hline has same size (same for Vline) and has common x or y so draw all vertical then all horizontal
;all vertical lines
	DrawLineV 10,20,40,WallColor
	DrawLineV 150,20,40,WallColor
	DrawLineV 170,20,40,WallColor
	DrawLineV 310,20,40,WallColor
	DrawLineV 10,70,40,WallColor
	DrawLineV 150,70,40,WallColor
	DrawLineV 170,70,40,WallColor
	DrawLineV 310,70,40,WallColor
;all horizontal lines
	DrawLineH 10,10,141,WallColor
	DrawLineH 10,60,140,WallColor
	DrawLineH 10,70,140,WallColor
	DrawLineH 10,120,140,WallColor
	DrawLineH 170,10,141,WallColor
	DrawLineH 170,60,140,WallColor
	DrawLineH 170,70,140,WallColor
	DrawLineH 170,120,140,WallColor
;bomb line 
	DrawLineV 155,20,40,WallColor
	DrawLineV 165,20,40,WallColor
	DrawLineV 155,70,40,WallColor
	DrawLineV 165,70,40,WallColor
;inside boxes
	DrawLineV 75,20,30,WallColor
	DrawLineV 85,20,30,WallColor
	DrawLineV 235,20,30,WallColor
	DrawLineV 245,20,30,WallColor

	DrawLineV 75,80,30,WallColor
	DrawLineV 85,80,30,WallColor
	DrawLineV 235,80,30,WallColor
	DrawLineV 245,80,30,WallColor

;wall convertor 
	DrawLineH 1,10,10,TrapColor
	DrawLineH 310,10,10,TrapColor
	DrawLineH 150,10,20,TrapColor ; double trap 
	DrawLineH 159,10,2,WallColor ;for not take it one time 

	DrawLineV  10,61,9,TrapColor
	DrawLineV  310,61,9,TrapColor

	DrawLineH  1,120,10,TrapColor
	DrawLineH  310,120,10,TrapColor
	DrawLineH  150,120,20,TrapColor ; double trap 
	DrawLineH  159,120,2,WallColor ;for not take it one time  

;bomb
	mov ax,160
	mov bx,25
loop2:
	DrawStar ax,bx,BombColor
	add bx,10
	cmp bx,110
	jl loop2

	mov ax,80
	mov bx,15
loop3:
	DrawStar  ax,bx,BombColor
	add bx,10
	cmp bx,116
	jl loop3

	mov ax,240
	mov bx,15
loop4:
	DrawStar ax,bx,BombColor
	add bx,10
	cmp bx,116
	jl loop4

	mov ax,90
	mov bx,125
loop5:
	DrawStar  ax,bx,BombColor
	add ax,20
	cmp ax,241
	jl loop5

;the initial postion of the two player
	drawsquare 1,1,Player1Color,PlayerLength  ;first player
	drawsquare 312,1,Player2Color,PlayerLength ;second player

	mov Player1x,1
	mov Player1y,1
	mov Player2x,312
	mov Player2y,1 

	mov Player1xx,1
	mov Player1yy,1
	mov Player2xx,312
	mov Player2yy,1

	;mov dirc1,1
	;mov dirc2,1
	mov delay,05FFFh ;speed 

;---- now initial data---------------
con:
	mov endflag,0 
	mov Collisionflag,0
	mov score1,0
	mov score2,0
	mov bombs1,0
	mov bombs2,0
	mov x1,11
	mov x2,11 
	mov Y1,21
	mov y2,22 
	dispstring  msgret,0,23 
	dispstring mychat,0,20
	disp2number win1,15,17
	dispstring dash,17,17
	disp2number win2,18,17
	;DISPLAY FIR NAME.
	MoveCursor 0,21             
    mov ah, 9 
    mov dx, offset name1 + 2 
    int 21h
    ;DISPLAY SEC NAME
    MoveCursor 0,22               
    mov ah, 9 
    mov dx, offset name2 + 2 
    int 21h
ENDM
;--------------------------------------
;------------control both player (for less code)- (include checkmov and some code in MAIN)
macro MovePlayer 
local up1,down1,left1,right1,con,bouns1,bomb1 ; for player 1
local up2,down2,left2,right2,con2,bouns2,bomb2 ; for player 2
local Collision ,player2log,myend ;general 
 
	drawsquare Player1x,Player1y,0,PlayerLength ;erase the player from old location
	mov cx,Player1x
	mov dx,Player1y 
	mov ah,dirc1
	cmp ah,1 ;up
	je up1
	cmp ah,2 ;down
	je down1
	cmp ah,3;right
	je right1
	cmp ah,4 ;left 
	je left1 

up1:
	checkup
jmp con

down1:
	checkdown
jmp con 

left1:
	checkleft
jmp con 

right1:
	checkright
jmp con 

con:
	mov Player1x,cx
	mov Player1y,dx
	mov Player1xx,cx
	mov Player1yy,dx
	drawsquare Player1x,Player1y,Player1Color,PlayerLength ;Draw the player at new location
	cmp bx,1 ;take point
	je bouns1
	cmp bx,2 ;take bomb
	je bomb1
	cmp bx,4  ;PlayerCollision
	je Collision
	jmp player2log

bouns1:
	inc score1
jmp player2log

bomb1:
	inc bombs1
jmp player2log


player2log:
	drawsquare Player2x,Player2y,0,PlayerLength ;erase the player from old location
	mov cx,Player2x
	mov dx,Player2y
	mov ah,dirc2
	cmp ah,1 ;up 
	je up2
	cmp ah,2 ;down 
	je down2
	cmp ah,3 ;right 
	je right2
	cmp ah,4 ;left 
	je left2 

up2:
	checkup
jmp con2

down2:
	checkdown
jmp con2 


left2:
	checkleft
jmp con2 

right2:
	checkright
jmp con2 

con2:
	mov Player2x,cx
	mov Player2y,dx
	mov Player2xx,cx
	mov Player2yy,dx
	drawsquare Player2x,Player2y,Player2Color,PlayerLength ;Draw the player at new location
	cmp bx,1   ;take point
	je bouns2
	cmp bx,2    ;take bomb
	je bomb2
	cmp bx,4  ;PlayerCollision
	je Collision
jmp myend

bouns2:
	inc score2
jmp myend 

bomb2:
	inc bombs2
jmp myend

Collision:
	mov Collisionflag,1
jmp myend

myend:
endm
;==================================================================calculate direction===========================================================
;------------------------------first player --------------
macro caldirc
local up, down, left,right,shoot,con,endga,sendlet 

	cmp ah,UpDirButton ;up
	je up
	cmp ah,DownDirButton ;down
	je down
	cmp ah,LeftDirButton ;left 
	je left
	cmp ah,RightDirButton ;right
	je right 
	cmp al,ShootButton1 
	je shoot
	cmp al,EndButton
	je endga
	cmp al,20
	jge sendlet

jmp con

up:
	mov dirc1,1
	mov SENDDATA,1
jmp con
down:
	mov dirc1,2
	mov SENDDATA,2
jmp con
right:
	mov dirc1,3
	mov SENDDATA,4
jmp con
left:
	mov dirc1,4
	mov SENDDATA,3
jmp con

shoot:
	mov SENDDATA,5
	ShootLaser Player1x,Player1y,PlayerLength,play1
	mov si,Player1xx
	mov Player1x,si
	mov si,Player1yy
	mov Player1y,si
	DeleteLaser Player1xx,player1yy,PlayerLength
	mov si,Player1x
	mov Player1xx,si
	mov si,Player1y
	mov Player1yy,si
jmp con

sendlet:
	mov SENDDATA,al
	MoveCursor X1,y1
	mov ah,2
	mov dl,[SENDDATA]
	int 21h
	SaveCursor X1, Y1
	cmp x1,39
	jl con 
	mov x1,11
	mov y1,21
jmp con

endga:
	mov endflag,1
	mov SENDDATA,6
jmp con

con:
endm
;------------------------second player --------------------
macro caldirc2 ;send & recive
local dirc,letter1,exit ,shoot,con

	Send SENDDATA
	Receive
	cmp VALUE ,4
	jle dirc 
	cmp value,5
	je shoot 
	cmp value,6
	je exit 
	cmp value,0
	jne letter1 ;else there are msg
jmp con

exit:
	mov endflag,1
jmp con

dirc:
	mov al,value
	mov dirc2,al
jmp con

shoot:
	ShootLaser Player2x,Player2y,PlayerLength,play2
	mov si,Player2xx
	mov Player2x,si
	mov si,Player2yy
	mov Player2y,si
	DeleteLaser Player2xx,player2yy,PlayerLength
	mov si,Player2x
	mov Player2xx,si
	mov si,Player2y
	mov Player2yy,si
jmp con

letter1:
	mov Y2,22
	PrintChar value, X2, Y2
	SaveCursor X2, Y2
	cmp x2,38
	jle con 
	mov x2,11
	mov y2,22
jmp con

con:
endm 
;=============
macro StatusBar

      ;PRINT FIRST NAME      
      movecursor 0,17                  
      mov ah, 9 ;SERVICE TO DISPLAY STRING.
      mov dx, offset name1 + 2 ;MUST END WITH '$'.
      int 21h
      ;PRINT SEC NAME      
      movecursor 21,17                  
      mov ah, 9 ;SERVICE TO DISPLAY STRING.
      mov dx, offset name2 + 2 ;MUST END WITH '$'.
      int 21h


	 dispstring score,0,18
     dispstring ammo,0,19
     dispstring score,21,18
     dispstring ammo,21,19
     disp4number score1,6,18
     disp4number score2,27,18
     disp2number bombs1,5,19
     disp2number bombs2,26,19
	  
endm