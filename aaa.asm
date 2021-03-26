.686
.model flat

.data
hh dd 180
eps dd ?
res dd 0
count dd 1
iks dd 0
factorial dd 1.0
item dd 0
.code


_Arcsin proc
FINIT
FLD dword ptr [esp+4]
FLD dword ptr [esp+4]
FMUL 
FLD1
FSUBR
FSQRT
FLD dword ptr [esp+4]
FDIVR
FLD1
FPATAN
FILD hh
FMUL
FLDPI
FDIV
FRNDINT
FIST hh
mov eax, hh

ret
_Arcsin endp








_SH proc
FINIT
FLD dword ptr[esp+8]
FSTP eps
FLD dword ptr[esp+4]
FST iks
FST item
FSTP res
FINIT
;mov ecx, 1

_begin:
FLD factorial
FLD iks
FLD item
FLD eps
FCOM 
FSTSW AX
SAHF
jnbe _end
FSTP eps
FSTP item
FLD dword ptr[esp+4]
FLD dword ptr[esp+4]
FMULP
FMULP
FST iks
lea eax, iks
FXCH
inc count
FILD count
inc count
FILD count
FMUL
FMUL
FST factorial
FDIV
FST item
FLD res
FADD
FST res
FINIT
jmp _begin

_end:
FLD res
ret
_SH endp


end