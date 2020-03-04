#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // 2. 동적메모리로 100byte를 할당받아 알파벳 출력

    int i = 0;
    char *pc;
    pc = (char *)malloc(100 * sizeof(char));

    if (pc == NULL)
    {
        printf("동적 메모리 할당에 실패");
        exit(1); // program 정상 종류
    }

    // pc가 가리키는 포인터를 1씩 증가시키며 알파벳 삽입
    for (i = 0; i < 26; i++)
    {
        *(pc + i) = 'a' + i;
    }

    *(pc + i) = 0; // 이 뒤에 할당했던 pc는 안쓰겠슴! ASCII 에서의 0 (NULL)값으로 초기화 == 문자열 종료를 의미
    printf("%s\n", pc);
    free(pc); // 동적 메모리 할당 해제

    return 0;
}