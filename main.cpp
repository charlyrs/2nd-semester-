#include <iostream>



bool Triangle (int a, int b, int c){
    int result;
    __asm{
        mov eax, a
        mov ebx, b
        add eax, ebx
        jc _continue
        cmp eax, c
        jle _false
        _continue:
        mov eax, c
        add eax, ebx
        jc _continue1
        cmp eax, a
        jle _false
        _continue1:
        mov eax, a
        mov ebx, c
        add eax, ebx
        jc _true
        cmp eax, b
        jle _false
        _true:
        mov result, 1
        jmp _end
        _false:
        mov result, 0
        _end:
    }
    return result;
}

int main() {
     int result[3];
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;
    int n=1;
    std::cin >> n;
    int* a = new int[n];
    int* b = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        std::cin >> b[i];
    }
    
    __asm {
        mov edi, a
        mov esi, b
        mov ecx, 0

        _begin:
        cmp ecx, n
            je _end
            mov ebx, dword ptr[edi]
            mov eax, dword ptr[esi]
            
            imul ebx
            add edi, 4
            add esi, 4
            mov edx, 0
            add [result], eax
            adc  [result + 4], edx
            adc  [result + 8], 0
            inc ecx
            jmp _begin
            _end :
    }

    return 0;
}
