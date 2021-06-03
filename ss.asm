
.686 
.model flat
.code


_Polyndrom proc
								mov al, 0
								mov edi, dword ptr[esp+4]
	
								mov ecx, -1
_continue:
								add ecx, 1
								scasb
								jne _continue;


								mov edi, dword ptr[esp+4]
								mov esi, dword ptr[esp+4]
								add esi, ecx
								add esi, -1

_check:
								cmp ecx, 0
								jng _true;
								add ecx, -2
								mov eax, 0
								std
								lodsb
								cld
								scasb
								je _check;

								mov eax, 0
								jmp _end;

_true:
								mov eax, 1

_end:

		ret 
_Polyndrom endp
end