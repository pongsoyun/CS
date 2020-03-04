#include <stdio.h>
#include <stdlib.h>
#include <cstring>

struct Book
{
    int number;
    char title[100];
};

void showBook(struct Book *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("번호 %d : %s\n", (p + i)->number, (p + i)->title);
    }
}

int main(void)
{
    // 1. 동적 메모리를 이용해 구조체 생성
    struct Book *p;
    p = (struct Book *)malloc(2 * sizeof(struct Book));
    if (p == NULL)
    {
        printf("동적 메모리 할당에 실패\n");
        exit(1);
    }

    p->number = 1; // 구조체pointer 은 화살표를 사용
    strcpy(p->title, "C Programming");

    (p + 1)->number = 2;
    strcpy((p + 1)->title, "Data Structure");

    showBook(p, 2);
    free(p);

    return 0;
}