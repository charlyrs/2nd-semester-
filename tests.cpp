#include <gtest/gtest.h>

int Calculate(int a, int b, int c, int y) {
    int result;
    int ostatok;
    __asm{
    mov eax, b
    mov ebx, y
    imul eax, ebx
    mov esi, c
    add eax, esi
    neg eax
    mov ebx, a
    imul ebx, 3
    cdq
    idiv ebx
    /////// далее округление
    mov ostatok, edx

    mov esi, eax
    mov eax, ebx
    cmp ostatok, 0
    je _end
    jnl _no
    neg ostatok
    _no:
    mov ebx, 2
    cmp eax, 0
    jnl _no_neg
    neg eax
    _no_neg:
    cdq
    idiv ebx

    cmp eax, ostatok
    jne _else
    mov eax, esi
    mov ebx, 2
    cdq
    idiv ebx
    cmp edx, 0
    je _end
    cmp esi, 0
    jnl _plus
    dec esi
    jmp _end
    _plus:
    inc esi
    jmp _end
    _else:
    jnl _end
    cmp esi, 0
    jnl _plus_one
    dec esi
    jmp _end
    _plus_one:
    inc esi


    _end:
    mov eax, esi
    mov result, eax
    }


    return result;
}
    //3ax + by + c = 0

    //тесты написала для себя
TEST(Check, A) { // проверка разного округления
    EXPECT_EQ(Calculate(1, 2, 3, 4), -4);
    EXPECT_EQ(Calculate(10, 20, 30, 40), -28); // -27,6
    EXPECT_EQ(Calculate(10, 20, 37, -40), 25); // 25,43
    EXPECT_EQ(Calculate(2, 8, 0, 1), -1);  // -1,333
    EXPECT_EQ(Calculate(2, 8, 3, 1), -2);  // -1,83
    EXPECT_EQ(Calculate(13, -12, 10, 16), 5); // 4,666
    EXPECT_EQ(Calculate(10, 12, 30, 16), -7); // -7,4
    EXPECT_EQ(Calculate(100,0,2,0),0);
}
TEST (Check, B){ // до ближайшего четного, когда половина
    EXPECT_EQ(Calculate(2, 0, 3, 0), 0);  // -0,5
    EXPECT_EQ(Calculate(2, 0, 9, 0), -2);  // -1,5
    EXPECT_EQ(Calculate(2, 0, -9, 0), 2);  // 1,5
    EXPECT_EQ(Calculate(2, 0, -15, 0), 2);  // 2,5
}
TEST (Check, C){
    EXPECT_EQ(Calculate(1, 0, -3, 0), 1);  // нацело
    EXPECT_EQ(Calculate(1, 0, 3, 0), -1);
    EXPECT_EQ(Calculate(1, 0, 6, 0), -2);
}