;---------------------------------------------------------------------

  use32              ; включить 32-битный режим ассемблера
  org    0           ; адресация с нуля

  db     'MENUET01'  ; 8-байтный идентификатор MenuetOS
  dd     1           ; версия заголовка (1 либо 2, см. док-ю)
  dd     START       ; адрес первой команды
  dd     I_END       ; размер программы
  dd     MEM         ; количество памяти
  dd     STACKTOP    ; адрес вершины стэка
  dd     0           ; адрес буфера для параметров
  dd     0           ; зарезервировано

include "macros.inc" ; макросы облегчают жизнь ассемблерщиков!

;---------------------------------------------------------------------
;---  НАЧАЛО ПРОГРАММЫ  ----------------------------------------------
;---------------------------------------------------------------------

include 'XO_CAS_V1.2.inc'
include 'XO_WinCon_V1.1.inc'
include 'XO_Draw.inc'
include 'XO_STRING_UTILS.INC'

START:


mov eax, 40
mov ebx, 100111b
int 0x40


red:                    ; перерисовать окно

    call draw_window    ; вызываем процедуру отрисовки окна

;---------------------------------------------------------------------
;---  ЦИКЛ ОБРАБОТКИ СОБЫТИЙ  ----------------------------------------
;---------------------------------------------------------------------

still:

    mcall 10            ; функция 10 - ждать события

    cmp  eax,1          ; перерисовать окно ?
    je   red            ; если да - на метку red
    cmp  eax,2
    je   key
    cmp  eax,3          ; нажата кнопка ?
    je   button         ; если да - на button
    cmp  eax,6          ; нажата клавиша ?
    je   mouse            ; если да - на key

    jmp  still          ; если другое событие - в начало цикла


;---------------------------------------------------------------------
  key:; нажата клавиша на клавиатуре
                 ; функция 2 - считать код символа (в ah)
    mcall 2

    ;call draw_window    ; вызываем процедуру отрисовки окна
    call CompMove

    jmp  still          ; вернуться к началу цикла

  mouse:; нажата клавиша на клавиатуре
                 ; функция 2 - считать код символа (в ah)

    mcall 37, 3
    test eax, 100000000b
    jz still

    mov edx, [field]
    test edx, 16
    jnz WcPs

    test edx, 1
    jnz step_PO

    test edx, 0x2000
    jz still
    jmp step_PX

    step_PO:
    test edx, 0x1000
    jz still
    step_PX:


    mcall 37, 1

    mov ebx, eax
    shr ebx, 16
    and eax, 0xff

    cmp ebx, 2
    jb still
    cmp ebx, 95
    ja still

    cmp eax, 5
    jb still
    cmp eax, 5+95
    ja still

    ;sub ebx, 2
    sub eax, 5

    shr ebx, 5
    shr eax, 5

    mov ecx, 6
    mul ecx

    shl ebx, 1

    shl eax, 8
    or eax, ebx

    mov ebx, 0x80000000
    mov cl, ah

    shr ebx, cl; mov on y

    mov cl, al
    shr ebx, cl; mov on x

    mov edx, [field]

    test edx, ebx  ;test is empty
    jnz still ; if not skip
    or edx, ebx ;set is not empty
    shr ebx, 1

    test edx, 1
    jz MWrO
    or edx,ebx
    jmp Mout
    MWrO:


    Mout:
    inc edx
    mov [field], edx

WcPs:

    rds:
    call draw_window    ; вызываем процедуру отрисовки окна

    jmp  still          ; вернуться к началу цикла

;---------------------------------------------------------------------

  button:
    mcall 17            ; 17 - получить идентификатор нажатой кнопки

    cmp   ah, 2
    jne b_next0
    and [field], 0x3000
    jmp rds

    b_next0:
    cmp   ah, 3
    jne b_next1
    xor [field], 0x1000
    jmp rds

   b_next1:
    cmp   ah, 4
    jne b_next2
    xor [field], 0x2000
    jmp rds

   b_next2:
    cmp   ah, 1         ; если НЕ нажата кнопка с номером 1,
    jne   still         ;  вернуться

  .exit:
    mcall -1            ; иначе конец программы


;---------------------------------------------------------------------
;---  ОПРЕДЕЛЕНИЕ И ОТРИСОВКА ОКНА  ----------------------------------
;---------------------------------------------------------------------

draw_window:

    mcall 12, 1       ; функция 12: сообщить ОС о начале отрисовки

    mcall 48, 3, sc,sizeof.system_colors
        mov   eax, [sc.work_button_text]    ; цвет фона
        or    eax, 0x90000000        ; и тип строки
        mov [butTextColAPar], eax

        mov   eax, [sc.work_text]    ; цвет фона
        ;or    eax, 0xD0000000        ; и тип строки
        or    eax, 0x90000000        ; и тип строки
        mov [LabelTextColAPar], eax

    mcall 26 , 5
    cmp eax, 4
    jnz NG_eng
    mov [St_NG], St_NG_Ru
    mov [St_Comp], St_Comp_Ru
    mov [St_Player], St_Player_Ru
    mov [St_Draw], St_Draw_Ru
    mov [St_Win], St_Win_Ru
    mov [St_Turn],St_Turn_Ru
    jmp NG_out
    NG_eng:
    mov [St_NG], St_NG_Eng
    mov [St_Comp], St_Comp_Eng
    mov [St_Player], St_Player_Eng
    mov [St_Draw], St_Draw_Eng
    mov [St_Win], St_Win_Eng
    mov [St_Turn],St_Turn_Eng
    NG_out:

    ;mcall 4, <105, (5+96-16)>,[butTextColAPar] ,


    mov   edx, [sc.work]         ; цвет фона
    or    edx, 0x34000000        ; и тип окна 3
    mcall 48, 4
    mov ecx, 200*65536+106
    add ecx,eax
    mcall 0, <200,205>,, , ,title



    mcall 8 , 100*65536+96 , (5+96-20)*65536+20 ,2 , [sc.work_button]

    mcall  ,  , (5+96-42)*65536+20 ,3 ,

    mcall  ,  , (5+96-64)*65536+20 ,4 ,

    mcall 4, <105, (5+96-16)>,[butTextColAPar] ,[St_NG]


    ;mcall , <105, (5+96-16-22)>, , St_X

    ;mcall , <105, (5+96-16-44)>, , St_O

    mov eax, TextBuff
    mov word [eax], 'O:'
        inc eax
        inc eax

    test [field], 0x1000
    jnz b1p
    mov ebx, [St_Comp]
    jmp b1c
    b1p:
    mov ebx, [St_Player]
    b1c:
    call Concat_lines
        mov byte [eax], 0
    mcall 4, <105, (5+96-16-22)>,[butTextColAPar] ,TextBuff

    mov eax, TextBuff
    mov word [eax], 'X:'
        inc eax
        inc eax

    test [field], 0x2000
    jnz b2p
    mov ebx, [St_Comp]
    jmp b2c
    b2p:
    mov ebx, [St_Player]
    b2c:
    call Concat_lines
        mov byte [eax], 0
    mcall 4, <105, (5+96-16-44)>,[butTextColAPar] ,TextBuff

;#|
    mcall 38 , 0, 5*65536+101 , [sc.work_graph]
    mcall  , 1*65536+1 , ,

    mcall  , 31*65536+31
    mcall  , 32*65536+32

    mcall  , 63*65536+63
    mcall  , 64*65536+64

    mcall  , 95*65536+95
    mcall  , 96*65536+96


;#-
    mcall 38 , 0*65536+96, 5*65536+5 ,
    mcall  , , 6*65536+6 ,

    mcall  , , (5+31)*65536+(5+31) ,
    mcall  , , (5+32)*65536+(5+32) ,

    mcall  , , (5+63)*65536+(5+63) ,
    mcall  , , (5+64)*65536+(5+64) ,

    mcall  , , (5+95)*65536+(5+95) ,
    mcall  , , (5+96)*65536+(5+96) ,

draw_XOs:
   mov eax, 0
   mov edx, 0x80000000
L1:
   push ax
   push edx


  test [field], edx
  jz L1_cont
;x
   ;AH - ostatok AL
    ;mov ax, 8
    mov ebx, 3 ; bl вызывает смещения.
    div bl
    mov cl, al

    shr ax, 8
    shl ax, 5
    ;obedenenoe
    ;shr ax, 3

    mov bx, ax
    shl eax, 16
    or eax, ebx
;y
    shl cx, 5
    mov bx, cx
    shl ecx, 16
    or ecx, ebx


   shr edx, 1
   test [field], edx
   jnz DrO

   call draw_X

   jmp L1_cont
   DrO:
   call draw_O



L1_cont:
    pop edx
    shr edx, 2

    pop ax
    inc ax
    cmp ax, 9
    jnz L1



call WinCon

;mov edi, [sc.work]
mov eax, TextBuff
mov edx, [field]
test edx, 16
jz Out_Turn
test edx, 32
jz No_Draw
mcall 13, 100*65536+96 , (5)*65536+20 , [sc.work]
mcall 4, <105, (5)>,[LabelTextColAPar] ,[St_Draw]
jmp DrawCon
No_Draw:
mov ebx,[St_Win]
call Concat_lines
test edx, 1
jz Win_O
mov word [eax], ' X'
jmp Win_X
Win_O:
mov word [eax], ' O'
Win_X:

jmp WconOT
Out_Turn:

mov ebx,[St_Turn]
call Concat_lines
test edx, 1
jnz Turn_O
mov word [eax], ' X'
jmp Turn_X
Turn_O:
mov word [eax], ' O'
Turn_X:

WconOT:
inc eax
inc eax
mov byte [eax], 0

mcall 13, 100*65536+96 , (5)*65536+20 , [sc.work]
mcall 4, <105, (5)>,[LabelTextColAPar] ,TextBuff
DrawCon:

call CompMove
cmp eax, 0
jnz draw_XOs




;SkipToBtn:







    mcall 12, 2                  ; функция 12.2, закончили рисовать

    ret                          ; выходим из процедуры







;---------------------------------------------------------------------
;---  ДАННЫЕ ПРОГРАММЫ  ----------------------------------------------
;---------------------------------------------------------------------

sc system_colors
butTextColAPar rd 1
LabelTextColAPar rd 1

field dd 0
;field dd 0xAFBEA000
; field dd 0x1000
TextBuff rb 32

title db 'XOs',0

St_NG rd 1
St_Comp rd 1
St_Player rd 1

St_Draw rd 1
St_Win rd 1
St_Turn rd 1

St_NG_Ru db 'Новая игра',0
St_NG_Eng db 'New game',0
St_Comp_Ru db 'Компьютер',0
St_Player_Ru db 'Игрок',0
St_Comp_Eng db 'Computer',0
St_Player_Eng db 'Player',0

St_Turn_Ru db 'Ход',0
St_Turn_Eng db 'Turn',0
St_Draw_Ru db 'Ничья',0
St_Draw_Eng db 'Draw',0
St_Win_Ru db 'Выйграл',0
St_Win_Eng db 'Won',0

;---------------------------------------------------------------------

I_END:                  ; метка конца программы
  ;rb 4096              ; память для стека
  rb 154       ;4*( макс глубина функций+ приблизительный счёт стека)+20% инженерный запас
align 16
STACKTOP:               ; метка вершины стека (при заполнении стек
                        ; растет в сторону уменьшения адресов, потому
                        ; память для него в коде программы встречается
                        ; раньше чем его вершина)
MEM:                    ; метка указывающая на конец программы плюс
                        ; размер используемой ею оперативной памяти
; Адрес метки MEM всегда должен быть больше чем адрес метки I_END.
; Метка STACKTOP должна располагается после метки I_END и перед меткой
;   MEM. STACKTOP может находится и перед I_END, но это не правильно.
; Имена меток могут быть с любыми названиями, главное соблюдать
;   правильный порядок их расположения.