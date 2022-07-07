CompAndMove:

mov ebx,ecx
and ebx,[field]
xor ebx,ecx
jnz skipH0

shr ecx, 1

mov ebx,ecx
and ebx,[field]
cmp ebx,ecx
jz Win
cmp ebx, 0
jz Win



jmp OutH0

skipH0:
shr ecx,1
OutH0:
shr ecx,1
jmp rcam
;

Win:
or eax, 128


rcam:

ret


WinCon:
xor eax, eax

mov ecx, 0x80808000  ;\
call CompAndMove
test eax, 128
jz noDi1
  mov ebx , (2)*65536+(96-2)
  mov ecx, (7)*65536+(96+3)
  mcall 38 , , , 0xFFFF00

  add ebx, 1*65536
  sub ecx, 1
  mcall  , , ,

  sub ebx, 1*65536+1
  add ecx, 1*65536+1
  mcall  , , ,

xor eax, eax
or [field], 16
noDi1:


mov ecx, 0x8880000  ;/
call CompAndMove
test eax, 128
jz noDi2

  mov ebx , (2)*65536+(96-2)
  mov ecx, (96+3)*65536+(7)
  mcall 38 , , , 0xFFFF00

  sub ebx, 1
  sub ecx, 1*65536
  mcall  , , ,

  add ebx, 1*65536+1
  add ecx, 1*65536+1
  mcall  , , ,

xor eax, eax
or [field], 16
noDi2:

mov ecx, 0xA8000000  ;-
call CompAndMove
test eax, 128
jnz DHor
add eax,32
shr ecx, 4

call CompAndMove
test eax, 128
jnz DHor
add eax,32
shr ecx, 4

call CompAndMove
test eax, 128
jz SDHor

DHor:
and eax ,96

mov ecx,(5+15)*65536+(5+15)
mov ebx, eax
shl ebx, 16
or eax,ebx
add ecx, eax

mcall 38 , 2*65536+(96-2),  , 0xFFFF00;-
add ecx, 1*65536+1
mcall 38 , , ,

or [field], 16
SDHor:
xor eax, eax

mov ecx, 0x82080000  ;|

call CompAndMove
test eax, 128
jnz DWert
add eax,32

call CompAndMove
test eax, 128
jnz DWert
add eax,32

call CompAndMove
test eax, 128
jz SDWert

DWert:

and eax ,96

mov ebx, eax
shl ebx, 16
or eax, ebx

mov ebx,(15)*65536+(15)
add ebx, eax

mcall 38 , , 7*65536+99 , 0xFFFF00 ;|
add ebx, 1*65536+1
mcall 38 , , ,

or [field], 16
SDWert:
test [field], 16
jnz noDow
mov edx, [field]
and edx, 0xF
cmp edx, 9
jnz noDow
or [field], 48
noDow:

ret