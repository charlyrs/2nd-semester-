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
    int res;
    int result[]={0,0,0};
    int n;
    std::cin >> n;
    int* a = new int[n];
    int* b = new int[n];
    a[0]=1;
    a[1]=2;
    a[2]=3;
    b[0]=1;
    b[1]=2;
    b[2]=3;

    __asm{
        lea edi, a
        lea esi, b
        mov ecx,0

        _begin:
        cmp ecx, n
        je _end
        mov ebx, dword ptr [edi]
        add edi, 4
        mov eax, dword ptr [esi]
        add esi, 4
        imul ebx
        mov edx,0
        add result, eax
        adc [result+4], edx
        adc [result + 8], 0
        inc ecx
        jmp _begin
        _end:

    }
    std::cout << result[0];






    //delete [] result;

    return 0;
}
