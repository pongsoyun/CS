#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // 3. 동적메모리로 정수 5개 처리

    int *pi;
    int i;
    pi = (int *)malloc(5 * sizeof(int));

    if (pi == NULL)
    {
        printf("동적 메모리 할당에 실패\n");
        exit(1);
    }

    pi[0] = 100; // pi = 100 과 동일
    pi[1] = 200;
    pi[2] = 300; // *(pi + 2) = 300; 와 동일
    pi[3] = 400;
    pi[4] = 500;

    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", *(pi + i));
    }
    free(pi);

    return 0;
}