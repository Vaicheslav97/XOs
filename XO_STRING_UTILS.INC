Concat_lines: ;eax s1inout, ebx s2

;mov eax, TextBuff
;mov edx, text2

Concat_lines_L:

mov cl, byte [ebx]
mov byte[eax],  cl

inc eax
inc ebx
cmp byte [ebx], 0
jnz Concat_lines_L

ret