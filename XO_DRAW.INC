;---------------------------------------------------------------------

draw_X: ;eax x, edx, y
   push ebp
   mov ebp, esp
   sub esp, 8

  mov [ebp-8],eax
   mov [ebp-4],ecx
  mov ebx , (7)*65536+(30-5+1)
  add ebx , eax

  mov eax, (7+5-1)*65536+(30+1)
  add ecx, eax
  mcall 38 , , , 0xFF0000

  sub ebx, 1*65536
  sub ecx, 1
  mcall  , , ,

  sub ebx, 1
  add ecx, 1*65536+1
  mcall  , , ,

   mov ecx, (5+30-5+1)*65536+(7+5-1)
   add ecx, [ebp-4]

   mov ebx , (7-1)*65536+(30-5)
   add ebx , [ebp-8]

   mcall  , , ,

   add ebx, 1
   sub ecx, 1*65536
   mcall  , , ,

   add ebx, 1*65536
   add ecx, 1*65536+1
   mcall  , , ,

;   mcall 38 , (2+5+1)*65536+(30-5), (7+5)*65536+(5+30-5) , 0xFF0000
;   mcall 38 , (2+5)*65536+(30-5), (7+5)*65536+(5+30-1-5) , 0xFF0000
;   mcall 38 , (2+5)*65536+(30-5-1), (7+5+1)*65536+(5+30+0-5) , 0xFF0000
 ;
 ;mcall 38 , (2+5)*65536+(30-1-5), (5+30-5)*65536+(7+5) , 0xFF0000
 ;mcall 38 , (2+5)*65536+(30-5), (5+30-1-5)*65536+(7+5) , 0xFF0000
 ;mcall 38 , (2+5+1)*65536+(30-5), (5+30+0-5)*65536+(7+1+5) , 0xFF0000

 mov esp, ebp
 pop ebp
 ret

draw_O:
   push ebp
   mov ebp, esp
   sub esp, 8

   mov [ebp-8],eax
   mov [ebp-4],ecx
;||
   mov ebx , (2+5)*65536+(2+5)
   add ebx , eax

   mov eax, (7+5+5)*65536+(5+30-5-5)
   add ecx, eax

   mcall 38 , , , 0xFF

   sub ebx, 1*65536+1
   mcall , , ,

   add ebx, 2*65536+2
   mcall 38 , , , 0xFF

   mov ebx , (30-5)*65536+(30-5)
   add ebx , [ebp-8]
   mcall  , , ,

   sub ebx, 1*65536+1
   mcall  , , ,

   add ebx, 2*65536+2
   mcall , , ,

;--


   mov ebx , (2+10)*65536+(30-10)
   add ebx , [ebp-8]
   mov ecx, [ebp-4]
   mov eax, (7+5)*65536+(7+5)
   add ecx, eax

   mcall 38 , , ,

   sub ecx, 1*65536+1
   mcall  , , ,

   add ecx, 2*65536+2
   mcall  , , ,


   mov ebx , (2+10)*65536+(30-10)
   add ebx , [ebp-8]
   mov ecx, [ebp-4]
   mov eax, (5+30-5)*65536+(5+30-5)
   add ecx, eax

   mcall 38 , , ,

   sub ecx, 1*65536+1
   mcall  , , ,

   add ecx, 2*65536+2
   mcall  , , ,
;//

   mov ebx , (2+5)*65536+(2+10)
   add ebx , [ebp-8]
   mov ecx, [ebp-4]
   mov eax, (7+5+5)*65536+(7+5)
   add ecx, eax

   mcall 38 , , ,
   sub ebx, 1*65536
   sub ecx, 1
   mcall , , ,
   add ebx, 2*65536
   add ecx, 2
   mcall  , , ,

   mov ebx , (30-10)*65536+(30-5)
   add ebx , [ebp-8]
   mov ecx, [ebp-4]
   mov eax, (5+30-5)*65536+(5+30-5-5)
   add ecx, eax

   mcall 38 , , ,
   sub ebx, 1
   sub ecx, 1*65536
   mcall  , , ,
   add ebx, 2
   add ecx, 2*65536
   mcall 38 , , ,

;\\
   mov ebx , (30-5)*65536+(30-10)
   add ebx , [ebp-8]
   mov ecx, [ebp-4]
   mov eax, (7+5+5)*65536+(7+5)
   add ecx, eax

   mcall 38 , , ,

   sub ebx, 1*65536
   add ecx, 1
   mcall  , , ,
   add ebx, 2*65536
   sub ecx, 2

  mcall  , , ,


   mov ebx , (2+10)*65536+(2+5)
   add ebx , [ebp-8]
   mov ecx, [ebp-4]
   mov eax, (5+30-5)*65536+(5+30-5-5)
   add ecx, eax

   mcall 38 , , ,


   sub ebx, 1*65536
   add ecx, 1
   mcall  , , ,
   add ebx, 2*65536
   sub ecx, 2

   mcall  , , ,


 ;||
;
; mcall 38 , (2+5+1)*65536+(2+5+1), (7+5+5)*65536+(5+30-5-5) , 0xFF
;   mcall 38 , (2+5)*65536+(2+5),     (7+5+5)*65536+(5+30-5-5) , 0xFF
;   mcall 38 , (2+5-1)*65536+(2+5-1), (7+5+5)*65536+(5+30-5-5) , 0xFF

;   mcall 38 , (30-5+1)*65536+(30-5+1),  (7+5+5)*65536+(5+30-5-5) , 0xFF
;   mcall 38 , (30-5)*65536+(30-5),      (7+5+5)*65536+(5+30-5-5) , 0xFF
;   mcall 38 , (30-5-1)*65536+(30-5-1),  (7+5+5)*65536+(5+30-5-5) , 0xFF
;--
;   mcall 38 , (2+10)*65536+(30-10), (7+5+1)*65536+(7+5+1) , 0xFF
;   mcall 38 , (2+10)*65536+(30-10), (7+5)*65536+(7+5) , 0xFF
;   mcall 38 , (2+10)*65536+(30-10), (7+5-1)*65536+(7+5-1) , 0xFF

;   mcall 38 , (2+10)*65536+(30-10), (5+30-5+1)*65536+(5+30-5+1) , 0xFF
;   mcall 38 , (2+10)*65536+(30-10), (5+30-5)*65536+(5+30-5) , 0xFF
;   mcall 38 , (2+10)*65536+(30-10), (5+30-5-1)*65536+(5+30-5-1) , 0xFF
;//
;   mcall 38 , (2+5+1)*65536+(2+10), (7+5+5)*65536+(7+5+1) , 0xFF
;   mcall 38 , (2+5)*65536+(2+10), (7+5+5)*65536+(7+5) , 0xFF
;   mcall 38 , (2+5-1)*65536+(2+10), (7+5+5)*65536+(7+5-1) , 0xFF

;   mcall 38 , (30-10)*65536+(30-5+1), (5+30-5+1)*65536+(5+30-5-5) , 0xFF
;   mcall 38 , (30-10)*65536+(30-5),   (5+30-5)*65536+(5+30-5-5) , 0xFF
 ;  mcall 38 , (30-10)*65536+(30-5-1), (5+30-5-1)*65536+(5+30-5-5) , 0xFF
;\\
;   mcall 38 , (30-5-1)*65536+(30-10), (7+5+5)*65536+(7+5+1) , 0xFF
;   mcall 38 , (30-5)*65536+(30-10), (7+5+5)*65536+(7+5) , 0xFF
;   mcall 38 , (30-5+1)*65536+(30-10), (7+5+5)*65536+(7+5-1) , 0xFF

;   mcall 38 , (2+10)*65536+(2+5+1), (5+30-5-1)*65536+(5+30-5-5) , 0xFF
;   mcall 38 , (2+10)*65536+(2+5),   (5+30-5)*65536+(5+30-5-5) , 0xFF
;   mcall 38 , (2+10)*65536+(2+5-1), (5+30-5+1)*65536+(5+30-5-5) , 0xFF

 mov esp, ebp
 pop ebp

 ret