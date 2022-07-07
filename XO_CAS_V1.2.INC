;include 'debug.inc'
F2iL:; eax begin, cl shift, edx mask,  push the X/O mask
push ebp
mov ebp, esp
push eax
push ecx
push edx

mov ebx, [field]
and ebx, edx

F2iL_L:
push eax
xor eax, edx
and eax, [ebp+8]
cmp ebx, eax
pop eax
jz F2iL_Set
shr eax, cl

test eax, edx
jnz F2iL_L

xor ebx, ebx
jmp F2iL_r
F2iL_Set:

mov ebx, eax

F2iL_r:

pop edx
pop ecx
pop eax

pop ebp
ret

F2s: ;
push ebp
mov ebp, esp
sub esp, 4
mov [ebp-4], dword 0
push ebx

;\
mov eax, 0xC0000000
mov ecx, 8
mov edx, 0xC0C0C000

call F2iL
or [ebp-4], ebx

;/
shr eax, 4 ;mov eax, 0xC000000
shr cl, 1 ; mov cx, 4
mov edx, 0xCCC0000

call F2iL
or [ebp-4], ebx

;|0
mov eax, 0xC0000000
mov edx, 0xC30C0000
mov cl, 6

call F2iL
or [ebp-4], ebx

;|1
shr eax, 2;mov eax, 0x30000000
shr edx, 2;mov edx, 0x30C30000
;mov cx, 6
call F2iL
or [ebp-4], ebx

;|2
shr eax, 2;mov eax, 0xC000000
;mov cx, 6
shr edx, 2;mov edx, 0xC30C000

call F2iL
or [ebp-4], ebx

;-0
mov eax, 0xC0000000
mov cl, 2
mov edx, 0xFC000000

call F2iL
or [ebp-4], ebx

;-1
shr eax, 6;mov eax, 0x3000000
;mov ecx, 2
shr edx, 6;mov edx, 0x3F00000

call F2iL
or [ebp-4], ebx

;-2
shr eax, 6;mov eax, 0xC0000
;mov cx, 2
shr edx, 6;mov edx, 0xFC000

call F2iL
or ebx, [ebp-4]
mov eax, ebx

pop ebx
;debug_print_dec eax
;newline
mov esp, ebp
pop ebp

ret

randb:
push eax
push ebx

mcall 26, 9;SSF_TIME_COUNT

;debug_print_dec eax
mov ecx, eax
and ecx, 11111b
;debug_print_dec ecx

rndr:
pop ebx
pop eax
ret

CompMove:
    mov eax,0
    mov edx, [field]
    test edx, 16
    jnz rCompMove

    test edx, 1
    jnz step_CO

    test edx, 0x2000
    jnz rCompMove
    mov ebx, 0xAAAA8000
    call F2s
    cmp eax, 0
    jnz SetSign
    mov ebx, 0xFFFFC000
    call F2s
    cmp eax, 0
    jnz SetSign

    jmp NoWoD
    ;jmp rCompMove

    step_CO:
    test edx, 0x1000
    jnz rCompMove
    mov ebx, 0xFFFFC000
    call F2s
    cmp eax, 0
    jnz SetSign
    mov ebx, 0xAAAA8000
    call F2s
    cmp eax, 0
    jnz SetSign

   ;jmp rCompMove

NoWoD:
;CCCCC000 X
;33F30000 +

call randb
cmp cl, 20
ja noX    ;
;debug_print_dec 111
mov ebx, [field]
and ebx, 0x88888000
cmp ebx,  0x88888000
jz noX
noPl:
mov eax, 0x88888000
jmp SetSign

noX:
;debug_print_dec 222
mov ebx, [field]
and ebx, 0x22A20000
cmp ebx,  0x22A20000
jz noPl

mov eax, 0x22A20000

SetSign:

;debug_print_dec eax

mov  ebx, [field]
and ebx, 0xAAAA8000
xor ebx, eax
and eax, ebx
;debug_print_dec eax
;newline
call randb
and ecx, 11110b
mov ebx, 0x80000000

shr ebx, cl
;debug_print_dec ebx
jmp L1_in
L1_C:
shr ebx, 2
L1_in:
test ebx, 0xAAAA8000
jnz NoutB
shl ebx, 18
NoutB:
test ebx, eax
jz L1_C
;debug_print_dec ebx

    test [field], 1
    jz F2iL_setDiag1_WrO
    mov ecx, ebx
    shr ecx, 1
    or ebx, ecx
    ;and eax, 0xAAAA8000
    F2iL_setDiag1_WrO:

mov eax, [field]
or eax ,ebx
inc eax
;debug_print_dec ebx
mov [field], eax
push eax

mcall 5, 10

pop eax
rCompMove:

ret