

.data
matrix dq ?
n dq ?
flag dq 0
s1 dq 0
s2 dq 0
res dq 0
count dd 0
.code


Magic proc
        
        mov rax, rcx
        mov matrix, rax;
        mov r8, 0;
        mov rbx, matrix;
        mov rcx,rdx; 
        mov n, rdx; 
       
        begin_n:
        push rcx;                       
        mov rcx, n;                     
                                 
        mov rsi, qword ptr [rbx];       
        begin_m :
        movzx eax, word ptr[rsi]
	    add r8, rax
        add rsi, 2
        loop begin_m;


        mov rdx, flag;
        cmp rdx, 0;
        je _notcompare;
        cmp r8, s1;
        jne _end;
        mov s1, r8;
        mov r8, 0;
        jmp next;
        _notcompare:;
        mov s1, r8;
        mov rdx, 1;
        mov flag, rdx;
        next:;
        mov r8, 0;
        add rbx, 8;         
        pop rcx;            
        loop begin_n
        jmp correct;
        _end:;
        pop rcx;
        mov r8, 0;
        mov res, r8;
        mov eax, 1;
        cmp eax, 1;
        je _end1;
        correct:;
        mov r8, 1;
        mov res, r8;
        _end1:;
        cmp res,0
        je _null
        mov s1, 0;
        mov r8, 0;
        mov rbx, matrix;
        mov rcx, n;
        mov flag, 0;
        begin_0:;
        mov rbx, matrix;
        mov r8, 0;
        push rcx;
        mov rcx, n;
        begin_1:;
        mov rsi, qword ptr[rbx];
        add esi, count;
        movzx eax,  word ptr[rsi];
        add r8, rax;
        add rbx, 8;
        loop begin_1;
        cmp flag, 0;
        je _notcompare2;
        cmp s1, r8;
        jne _end20;
        mov s1, r8;
        add count, 2;
        pop rcx;
        loop begin_0;
        jmp pobeda;
        _notcompare2:;
        mov s1, r8;
        mov flag, 1;
        add count, 2;
        pop rcx;
        loop begin_0;

        _end20:;
        mov res, 0;
        pop rcx;
        jmp _end234;
        pobeda:;
        mov res, 1;
        _end234:;
        cmp res,0
        je _null
        mov rax, 1
        ret
        _null:
        mov rax,0

ret
Magic endp

end