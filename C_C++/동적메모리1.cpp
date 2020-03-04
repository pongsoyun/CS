#include <stdio.h>
#include <stdlib.h> // malloc 사용

int main(void)
{
    // 1. 동적메모리를 간단하게 할당하여 사용/반환

    int *pi;                         // Pointer Integer
    pi = (int *)malloc(sizeof(int)); // malloc = 메모리를 할당해라 - int 대신 4(byte)를 넣어도 됨. (int *)를 통해 형변환

    if (pi == NULL)
    {
        printf("동적 메모리 할당에 실패했습니다.\n");
        exit(1); // program 종료
    }
    *pi = 100;
    printf("%d\n", *pi);
    free(pi); // 동적메모리 사용 이후에는 무조건 해당 메모리를 반환한다.
    return 0;
}