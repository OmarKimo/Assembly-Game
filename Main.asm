;Author: Yahia Ali Abusaif, Omar Mohammed Mohammed 
include standrd.INC
include laser.INC
include chattting.INC  
include gamemode.inc
.MODEL LARGE
.STACK 64
.DATA 
;output
Endl db 10,13,'$'  ;End line
req1 db 'enter Username: ','$'
playerstatment db 'Player$'
winner db 'is the winner',10,13,'$'
loser db 'is the loser',10,13,'$'
space db ' $'
dash db '-$'
score db 'Score:' , '$'
ammo db 'Ammo:' , '$'  
invgame db 'invite to game' , '$' 
invchat db 'invite to chat' , '$' 
invquit db 'quite the program' , '$' 
msgret db 'for return to menu press Esc $' 
WelcomeString db '  ',10,13
db ' ',10,13
db ' ',10,13
db ' ',10,13
db '  ===================================================================',10,13
db ' ||                       *    PAC-DUEL Game    *                   ||',10,13 
db ' ||                              Control:                           ||',10,13          
db ' ||    Use up, down, left and right keys to change the direction    ||',10,13
db ' ||           of the player and tap button to shoot laser           ||',10,13
db ' ||                                                                 ||',10,13
db ' ||                            How to play:                         ||',10,13          
db ' ||   there are 3 map,each map has points try to collect points     ||',10,13
db ' ||   more than the another player , when the two players clash     ||',10,13
db ' ||   the player with the highst score at that moment will win      ||',10,13
db ' ||   at this round But be aware there are trapes with grey         ||',10,13 
db ' ||       color when you go throw it you can not return             ||',10,13 
db ' ||   there are ammo you need to collect it for shoot the laser     ||',10,13
db ' ||    it will go as horizontel &vertical line ,if it hit the       ||',10,13  
db ' ||      another palyer it will decrease his points by 5            ||',10,13
db ' ||   at the end the player who win 2 maps or more will be the      ||',10,13
db ' ||                               winner                            ||',10,13 
db ' ||                                                                 ||',10,13 
db ' ||                                                                 ||',10,13  
db ' ||                  Press any key to start the game                ||',10,13 
db '  ===================================================================',10,13
db '$'  

menu db '  ',10,13
db ' ',10,13
db ' ',10,13
db ' ',10,13
db '                ====================================================',10,13
db '               ||                                                  ||',10,13
db '               ||                                                  ||',10,13
db '               ||              *    PAC-DUEL Game    *             ||',10,13 
db '               ||--------------------------------------------------||',10,13 
db '               ||                                                  ||',10,13 
db '               ||                for start chat press 1            ||',10,13          
db '               ||                for start game press 2            ||',10,13
db '               ||             for end the program press ESC        ||',10,13
db '               ||                                                  ||',10,13
db '               ||                                                  ||',10,13          
db '               ||                                                  ||',10,13
db '               ||                                                  ||',10,13
db '               ||                                                  ||',10,13
db '               ||                                                  ||',10,13 
db '               ||                                                  ||',10,13 
db '               ||                                                  ||',10,13
db '               ||                                                  ||',10,13 
db '               ||                                                  ||',10,13
db '               ||                                                  ||',10,13
db '                ====================================================',10,13
db '$' 
mychat db '------------------chat------------------$'
  
;const for the game
limitX dw 320      ;The rightmost pixel can be reached 
limitY dw 131      ;The downmost pixel can be reached
PlayerLength dw 7  ;The side length of the player ,note if change go to checkdown
LaserColor db 11   ;The color of Laser
Player1Color db 9  ;The color of Player 1
Player2Color db 12 ;The color of Player 2
WallColor db 4     ;The color of Wall
BonusColor db 13   ;The color of Bonus
BombColor db 14    ;The color of Bombs
trapColor db 7     ;The color of to-Wall Converter

;ASCII of the game 
RightDirButton db 4dh  ;ASCII of right direction button for player 
LeftDirButton db  4bh  ;ASCII of left direction button for player 
UpDirButton db    48h  ;ASCII of up direction button for player 
DownDirButton db  50h  ;ASCII of down direction button for player 
ShootButton1 db 9     ;ASCII of shoot button for player 
StartButton db 13       ;ASCII of the button which start the game
EndButton db 27          ;ASCII of the button which end the game    

;logic & info for the game
Player1x DD 0  ;X coordinate of player 1
Player1y DD 0  ;Y coordinate of player 1
Player2x DD 0  ;X coordinate of player 2
Player2y DD 0  ;Y coordinate of player 2
Player1xx DD 0 ;temp X coordinate of player 1
Player1yy DD 0 ;temp Y coordinate of player 1
Player2xx DD 0 ;temp X coordinate of player 2
Player2yy DD 0 ;temp Y coordinate of player 2
dirc1 DB 0     ;0:up / 1:down / 2:right /3:left for player 1
dirc2 DB 0     ;0:up / 1:down / 2:right /3:left for player 2
score1 DW 0    ;Score of player 1
score2 DW 0    ;Score of player 2
bombs1 Db 0    ;ammo of player 1 
bombs2 Db 0    ;ammo of player 2 
; name of the two player 
name2        db  10        ;MAX NUMBER OF CHARACTERS ALLOWED (20).
             db  ?         ;NUMBER OF CHARACTERS ENTERED BY USER.
             db  11 dup(36) ;CHARACTERS ENTERED BY USER. THE LAST CHAR (11) MUST BE =$ 
            
name1        db  10        ;MAX NUMBER OF CHARACTERS ALLOWED (20).
             db  20         ;NUMBER OF CHARACTERS ENTERED BY USER.
             db  11 dup(36) ;CHARACTERS ENTERED BY USER.  THE LAST CHAR (11) MUST BE =$            
;flags
endflag  db 0
flag1    db 0       ;To check if player 1 is shot.
flag2    db 0       ;To check if player 2 is shot.
nodelete db 0       ;Flag to if the laser is shot or not.
play1    db 1       ;Flag to Player 1
play2    db 2       ;Flag to Player 2  
Collisionflag Db 0  ;if the player already Collision 
stateflag db 0      ;1,2,3,4= direction || 5= laser shot|| 6= endgame, 7 start chat, 8 = MAIN MENU 

;map 
win1 db 0         ;number of games that player1 win 
win2 db 0         ;number of games that player2 win
mapn db 0         ;flag describe what is the current map
delay DD   0FFFFh ;speed -> change for each map
;for erase star 
erasex dd 0
erasey dd 0
;TO SEND & RECIVE  
SENDDATA DB 0       ;the data you want to send at the game And main menu 
;RECDATA DB 0    
VALUE       DB      0   ;RECIVE data (put the value in it when call RECIVE)
LETTER      DB      0   ;SEND data in chat
X1          DB      0   ;X POSTION OF CURSOR FOR PLAYER 1
Y1          DB      0   ;Y POSTION OF CURSOR FOR PLAYER 1 
X2          DB      0   ;X POSTION OF CURSOR FOR PLAYER 2
Y2          DB      14  ;Y POSTION OF CURSOR FOR PLAYER 2
;-------------------------------------------------------------------------------------------------      
        .code
MAIN    PROC FAR               
        MOV AX,@DATA
        MOV DS,AX
        mov ES,AX 
        ;intial for program  
        Configure  
        intialname     
retu:   ;THE MAIN OF PROGRAM
        MOV  SENDDATA,EndButton ;our ASSCI for main menu
        Send SENDDATA   		;tell the another i am in the main menu  
        TEXTMODE
        displaystring menu 
Again1:     
        ;read char & decide what mode
        mov ah,1
        int 16h
        jz conti
        PUSH AX 
        mov ah,0 
        int 16h
        POP AX  
        mov SENDDATA,al
        Send SENDDATA
        cmp al,'1'
        jz chatmode
        cmp al,'2'
        jz gamemode
        cmp al,EndButton
        jz EndApp 
conti:  
        mov al,0
        Receive      
        mov al,value
        cmp al,'1'
        jz invc
        cmp al,'2'
        jz invg
        cmp al,EndButton
        jz invq
jmp Again1

invg:  
		dispstring  invgame,0,23   
jmp Again1

invc:   
		dispstring  invchat,0,23
jmp Again1

invq:   
		dispstring  invquit,0,23
jmp Again1
        
        
gamemode:
        ;intial for game
        displaystring WelcomeString 
        videomode  
        mov mapn,0 
        mov win1,0
        mov win2,0
        mov endflag,0          
        ;------------------Game Start-----------------------
mainmap:
        mov al,mapn ;cal number of win to player 2
        sub al,win1
        mov win2,AL
        drawmap   
lopm1:  
        mov al,dirc1
        cmp al,3
        je myri
        cmp al,4
        je myle
jmp tothehome
myri:   
		mov al,4
jmp tothehome
myle:   
		mov al,3    

tothehome:
        mov SENDDATA,al
        ;input
        mov ah,1
        int 16h
        jz skip1  ; no input
        ;else there are input ,take it and clear buffer
        PUSH AX 
        mov ah,0 
        int 16h
        POP AX 
        caldirc 
        jmp skip1
skip1:
        
        caldirc2 	;send & recive  info to another player
        ;CHECK IF THE GAME END 
        mov  al,endflag
        cmp al,1
        jz retu
        MovePlayer ;calculate new postion for players 
       
        mov  al,Collisionflag  ;check for Collision
        cmp al,1
        jz endmap
         
        statusbar ; update statusbar  
        
        mov ax,0  ;make delay
lopbuf1:
        inc ax 
        cmp ax,delay
        jne lopbuf1
         
jmp lopm1        

endmap:
        mov AX,score1
        cmp AX,score2    ;win for player2
        jl incrmap       ;change map
        cmp AX,score2    ;win for player1
        jG incr1         ;incr res for player 1 
        jmp mainmap      ; points equal , play again 
incr1:
        inc win1 		 ;then change map 
        
incrmap:
		inc mapn     ; change map (0,1,2)
		mov al,mapn   
		cmp al,2     ; if we already finished last map then al must =3
		jg endgame   ; then end game
		jmp mainmap  ; else there are more map map for play
;---------------------------------end of game -------------------------------
endgame:
        ClearScreen 

        ;Determine the winner        
        cmp win1,2  
        jae Player1Win ; condtion for player 1 to win 
        ;else player 2 will win
        movecursor 0,0                   
        mov ah, 9 
        mov dx, offset name2 + 2 
        int 21h         
        dispstring winner,0,1       
        movecursor 0,2
        ;DISPLAY STRING.                   
        mov ah, 9 ;SERVICE TO DISPLAY STRING.
        mov dx, offset name1 + 2 
        int 21h                                      
        dispstring loser,0,3 
jmp tothemain
            
Player1Win:
        MoveCursor 0,0             
        mov ah, 9 
        mov dx, offset name1 + 2 
        int 21h
        dispstring winner,0,1         
        movecursor 0,2                 
        mov ah, 9 
        mov dx, offset name2 + 2 
        int 21h
        dispstring loser,0,3
jmp tothemain

        
tothemain:
        dispstring  msgret,0,4        
        mov ah,0
        int 16h
jmp retu
;-------------------------------------------------------chat mode -------------------------------------------------------
chatmode:
        chatmodedraw           
        ;DISPLAY FIR NAME. 
        MoveCursor 0,0             
        mov ah, 9 
        mov dx, offset name1 + 2 
        int 21h
        ;DISPLAY SEC NAME
        MoveCursor 0,13                
        mov ah, 9 
        mov dx, offset name2 + 2 
        int 21h
        dispstring  msgret,0,23 ; FOR EXIT 
        ; INTIAL CURSOR 
        mov X1,0
        mov Y1,1
        mov X2,0
        mov Y2,14
        MoveCursor X1, Y1              
chatlop:        
        GetKey ;IF KEY PRESSED TAKE IT
        CMP LETTER,27  ;IF EXIT PRESSED 
        Jz retu
        
        CMP LETTER, 0   ;IF NO KEY THEN NOTHING TO SEND ,MOVE TO RECIVE 
        JNZ SEND_LETTER
        Jmp RECEIVE_LETTER
        
        SEND_LETTER:
        PrintChar LETTER, X1, Y1  ;FIRST PRINT IT
	    SaveCursor X1, Y1         ;SAVE NEW POSTION
        Send LETTER               ;SEND
        
RECEIVE_LETTER:
        Receive 
        CMP VALUE, 0  ;CHECK IF THERE ARE SOMETHING TO RECIVE 
        JZ chatlop
        CMP VALUE,7
        Jz retu
	    MoveCursor X2, Y2 ;MOVE TO PLAYER2 CURSOR POSTION
        PrintChar VALUE, X2, Y2  ;PRINT IT
	    SaveCursor X2, Y2        ;SAVE NEW POSTION      
jmp chatlop                
        
EndApp:        
         Send EndButton  ;tell the another you quite 
         ;int that end program
         MOV AH,04CH
         INT 21h 

        HLT
MAIN    ENDP
END  MAIN