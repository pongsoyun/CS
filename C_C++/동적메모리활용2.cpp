#include <stdio.h>
#include <stdlib.h>
#include <cstring>

int main(void)
{
    int i, x, y;
    int **pptr = (int **)malloc(sizeof(int *) * 8); // (int형 포인터공간 8개)가 만들어지는 것
    for (int i = 0; i < 8; i++)
    {
        *(pptr + i) = (int *)malloc(sizeof(int) * 6); // 그 위의 포인터 하나가 가리키고있는 곳은 또 int형 공간 6개 가 만들어지는 것
    }

    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 6; x++)
        {
            *(*(pptr + y) + x) = 6 * y + x;
        }
    }

    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 6; x++)
        {
            printf("%3d", *(*(pptr + y) + x));
        }
        printf("\n");
    }

    for (y = 0; y < 8; y++)
    {

        free(*(pptr + y));
    }

    free(pptr);

    return 0;
}