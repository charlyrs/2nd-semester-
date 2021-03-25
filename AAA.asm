.586
.model flat
.code
_Triangle@12 proc
        mov eax, [esp+4]
        mov ebx, [esp+8]
        add eax, ebx
        jc _continue
        cmp eax, [esp+12]
        jle _false
        _continue:
        mov eax, [esp+12]
        add eax, ebx
        jc _continue1
        cmp eax, [esp+4]
        jle _false
        _continue1:
        mov eax, [esp+4]
        mov ebx, [esp+12]
        add eax, ebx
        jc _true
        cmp eax, [esp+8]
        jle _false
        _true:
        mov eax, 1
        jmp _end
        _false:
        mov eax, 0
        _end:
        ret 12
_Triangle@12 endp
end